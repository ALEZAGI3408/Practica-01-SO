#ifndef PROCESOPAR_H
#define PROCESOPAR_H
#include <unistd.h>
typedef unsigned int Estado_t;
typedef struct ProcesoPar {
    int pipePadreA[2];
    int pipePadreB[2];
    pid_t pid;
    Estado_t (*callback)(const char*,int);
} ProcesoPar_t;

#define E_OK 0
#define E_PAR_INC 1
#define E_ERR_PIPE 2
#define E_ERR_FORK 3
#define E_ERR_EXEC 4
#define E_ERR_WRITE 5
#define E_ERR_READ 6

Estado_t lanzarProcesoPar(const char*, const char**, ProcesoPar_t**);
Estado_t enviarMensajeProcesoPar(ProcesoPar_t*, const char*, int);
Estado_t establecerFuncionDeEscucha(ProcesoPar_t*, Estado_t (*f)(const char*,int));
Estado_t destruirProcesoPar(ProcesoPar_t*);
#endif
