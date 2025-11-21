#include "ProcesoPar.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

Estado_t cb(const char*m,int n){
    write(STDOUT_FILENO,"[CALLBACK] ",11);
    write(STDOUT_FILENO,m,n);
    return 0;
}

int main(){
    const char*args[]={"./child",NULL};
    ProcesoPar_t *pp = NULL;

    Estado_t st = lanzarProcesoPar("./child",args,&pp);
    if (st != E_OK) {
       fprintf(stderr, "Error lanzando proceso par, estado = %u\n", st);
       return 1;
    }

    establecerFuncionDeEscucha(pp,cb);

    const char *m1 = "Hola hijo\n";
    enviarMensajeProcesoPar(pp, m1, (int)strlen(m1));
    sleep(1);

    const char *m2 = "Todo bien por alla?\n";
    enviarMensajeProcesoPar(pp, m2, (int)strlen(m2));
    sleep(1);

    const char *m3 = "FIN\n";
    enviarMensajeProcesoPar(pp, m3, (int)strlen(m3));

    sleep(2);

    destruirProcesoPar(pp);
    return 0;
}
