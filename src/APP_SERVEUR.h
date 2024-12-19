#ifndef DEF_APP_SERVEUR_H
#define DEF_APP_SERVEUR_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <GL/glut.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

extern pthread_mutex_t carMutex;
extern pthread_mutex_t cameraMutex;
extern pthread_mutex_t roueMutex;

void serverProcess(int toClient[2], int toServer[2],int toClient2[2],int toServer2[2],
int toClient3[2],int toServer3[2],int toClient4[2],int toServer4[2],int toClient5[2],int toServer5[2],
int toClient6[2],int toServer6[2]);

void* communicationThread(void* args);
void* gameUpdateThread(void* args);

#endif
