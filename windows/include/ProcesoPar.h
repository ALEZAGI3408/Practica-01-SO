#ifndef PROCESOPAR_H
#define PROCESOPAR_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int Estado_t;

/**
 * Estructura que representa un Proceso Par.
 * Contiene la información necesaria para controlar el proceso hijo
 * y las tuberías de comunicación.
 */
typedef struct ProcesoPar {
    HANDLE hPipeEntrada;   /* A lee aquí lo que B escribe (stdout de B) */
    HANDLE hPipeSalida;    /* A escribe aquí lo que B lee (stdin de B)  */
    PROCESS_INFORMATION pi;
    HANDLE hHiloEscucha;
    Estado_t (*callback)(const char *mensaje, int longitud);
} ProcesoPar_t;

/* Códigos de estado básicos */
#define E_OK               0  /* Operación correcta                */
#define E_PAR_INC          1  /* Parámetro incorrecto              */
#define E_ERR_CREAR_PIPES  2  /* Error creando tuberías            */
#define E_ERR_CREAR_PROCESO 3 /* Error creando proceso hijo        */
#define E_ERR_ESCRITURA    4  /* Error escribiendo en la tubería   */
#define E_ERR_LECTURA      5  /* Error leyendo de la tubería       */

/**
 * Lanza un proceso par.
 *
 * nombreArchivoEjecutable: ruta al ejecutable hijo.
 * listaLineaComando: lista de argumentos terminados en NULL (puede ser NULL).
 * procesoPar: puntero de salida que apuntará a la estructura creada.
 */
Estado_t lanzarProcesoPar(const char *nombreArchivoEjecutable,
                          const char **listaLineaComando,
                          ProcesoPar_t **procesoPar);

/**
 * Destruye un proceso par y libera recursos.
 */
Estado_t destruirProcesoPar(ProcesoPar_t *procesoPar);

/**
 * Envía un mensaje al proceso par (hijo) a través de la tubería de salida.
 */
Estado_t enviarMensajeProcesoPar(ProcesoPar_t *procesoPar,
                                 const char *mensaje,
                                 int longitud);

/**
 * Establece una función de escucha que se invocará cada vez que
 * llegue un mensaje desde el proceso hijo.
 *
 * f: función con la forma Estado_t f(const char *mensaje, int longitud)
 */
Estado_t establecerFuncionDeEscucha(ProcesoPar_t *procesoPar,
                                    Estado_t (*f)(const char *, int));

#ifdef __cplusplus
}
#endif

#endif /* PROCESOPAR_H */
