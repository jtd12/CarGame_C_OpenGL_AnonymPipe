#ifndef DEF_APP_CLIENT_H
#define DEF_APP_CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>
#include <GL/glut.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include<math.h>
#include"entities/textures/texture.h"

void clientProcess(int toClient[2],int toServer[2],int toClient2[2],int toServer2[2],
int toClient3[2],int toServer3[2],int toClient4[2],int toServer4[2],int toClient5[2],int toServer5[2],
int toClient6[2],int toServer6[2],int toClient7[2],int toServer7[2]);

void* communicationThread2(void* args);
void* gameUpdateThread2(void* args);

extern int WINDOWSWIDTH;
extern int WINDOWSHEIGHT;

extern pthread_mutex_t carMutex2;
extern pthread_mutex_t cameraMutex2;
extern pthread_mutex_t roueMutex2;

extern int sound1,sound2;

#endif
