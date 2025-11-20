#include "ProcesoPar.h"
#include <windows.h>

Estado_t enviarMensajeProcesoPar(ProcesoPar_t *procesoPar,
                                 const char *mensaje,
                                 int longitud) {
    if (!procesoPar || !mensaje || longitud <= 0) return E_PAR_INC;

    DWORD escritos = 0;
    BOOL ok = WriteFile(procesoPar->hPipeSalida,
                        mensaje,
                        (DWORD)longitud,
                        &escritos,
                        NULL);
    if (!ok || escritos != (DWORD)longitud) {
        return E_ERR_ESCRITURA;
    }

    return E_OK;
}
