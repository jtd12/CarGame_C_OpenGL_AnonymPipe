#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glut.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include"APP_SERVEUR.h"
#include"APP_CLIENT.h"
#include"tubes_anonymes.h"


int main() {

    if (pipe(toClient) == -1 || pipe(toServer) == -1 || pipe(toClient2) == -1 || pipe(toServer2) == -1  ||
    pipe(toClient3) == -1 || pipe(toServer3) == -1 ||  pipe(toClient4) == -1 || pipe(toServer4) == -1 
    ||  pipe(toClient5) == -1 || pipe(toServer5) == -1 
    || pipe(toClient6) == -1 || pipe(toServer6) == -1) {
        perror("Erreur lors de la création des tubes");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("Erreur lors du fork");
        exit(EXIT_FAILURE);
    }
    

    if (pid == 0) {
        printf("Processus client démarré.\n");
        clientProcess(toClient, toServer,toClient2, toServer2,toClient3, toServer3,toClient4, toServer4,toClient5, toServer5,toClient6, toServer6);
    } else {
        printf("Processus serveur démarré.\n");
        serverProcess(toClient, toServer,toClient2, toServer2,toClient3, toServer3,toClient4, toServer4,toClient5, toServer5,toClient6, toServer6);

        // Attendre la fin du processus client
        wait(NULL);
        printf("Processus client terminé.\n");
    }

    return 0;
}

