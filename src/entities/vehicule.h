#ifndef DEF_VEHICULE_H
#define DEF_VEHICULE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glut.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<time.h>
#include<math.h>
#include"functions/functions.h"
#include"sound/sound.h"
#define NUM 6
#define SIZECAR 1
#define SIZEAICAR 10
#define SIZEROUES 4
#define SIZEROUESAI 4
#define COLORCAR 4


static int points[NUM][2] = {15,30,
                        45,30,
                        45,-50,
                        -40,-50,
                        -40,40,
                        5,25
                       };


					  
// Structure représentant une voiture
typedef struct {
    float x, y,z;   // Position
    float speed,maxSpeed,acc,dec,turnSpeed,frein;
    float rotation;
    int nn;
    int points;
    float rotationLineHUD;
    float colorCarRandomR[COLORCAR],colorCarRandomG[COLORCAR],colorCarRandomB[COLORCAR];
    int deviation;
} Car;

Car cars[SIZECAR]; // Une seule voiture pour cet exemple

Car carsAI[SIZEAICAR];

extern int timer;
extern int finishedGame;
extern int rotTeapot;

typedef struct {
    float x, y,z;   // Position
    float rot;
    int rot_;
} Roue;

Roue roues[SIZEROUES]; // les roues

Roue rouesAI[SIZEROUESAI]; // les roues

void initialiseTimer();
void initialiseCar();
void drawCar(Car car);
void controlCar(Car *car,char command);
void updateCar(Car *car, float deltaTime);
void initialiseCarsAI();
void setPhysicsCarAI();
void  updateCarAI(float deltaTime);
void setPhysics();
void collisionInterior();
void collisionExterior();
void collisionInteriorCarAI();
void collisionExteriorCarAI();
void collisionBetweenCar_CARAI();
void collisionBetweenCarAI();
void resetCar(char command);
void resetCarAI(char command);
int checkCollision(float carMinX,float carMinY,float carMinZ, float carMaxX,float carMaxY,float carMaxZ, float cubeMinX,float cubeMinY,float cubeMinZ, float cubeMaxX,float cubeMaxY,float cubeMaxZ);
int checkCollisionAABB(float x1_min, float x1_max, float y1_min, float y1_max,float z1_min, float z1_max,
                       float x2_min, float x2_max, float y2_min, float y2_max,float z2_min, float z2_max);
void findTarget();
void drawCheckPoints(float x, float y, float z,float rot,float r,float g,float b);
void checkPoints(float x,float y,float z);
void checkPointsAI(float x,float y,float z);
void rotationRoues(char command,float deltaTime);
void rotationRouesAI(float deltaTime);
void drawRoues();
#endif
