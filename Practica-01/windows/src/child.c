#include <stdio.h>
#include <string.h>

/* Programa hijo que lee de stdin y responde por stdout */
int main(void) {
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), stdin)) {
        printf("Hijo recibio: %s", buffer);
        fflush(stdout);

        if (strstr(buffer, "Fin de la comunicación.") != NULL) {
            break;
        }
    }

    return 0;
}
