#include"APP_SERVEUR.h"
#include"entities/vehicule.h"
#include"entities/camera.h"
#include"tubes_anonymes.h"

 pthread_mutex_t carMutex = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t cameraMutex = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t roueMutex = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t carAIMutex = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t roueAIMutex = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t timerMutex = PTHREAD_MUTEX_INITIALIZER;
   
int sendCommand2(int pipeFd, void *command,size_t size) {
    if (write(pipeFd, command, size) < 0) {
        perror("Client : Erreur d'écriture dans le tube");
        return 0;  // Renvoie 0 en cas d'erreur
    }
    return 1;  // Renvoie 1 si tout s'est bien passé
}


void* communicationThread(void* args) {
   char command;

                       
        // Lire les commandes du client
          if (read(toServer[0], &command, sizeof(char)) > 0) {
            pthread_mutex_lock(&carMutex);
	    if(timer<=0)
	    {
	     updateCar(&cars[0], 0.016f); // 60 FPS
             controlCar(&cars[0], command);
             cars[0].rotationLineHUD=-cars[0].speed*5;
             }
            setPhysics();
   	    collisionExterior();
   	    collisionInterior();
   	    collisionBetweenCar_CARAI();
   	    
   	    checkPoints(20,1,30,cars[0].x,cars[0].y,cars[0].z);
   	    checkPoints(40,1,-40,cars[0].x,cars[0].y,cars[0].z);
   	    checkPoints(-40,1,30,cars[0].x,cars[0].y,cars[0].z);
   	    
   	    for(int i=0;i<SIZEAICAR;i++)
   	    {
   	    checkPointsAI(20,1,30,carsAI[i].x,carsAI[i].y,carsAI[i].z);
   	    checkPointsAI(40,1,-40,carsAI[i].x,carsAI[i].y,carsAI[i].z);
   	    checkPointsAI(-40,1,30,carsAI[i].x,carsAI[i].y,carsAI[i].z);
   	    }
   	    
            pthread_mutex_unlock(&carMutex);
              } 
              
                 if (read(toServer2[0], &command, sizeof(char)) > 0) {
          pthread_mutex_lock(&roueMutex);
	  if(timer<=0)
            rotationRoues( command,0.016f);
               pthread_mutex_unlock(&roueMutex);
              } 
              
              
                if (read(toServer3[0], &command, sizeof(char)) > 0) {
                pthread_mutex_lock(&cameraMutex);
            controlCamera(command);
            mouseScroll(command);
            pthread_mutex_unlock(&cameraMutex);
        }
        
           if (read(toServer4[0], &command, sizeof(char)) > 0) {
                pthread_mutex_lock(&carAIMutex);
                setPhysicsCarAI();
                if(timer<=0)
                  updateCarAI( 0.016f); // 60 FPS
                findTarget();
                collisionExteriorCarAI();
   	   	 collisionInteriorCarAI();
   	   	 collisionBetweenCarAI();
   	   	 
                pthread_mutex_unlock(&carAIMutex);
        }
        
             if (read(toServer5[0], &command, sizeof(char)) > 0) {
                pthread_mutex_lock(&roueAIMutex);
                if(timer<=0)
		  rotationRouesAI(0.016f);
                pthread_mutex_unlock(&roueAIMutex);
        }
        
          if (read(toServer6[0], &command, sizeof(char)) > 0) {
                pthread_mutex_lock(&timerMutex);
		 timer-=0.01f;
                pthread_mutex_unlock(&timerMutex);
        }
       
      
}

void* gameUpdateThread(void* args) {

 pthread_mutex_lock(&carMutex);
  if (!sendCommand2(toClient[1], cars, sizeof(Car))) {
            printf( "Erreur lors de l'envoi de l'état des voitures au client." );
        }
        
 pthread_mutex_unlock(&carMutex);
 
  pthread_mutex_lock(&roueMutex);
        if (!sendCommand2(toClient2[1], roues, sizeof(Roue) * 4)) {
         pthread_mutex_lock(&roueMutex);
  
    
        }
               pthread_mutex_unlock(&roueMutex);
        
          pthread_mutex_lock(&cameraMutex);
     if (!sendCommand2(toClient3[1], &cam, sizeof(Camera))) {
            printf("Erreur lors de l'envoi de l'état de la caméra au client." );
        }
               pthread_mutex_unlock(&cameraMutex);
               
            
        
          pthread_mutex_lock(&carAIMutex);
     if (!sendCommand2(toClient4[1], &carsAI, sizeof(Car)*10)) {
            printf("Erreur lors de l'envoi de l'état de la caméra au client." );
        }
               pthread_mutex_unlock(&carAIMutex);
               
              pthread_mutex_lock(&roueAIMutex);
     if (!sendCommand2(toClient5[1], &rouesAI, sizeof(Roue)*4)) {
            printf("Erreur lors de l'envoi de l'état de la caméra au client." );
        }
               pthread_mutex_unlock(&roueAIMutex);
               
      pthread_mutex_lock(&timerMutex);
     if (!sendCommand2(toClient6[1], &timer, sizeof(int))) {
            printf("Erreur lors de l'envoi de l'état de la caméra au client." );
        }
               pthread_mutex_unlock(&timerMutex);
}



// Fonction serveur
void serverProcess(int toClient[2],int toServer[2],int toClient2[2],int toServer2[2],
int toClient3[2],int toServer3[2],int toClient4[2],int toServer4[2],int toClient5[2],int toServer5[2],
int toClient6[2],int toServer6[2]) {
    close(toClient[0]); // Ferme la lecture côté client
    close(toServer[1]); // Ferme l'écriture côté client
    close(toClient2[0]); // Ferme la lecture côté client
    close(toServer2[1]); // Ferme l'écriture côté client
    close(toClient3[0]); // Ferme la lecture côté client
    close(toServer3[1]); // Ferme l'écriture côté client
    close(toClient4[0]); // Ferme la lecture côté client
    close(toServer4[1]); // Ferme l'écriture côté client
    close(toClient5[0]); // Ferme la lecture côté client
    close(toServer5[1]); // Ferme l'écriture côté client
    close(toClient6[0]); // Ferme la lecture côté client
    close(toServer6[1]); // Ferme l'écriture côté client
    
   initialiseCar();
   initialiseCamera();
   initialiseCarsAI();
   initialiseTimer();

   char command;

        pthread_t commThread, updateThread;

    
    while (1) {
       
        pthread_create(&commThread, NULL, communicationThread, &command);
        // Envoyer l'état du jeu aux clients
        pthread_create(&updateThread, NULL, gameUpdateThread, &command);
        
        
    pthread_join(commThread, NULL);
    pthread_join(updateThread, NULL);

    // Détruire les mutex après usage
   

     //  usleep(100); // Pause pour limiter à ~60 FPS
}
    pthread_mutex_destroy(&carMutex);
    pthread_mutex_destroy(&cameraMutex);
    pthread_mutex_destroy(&roueMutex);
    pthread_mutex_destroy(&carAIMutex);
    pthread_mutex_destroy(&roueAIMutex);
    pthread_mutex_destroy(&timerMutex);

}

