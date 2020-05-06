#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "named_semaphores.h"

int main(void)
{
    liberar_semaforos();

    while (1)
    {

        pid_t pid = fork();
        if (pid < 0)
        {

            printf("Error\n");
        }
        else if (pid == 0)
        {

            printf("Y yo soy el hijo\n");
            sleep(1);

            realizarTarea();

            // Finaliza el proceso hijo

            exit(0);
        }
        else
        { // Padre

            printf("%d soy tu padre\n", pid);
        }
    }

    return 0;
}
