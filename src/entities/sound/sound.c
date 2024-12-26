#include"sound.h"


   
void initializeSound() {
   sound.datas = NULL; // Dynamic array of Data structs
   sound.datasCount = 0;
   sound.context = NULL;
   sound.device = NULL;
   sound.isBigEndian = 0;
   
    sound.device = alcOpenDevice(NULL); // Open default audio device
    if (!sound.device) {
        fprintf(stderr, "Failed to open audio device\n");
        exit(EXIT_FAILURE);
    }
    sound.context = alcCreateContext(sound.device, NULL);
    if (!sound.context  || alcMakeContextCurrent(sound.context) == ALC_FALSE) {
        fprintf(stderr, "Failed to create audio context\n");
          if (sound.context) alcDestroyContext(sound.context);
        alcCloseDevice(sound.device);
        exit(EXIT_FAILURE);
    }
    alcMakeContextCurrent(sound.context);
    sound.isBigEndian = isBigEndian_();
}

unsigned int loadSound(const char *filename) {
    initializeSound();
    int channels, samplerate, bps, size;
    char *wavBuffer = loadWAV(filename, &channels, &samplerate, &bps, &size);
    if (!wavBuffer) {
        fprintf(stderr, "Failed to load WAV file: %s\n", filename);
        return 0;
    }

    unsigned int buffer, source;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, (channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16), wavBuffer, size, samplerate);
    free(wavBuffer);

    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    // Add to datas array
    sound.datasCount++;
    sound.datas = (Data *)realloc(sound.datas, sound.datasCount * sizeof(Data));
    sound.datas[sound.datasCount - 1].sourceid = source;
    sound.datas[sound.datasCount - 1].bufferid = buffer;
   sound. datas[sound.datasCount - 1].buffer = NULL;
    sound.datas[sound.datasCount - 1].name = strdup(filename);

    return source;
}

void deleteSound(unsigned int id) {
    for (int i = 0; i < sound.datasCount; ++i) {
        if (sound.datas[i].sourceid == id) {
            alDeleteSources(1, &sound.datas[i].sourceid);
            alDeleteBuffers(1, &sound.datas[i].bufferid);
            free(sound.datas[i].name);
            // Remove from datas array
            memmove(&sound.datas[i], &sound.datas[i + 1], (sound.datasCount - i - 1) * sizeof(Data));
            sound.datasCount--;
            sound.datas = (Data *)realloc(sound.datas, sound.datasCount * sizeof(Data));
            return;
        }
    }
    fprintf(stderr, "Sound ID not found: %u\n", id);
}

void playSound(unsigned int id) {
    alSourcePlay(id);
}

void playSoundWithPosition(unsigned int id, int positionX, int positionY, int positionZ, float pitch) {
    alSource3f(id, AL_POSITION, (float)positionX, (float)positionY, (float)positionZ);
    alSourcef(id, AL_PITCH, pitch);
    alSourcePlay(id);
}

void stopSound(unsigned int id) {
    alSourceStop(id);
}

void playSoundLoop(unsigned int id) {
    alSourcei(id, AL_LOOPING, AL_TRUE);  // Set looping flag to true
    alSourcePlay(id);  // Play the sound
}

void setListener(int positionX, int positionY, int positionZ, int orientationX, int orientationY, int orientationZ) {
    float position[] = {(float)positionX, (float)positionY, (float)positionZ};
    float orientation[] = {(float)orientationX, (float)orientationY, (float)orientationZ, 0.0f, 1.0f, 0.0f}; // Assuming up vector
    alListenerfv(AL_POSITION, position);
    alListenerfv(AL_ORIENTATION, orientation);
}

 void freeSound() {
    if (sound.sound1) {
        alDeleteBuffers(1, &sound.sound1);
        sound.sound1 = 0;
    }
    if (sound.sound2) {
        alDeleteBuffers(1, &sound.sound2);
        sound.sound2 = 0;
    }

    if (sound.device) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(sound.context);
        alcCloseDevice(sound.device);
        sound.device = NULL;
        sound.context = NULL;
    }

}

char *loadWAV(const char *fn, int *chan, int *samplerate, int *bps, int *size) {
     char buffer[4];
    FILE *in = fopen(fn, "rb");
    if (!in) {
        printf("Failed to open file: %s\n", fn);
        return NULL;
    }

    // Lire le marqueur "RIFF"
    fread(buffer, 1, 4, in);
    if (strncmp(buffer, "RIFF", 4) != 0) {
        printf("Not a valid WAV file!\n");
        fclose(in);
        return NULL;
    }

    // Ignorer certains octets inutiles
    fread(buffer, 1, 4, in); // Taille du fichier
    fread(buffer, 1, 4, in); // Format "WAVE"

    // Lire le sous-chunk "fmt "
    fread(buffer, 1, 4, in); // Sous-chunk1 ID
    fread(buffer, 1, 4, in); // Sous-chunk1 taille
    fread(buffer, 1, 2, in); // Format audio
    fread(buffer, 1, 2, in); // Nombre de canaux
    *chan = convertToInt(buffer, 2);

    fread(buffer, 1, 4, in); // Fréquence d'échantillonnage
    *samplerate = convertToInt(buffer, 4);

    fread(buffer, 1, 4, in); // Byte rate (ignorer)
    fread(buffer, 1, 2, in); // Block align (ignorer)
    fread(buffer, 1, 2, in); // Bits per sample
    *bps = convertToInt(buffer, 2);

    // Lire le sous-chunk "data"
    fread(buffer, 1, 4, in); // Sous-chunk2 ID "data"
    fread(buffer, 1, 4, in); // Taille des données
    *size = convertToInt(buffer, 4);

    // Allouer de la mémoire pour les données audio
    char *soundData = (char *)malloc(*size);
    if (!soundData) {
        printf("Failed to allocate memory for sound data!\n");
        fclose(in);
        return NULL;
    }

    fread(soundData, 1, *size, in); // Lire les données audio
    fclose(in);

    return soundData;
}

int convertToInt(char *buffer, int len) {
    int result = 0;
    if (sound.isBigEndian) {
        for (int i = 0; i < len; i++) {
            result = (result << 8) | (unsigned char)buffer[i];
        }
    } else {
        for (int i = len - 1; i >= 0; i--) {
            result = (result << 8) | (unsigned char)buffer[i];
        }
    }
    return result;
}

int isBigEndian_() {
    int num = 1;
    return (*(char *)&num == 0);
}

