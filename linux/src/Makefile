CC=gcc
CFLAGS=-I../include -Wall

OBJS=lanzarProcesoPar.o enviarMensajeProcesoPar.o establecerFuncionDeEscucha.o destruirProcesoPar.o main.o
CHILD=child.o

all: demo child

demo: $(OBJS)
	$(CC) $(CFLAGS) -o ../lib/proceso_par_demo $(OBJS) -lpthread

child: $(CHILD)
	$(CC) $(CFLAGS) -o child child.o

clean:
	rm -f *.o ../lib/proceso_par_demo child
