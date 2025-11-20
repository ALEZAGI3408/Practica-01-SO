# Makefile para compilar la práctica en Windows (MSYS2 MINGW64)

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include
LDFLAGS =

LIB_OBJS = lanzarProcesoPar.o enviarMensajeProcesoPar.o establecerFuncionDeEscucha.o destruirProcesoPar.o
DEMO_OBJS = main.o
CHILD_OBJS = child.o

all: ../lib/proceso_par_demo.exe child.exe

../lib/proceso_par_demo.exe: $(LIB_OBJS) $(DEMO_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

child.exe: $(CHILD_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o ../lib/proceso_par_demo.exe child.exe

.PHONY: all clean
