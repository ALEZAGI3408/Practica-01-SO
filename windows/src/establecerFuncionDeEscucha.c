#include "ProcesoPar.h"
#include <windows.h>
#include <stdio.h>

static DWORD WINAPI hiloEscucha(LPVOID param) {
    ProcesoPar_t *pp = (ProcesoPar_t*)param;
    if (!pp) return 0;

    char buffer[1024];
    DWORD leidos = 0;

    while (1) {
        BOOL ok = ReadFile(pp->hPipeEntrada, buffer, sizeof(buffer) - 1, &leidos, NULL);
        if (!ok || leidos == 0) {
            break; /* Fin de la comunicación */
        }
        buffer[leidos] = '\0';

        if (pp->callback) {
            pp->callback(buffer, (int)leidos);
        } else {
            /* Comportamiento por defecto: imprimir en stdout */
            printf("Mensaje desde hijo: %s", buffer);
            fflush(stdout);
        }
    }

    return 0;
}

Estado_t establecerFuncionDeEscucha(ProcesoPar_t *procesoPar,
                                    Estado_t (*f)(const char *, int)) {
    if (!procesoPar) return E_PAR_INC;

    procesoPar->callback = f;

    HANDLE hThread = CreateThread(
        NULL,
        0,
        hiloEscucha,
        procesoPar,
        0,
        NULL
    );

    if (!hThread) {
        return E_ERR_LECTURA;
    }

    procesoPar->hHiloEscucha = hThread;
    return E_OK;
}
