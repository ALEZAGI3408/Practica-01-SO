#include "ProcesoPar.h"
#include <windows.h>
#include <stdlib.h>

Estado_t destruirProcesoPar(ProcesoPar_t *procesoPar) {
    if (!procesoPar) return E_PAR_INC;

    /* Cerramos la tubería de escritura para indicar EOF al hijo */
    if (procesoPar->hPipeSalida) {
        CloseHandle(procesoPar->hPipeSalida);
        procesoPar->hPipeSalida = NULL;
    }

    /* Esperamos a que el proceso hijo termine (timeout opcional) */
    if (procesoPar->pi.hProcess) {
        WaitForSingleObject(procesoPar->pi.hProcess, 3000);
        CloseHandle(procesoPar->pi.hProcess);
        CloseHandle(procesoPar->pi.hThread);
    }

    if (procesoPar->hPipeEntrada) {
        CloseHandle(procesoPar->hPipeEntrada);
        procesoPar->hPipeEntrada = NULL;
    }

    if (procesoPar->hHiloEscucha) {
        WaitForSingleObject(procesoPar->hHiloEscucha, 1000);
        CloseHandle(procesoPar->hHiloEscucha);
    }

    free(procesoPar);
    return E_OK;
}
