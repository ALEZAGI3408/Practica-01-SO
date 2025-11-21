#include "ProcesoPar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

Estado_t lanzarProcesoPar(const char *exe, const char **args, ProcesoPar_t **pp){
    *pp = malloc(sizeof(ProcesoPar_t));
    if(!*pp) return E_PAR_INC;

    if(pipe((*pp)->pipePadreA)<0) return E_ERR_PIPE;
    if(pipe((*pp)->pipePadreB)<0) return E_ERR_PIPE;

    pid_t pid=fork();
    if(pid<0) return E_ERR_FORK;

    if(pid==0){
        dup2((*pp)->pipePadreA[0],0);
        dup2((*pp)->pipePadreB[1],1);
        close((*pp)->pipePadreA[1]);
        close((*pp)->pipePadreB[0]);
        execvp(exe,(char*const*)args);
        exit(1);
    }

    (*pp)->pid=pid;
    (*pp)->callback=NULL;

    close((*pp)->pipePadreA[0]);
    close((*pp)->pipePadreB[1]);

    return E_OK;
}
