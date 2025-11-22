Practica 01 - Procesos Par

Este repositorio contiene la implementación del mecanismo de Proceso Par para 
los sistemas operativos **Windows** y **Linux**, cumpliendo con los requisitos 
establecidos en la práctica.

Estructura:

Practica-01-SO/
│
├── windows/     → Implementación completa para Windows (MSYS2 + GCC)
│   ├── src/
│   ├── include/
│   ├── lib/
│   └── readme.txt
│
├── linux/       → Implementación completa para Linux (POSIX + GCC)
│   ├── src/
│   ├── include/
│   ├── lib/
│   └── readme.txt
│
└── readme.txt   → Este archivo

Contenido del proyecto:
-----------------------

Cada plataforma contiene:

- Una implementación propia del API:
    - lanzarProcesoPar()
    - enviarMensajeProcesoPar()
    - establecerFuncionDeEscucha()
    - destruirProcesoPar()

- Un archivo de encabezados común: `ProcesoPar.h`

- Un proceso hijo (`child`) que se comunica con el padre vía tuberías

- Un programa demostración (`proceso_par_demo` / `proceso_par_demo.exe`)

- Un Makefile para compilar desde cada plataforma
