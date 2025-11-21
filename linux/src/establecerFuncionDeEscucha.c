#include "ProcesoPar.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* threadEscucha(void*arg){
    ProcesoPar_t*pp=arg;
    char b[256];
    while(1){
        int r=read(pp->pipePadreB[0],b,sizeof(b));
        if(r<=0) break;
        if(pp->callback) pp->callback(b,r);
        else write(1,b,r);
    }
    return NULL;
}

Estado_t establecerFuncionDeEscucha(ProcesoPar_t*pp,Estado_t(*f)(const char*,int)){
    pp->callback=f;
    pthread_t t;
    pthread_create(&t,NULL,threadEscucha,pp);
    pthread_detach(t);
    return E_OK;
}
