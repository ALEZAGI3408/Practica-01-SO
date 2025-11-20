#include "ProcesoPar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Construye la línea de comandos a partir del ejecutable y la lista de argumentos */
static char *construirLineaComando(const char *exe, const char **args) {
    size_t len = strlen(exe) + 3; /* comillas + espacio */
    if (args) {
        for (int i = 0; args[i] != NULL; ++i) {
            len += strlen(args[i]) + 1;
        }
    }
    char *cmd = (char*)malloc(len + 1);
    if (!cmd) return NULL;

    /* Formato sencillo: exe arg1 arg2 ... */
    strcpy(cmd, exe);
    if (args) {
        for (int i = 0; args[i] != NULL; ++i) {
            strcat(cmd, " ");
            strcat(cmd, args[i]);
        }
    }
    return cmd;
}

Estado_t lanzarProcesoPar(const char *nombreArchivoEjecutable,
                          const char **listaLineaComando,
                          ProcesoPar_t **procesoPar) {
    if (!nombreArchivoEjecutable || !procesoPar) return E_PAR_INC;

    *procesoPar = (ProcesoPar_t*)malloc(sizeof(ProcesoPar_t));
    if (!*procesoPar) return E_PAR_INC;

    ZeroMemory(*procesoPar, sizeof(ProcesoPar_t));

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    HANDLE childStdInRead = NULL;
    HANDLE childStdInWrite = NULL;
    HANDLE childStdOutRead = NULL;
    HANDLE childStdOutWrite = NULL;

    /* Tubería para stdin del hijo: A escribe, B lee */
    if (!CreatePipe(&childStdInRead, &childStdInWrite, &sa, 0)) {
        return E_ERR_CREAR_PIPES;
    }
    /* Evitar que el extremo de escritura sea heredable si no se necesita */
    SetHandleInformation(childStdInWrite, HANDLE_FLAG_INHERIT, 0);

    /* Tubería para stdout del hijo: B escribe, A lee */
    if (!CreatePipe(&childStdOutRead, &childStdOutWrite, &sa, 0)) {
        return E_ERR_CREAR_PIPES;
    }
    SetHandleInformation(childStdOutRead, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput  = childStdInRead;
    si.hStdOutput = childStdOutWrite;
    si.hStdError  = childStdOutWrite;

    char *cmdLine = construirLineaComando(nombreArchivoEjecutable, listaLineaComando);
    if (!cmdLine) {
        return E_PAR_INC;
    }

    BOOL ok = CreateProcessA(
        NULL,
        cmdLine,
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    );

    free(cmdLine);

    if (!ok) {
        return E_ERR_CREAR_PROCESO;
    }

    /* En el padre, conservamos:
       - childStdInWrite para enviar datos al hijo
       - childStdOutRead para recibir datos del hijo
     */
    CloseHandle(childStdInRead);
    CloseHandle(childStdOutWrite);

    (*procesoPar)->hPipeSalida  = childStdInWrite;
    (*procesoPar)->hPipeEntrada = childStdOutRead;
    (*procesoPar)->pi = pi;
    (*procesoPar)->hHiloEscucha = NULL;
    (*procesoPar)->callback = NULL;

    return E_OK;
}
