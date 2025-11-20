#include "ProcesoPar.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>

static Estado_t callbackDemo(const char *mensaje, int longitud) {
    printf("[CALLBACK] Mensaje recibido (%d bytes): %.*s",
           longitud,
           longitud,
           mensaje);
    return E_OK;
}

int main(void) {
    ProcesoPar_t *pp = NULL;

    /* Sin argumentos adicionales, listaLineaComando = NULL */
    const char **args = NULL;

    printf("Lanzando proceso hijo (child.exe)...\n");

    Estado_t st = lanzarProcesoPar("child.exe", args, &pp);
    if (st != E_OK) {
        printf("Error lanzando proceso hijo. Estado = %u\n", st);
        return 1;
    }

    /* Establecemos la función de escucha */
    establecerFuncionDeEscucha(pp, callbackDemo);

    /* Enviamos algunos mensajes al hijo */
    const char *msg1 = "Hola hijo, soy el padre.\n";
    enviarMensajeProcesoPar(pp, msg1, (int)strlen(msg1));

    Sleep(1000);

    const char *msg2 = "Todo bien por alla\n";
    enviarMensajeProcesoPar(pp, msg2, (int)strlen(msg2));

    Sleep(1000);

    const char *msg3 = "Fin de la comunicacion.\n";
    enviarMensajeProcesoPar(pp, msg3, (int)strlen(msg3));

    /* Cerramos y esperamos a que todo termine */
    Sleep(2000);
    destruirProcesoPar(pp);

    printf("Proceso par destruido. Fin del demo.\n");
    return 0;
}
