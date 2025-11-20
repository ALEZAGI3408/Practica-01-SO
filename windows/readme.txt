Practica 01 - Implementación Windows

Requisitos:
- Windows 10/11
- MSYS2 (https://www.msys2.org/)
- Paquetes: mingw-w64-x86_64-gcc, mingw-w64-x86_64-make

Pasos básicos:

1. Abrir "MSYS2 MINGW64".
2. Ir a la carpeta src:
   cd /c/ruta/a/Practica-01/windows/src

3. Compilar:
   mingw32-make

4. Ejecutar el programa de prueba (desde src):
   ./../lib/proceso_par_demo.exe

Esto lanzará el proceso hijo (child.exe), le enviará un mensaje y mostrará
la respuesta recibida por la tubería.
