#include "ProcesoPar.h"
#include <unistd.h>

Estado_t enviarMensajeProcesoPar(ProcesoPar_t *pp, const char *msg, int length){
    if(!pp||!msg) return E_PAR_INC;
    int w=write(pp->pipePadreA[1],msg,length);
    return (w==length)?E_OK:E_ERR_WRITE;
}
