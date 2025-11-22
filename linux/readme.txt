PRACTICA 01 - PROCESO PAR (LINUX)
=================================

Esta carpeta contiene la implementación del Proceso Par para Linux utilizando 
llamadas al sistema POSIX (pipe, fork, dup2, execvp, read, write) y hilos 
pthread para la función de escucha.

Estructura de la carpeta:
-------------------------

linux/
│
├── src/
│   ├── lanzarProcesoPar.c
│   ├── enviarMensajeProcesoPar.c
│   ├── establecerFuncionDeEscucha.c
│   ├── destruirProcesoPar.c
│   ├── main.c
│   ├── child.c
│   └── Makefile
│
├── include/
│   └── ProcesoPar.h
│
└── lib/
    (Aquí se genera proceso_par_demo después de compilar)

Compilación:
------------

Ingresar a la carpeta src:

    cd Practica-01/linux/src

Compilar el proyecto:

    make

Esto genera:
- proceso_par_demo en ../lib/
- child en la carpeta actual

Ejecución:
----------

Muy importante: ejecutar desde src para que el hijo pueda ser localizado:

    ./../lib/proceso_par_demo

Salida esperada:

    [CALLBACK] Hijo recibio: Hola hijo
    [CALLBACK] Hijo recibio: Todo bien por alla?
    [CALLBACK] Hijo recibio: FIN

Limpieza del proyecto:

    make clean
