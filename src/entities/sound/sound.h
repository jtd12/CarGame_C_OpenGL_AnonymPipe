#ifndef DEF_SOUND_H
#define DEF_SOUND_H
#include <stdlib.h>
#include <stdio.h> // Include this for fprintf
#include <string.h>
#include <AL/al.h>
#include <AL/alc.h>



typedef struct {
    int sourceid;
    int bufferid;
    char *buffer;
    char *name; // C equivalent for std::string
} Data;


// Global variables

// Function declarations
void initializeSound();
unsigned int loadSound(const char *filename);
void deleteSound(unsigned int id);
void playSound(unsigned int id);
void playSoundWithPosition(unsigned int id, int positionX, int positionY, int positionZ, float pitch);
void stopSound(unsigned int id);
void setListener(int positionX, int positionY, int positionZ, int orientationX, int orientationY, int orientationZ);
void freeSound();
void playSoundLoop(unsigned int id);
char *loadWAV(const char *fn, int *chan, int *samplerate, int *bps, int *size);
int convertToInt(char *buffer, int len);
int isBigEndian_();

typedef struct
{
 int sound1;
 int sound2;
 Data *datas; // Dynamic array of Data structs
 int datasCount;
 ALCcontext *context;
 ALCdevice *device;
 int isBigEndian;
} Sound;

Sound sound;

#endif
