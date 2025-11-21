#include "ProcesoPar.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

Estado_t destruirProcesoPar(ProcesoPar_t*pp){
    if(!pp) return E_PAR_INC;
    close(pp->pipePadreA[1]);
    close(pp->pipePadreB[0]);
    waitpid(pp->pid,NULL,0);
    free(pp);
    return E_OK;
}
