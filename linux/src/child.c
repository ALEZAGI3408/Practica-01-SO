#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
    char b[256];
    while(fgets(b,sizeof(b),stdin)){
        printf("Hijo recibio: %s",b);
        fflush(stdout);
        if(strstr(b,"FIN")){
	  fflush(stdout);
	  usleep(10000);
	  break;
	}
    }
}
