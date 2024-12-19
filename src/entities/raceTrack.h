#ifndef DEF_RACETRACK_H
#define DEF_RACETRACK_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glut.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<math.h>
#include<time.h>
#include"functions/functions.h"
#define NUMBERBLOC 10
#define NUMPOINTS 50

extern const float trackWidth; // Largeur de la piste

extern GLfloat vertices[8][3];

float scaleRandomX[NUMBERBLOC],scaleRandomY[NUMBERBLOC],scaleRandomZ[NUMBERBLOC];
float colorRandomR[NUMBERBLOC],colorRandomG[NUMBERBLOC],colorRandomB[NUMBERBLOC];
// Stockage des points de la piste
float trackPoints[NUMPOINTS][2];

void initialiseCity();
void generateTrack();
void drawTrack();
void drawPlane(float size);
void drawCube();
void drawCity();

#endif
