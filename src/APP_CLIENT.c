#include"APP_CLIENT.h"
#include"entities/vehicule.h"
#include"entities/raceTrack.h"
#include"entities/grid.h"
#include"entities/camera.h"
#include"tubes_anonymes.h"

int WINDOWSWIDTH= 960;
int WINDOWSHEIGHT= 540;
int centerX,centerY;
int timer=0;
// Fonction de mise à jour côté client

pthread_mutex_t carMutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cameraMutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t roueMutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t carAIMutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t roueAIMutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t timerMutex2 = PTHREAD_MUTEX_INITIALIZER;

void read_client()
{
// Lire les données des tubes (non-bloquant recommandé)
    if (read(toClient[0], cars, sizeof(Car)) > 0) {
        // Traiter les données reçues pour les voitures
    }

    if (read(toClient2[0], roues, sizeof(Roue) * 4) > 0) {
        // Traiter les données reçues pour les roues
    }

    if (read(toClient3[0], &cam, sizeof(Camera)) > 0) {
        // Traiter les données reçues pour la caméra
    }
    
      if (read(toClient4[0], &carsAI, sizeof(Car)*10) > 0) {
        // Traiter les données reçues pour la caméra
    }
    
       if (read(toClient5[0], &rouesAI, sizeof(Roue)*4) > 0) {
        // Traiter les données reçues pour la caméra
    }
      if (read(toClient6[0], &timer, sizeof(int)) > 0) {
        // Traiter les données reçues pour la caméra
    }

}
     
int sendCommand_(int pipeFd, char command) {
    if (write(pipeFd, &command, sizeof(char)) < 0) {
        perror("Client : Erreur d'écriture dans le tube");
        return 0;  // Renvoie 0 en cas d'erreur
    }
    return 1;  // Renvoie 1 si tout s'est bien passé
}

void* communicationThread2(void* args) {

char command = ' '; // Commande par défaut : Stop

 pthread_mutex_lock(&carMutex2);
   if (sendCommand_(toServer[1], command))
        printf("Client : Commande envoyée à toServer : %c\n", command);

 pthread_mutex_unlock(&carMutex2);
 
  pthread_mutex_lock(&roueMutex2);
    if (sendCommand_(toServer2[1], command))
        printf("Client : Commande envoyée à toServer2 : %c\n", command);
 pthread_mutex_unlock(&roueMutex2);
 
   pthread_mutex_lock(&cameraMutex2);
    if (sendCommand_(toServer3[1], command))
        printf("Client : Commande envoyée à toServer3 : %c\n", command);
      pthread_mutex_unlock(&cameraMutex2); 
      
      
      pthread_mutex_lock(&carAIMutex2);
    if (sendCommand_(toServer4[1], command))
        printf("Client : Commande envoyée à toServer4 : %c\n", command);
      pthread_mutex_unlock(&carAIMutex2); 
      
      
     pthread_mutex_lock(&roueAIMutex2);
    if (sendCommand_(toServer5[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
      pthread_mutex_unlock(&roueAIMutex2); 
      
       
     pthread_mutex_lock(&timerMutex2);
    if (sendCommand_(toServer6[1], command))
        printf("Client : Commande envoyée à toServer6 : %c\n", command);
      pthread_mutex_unlock(&timerMutex2); 
      
  

}

void* gameUpdateThread2(void* args) {

pthread_mutex_lock(&carMutex2);
  if (read(toClient[0], cars, sizeof(Car)) > 0)
  {
     printf("Client : Position reçue : x = %.2f, z = %.2f\n", cars[0].x, cars[0].z);
     }
 pthread_mutex_unlock(&carMutex2);
 
     pthread_mutex_lock(&roueMutex2);
     if(read(toClient2[0], roues, sizeof(Roue) * 4) > 0)
            {
               printf("Client : Position reçue : x = %.2f, z = %.2f\n", cars[0].x, cars[0].z);
            }
          pthread_mutex_unlock(&roueMutex2);   
            
               pthread_mutex_lock(&cameraMutex2);
            if( read(toClient3[0], &cam, sizeof(Camera)) > 0) {
            
            printf("Client : Position reçue : x = %.2f, z = %.2f\n", cars[0].x, cars[0].z);
        }
             pthread_mutex_unlock(&cameraMutex2);
             
             pthread_mutex_lock(&carAIMutex2);
             
             if( read(toClient4[0], &carsAI, sizeof(Car)*10) > 0) {
            
            for(int i=0;i<SIZEAICAR;i++)
              printf("Client : Position reçue : x = %.2f, z = %.2f\n", carsAI[i].x, carsAI[i].z);
         
             }
            pthread_mutex_unlock(&carAIMutex2); 
            
              pthread_mutex_lock(&roueAIMutex2);
            if( read(toClient5[0], &rouesAI, sizeof(Roue)*4) > 0) {
            
            for(int i=0;i<SIZEROUESAI;i++)
              printf("Client : Position reçue : x = %.2f, z = %.2f\n", carsAI[i].x, carsAI[i].z);
         
             }
            pthread_mutex_unlock(&roueAIMutex2); 
            
            pthread_mutex_lock(&timerMutex2);
            if( read(toClient6[0], &timer, sizeof(int)) > 0) {
            
         
             }
            pthread_mutex_unlock(&timerMutex2); 
}

void updateClient() {

      char command = ' '; // Commande par défaut : Stop


      pthread_t commThread, updateThread;


      pthread_create(&commThread, NULL, communicationThread2, &command);
        // Envoyer l'état du jeu aux clients
      pthread_create(&updateThread, NULL, gameUpdateThread2, &command);
        
        
    pthread_join(commThread, NULL);
    pthread_join(updateThread, NULL);

    
    glutPostRedisplay();
         
    pthread_mutex_destroy(&carMutex2);
    pthread_mutex_destroy(&cameraMutex2);
    pthread_mutex_destroy(&roueMutex2);
    pthread_mutex_destroy(&carAIMutex2);
    pthread_mutex_destroy(&roueAIMutex2);
    pthread_mutex_destroy(&timerMutex2);
   
 //  glutTimerFunc(16, updateClient, 0); // Rappel pour le prochain frame
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);

    // Vérifier les erreurs OpenGL
    if (glGetError() != GL_NO_ERROR) {
        printf("Erreur : Position raster invalide.\n");
        return;
    }

    // Parcourir la chaîne et afficher chaque caractère
    for (const char* p = text; *p != '\0'; p++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
    }
   // glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void hud(const char* filename)
{
	glEnable(GL_TEXTURE_2D);
	if(hudTex==0)
	 hudTex=loadBMP_custom(filename);
	glPushMatrix();
	glTranslated(-0.68,-0.85,0);
	glScaled(0.2,0.17,0);
	glBindTexture(GL_TEXTURE_2D,hudTex);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	
	glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
	glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
	glTexCoord2i(1,0);glVertex3i(+1,+1,-1); 
	glTexCoord2i(0,0);glVertex3i(-1,+1,-1);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}

void hud2(const char* filename)
{
	glEnable(GL_TEXTURE_2D);
	if(hudTex2==0)
	 hudTex2=loadBMP_custom(filename);
	glPushMatrix();
	glTranslated(-0.75,-0.9,0);
	glRotatef(cars[0].rotationLineHUD,0,0,0.5);
	glTranslated(-0.025,0.0,0);
	glScaled(0.015,0.015,0);
	glBindTexture(GL_TEXTURE_2D,hudTex2);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	
	glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
	glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
	glTexCoord2i(1,0);glVertex3i(+1,+1,-1); 
	glTexCoord2i(0,0);glVertex3i(-1,+1,-1);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void hud3(const char* filename)
{
	glEnable(GL_TEXTURE_2D);
	if(hudTex3==0)
	 hudTex3=loadBMP_custom(filename);
	glPushMatrix();
	glTranslated(-0.65,0.3,0);
	glScaled(0.15,0.98,0);
	glBindTexture(GL_TEXTURE_2D,hudTex3);
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_QUADS);
	
	glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
	glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
	glTexCoord2i(1,0);glVertex3i(+1,+1,-1); 
	glTexCoord2i(0,0);glVertex3i(-1,+1,-1);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void hud4(const char* filename)
{
	glEnable(GL_TEXTURE_2D);
	if(hudTex4==0)
	 hudTex4=loadBMP_custom(filename);
	glPushMatrix();
	glTranslated(0.75,-0.15,0);
	glScaled(0.15,0.75,0);
	glBindTexture(GL_TEXTURE_2D,hudTex4);
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_QUADS);
	
	glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
	glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
	glTexCoord2i(1,0);glVertex3i(+1,+1,-1); 
	glTexCoord2i(0,0);glVertex3i(-1,+1,-1);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

char* int2str(int x) {
    // Allouer un tampon suffisamment grand pour contenir la représentation entière de x
    // avec espace pour le signe et le caractère nul de fin.
    char* buffer = (char*)malloc(12 * sizeof(char)); // Assure un espace pour un entier 32 bits
    if (buffer != NULL) {
        sprintf(buffer, "%d", x);
    }
    return buffer;
}

char* concat(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char* result = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    if (result != NULL) {
        strcpy(result, str1);
        strcat(result, str2);
    }
    return result;
}


void drawHud()
{

	    
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	hud2("data/HUD/aiguille.bmp");	
	hud("data/HUD/tableaubord2.bmp");	
	
	glDisable(GL_DEPTH_TEST);
	
	glEnable(GL_DEPTH_TEST);
	
	char* speedStr = int2str(cars[0].speed*20);
	char* speedStr2 = int2str(cars[0].speed*-20);
	char* speedStr3 = int2str(cars[0].points);
	char* speedTxt = concat("VITESSE: ", speedStr);
	char* speedTxt2 = concat("VITESSE: ", speedStr2);
	char* speedTxt3 = concat("POINTS: ", speedStr3);

	
	drawText(-0.8,0.9,"CARPLAYER:");
	if(cars[0].speed>0)
	 drawText(-0.8,0.8,speedTxt);
	else if(cars[0].speed<0)
	 drawText(-0.8,0.8,speedTxt2); 
	else
	  drawText(-0.8,0.8,speedTxt2); 
	  
	drawText(-0.8,0.7,speedTxt3);
	
	drawText(-0.8,0.5,"CARPLAYERAI:");
	
       for(int i=0;i<SIZEAICAR;i++)
	{
	char* speedStr4 = int2str(carsAI[i].points);
	char* speedTxt4 = concat("CARAI POINTS: ", speedStr4);

	drawText(-0.8,0.55-(i*0.2),speedTxt4);
	}
	

	 for(int i=0;i<SIZEAICAR;i++)
	 {
	 char* speedStr5 = int2str(carsAI[i].speed);
	 char* speedTxt5 = concat("CARAI VITESSE: ", speedStr5);
	  drawText(0.6,0.55-(i*0.2),speedTxt5); 
	 }
	
	
	 char* timeStr = int2str(timer/100);
	 char* timeTxt = concat("START GAME INTO: ", timeStr);
	 
	if(timer>0)
  	{
	drawText(-0.15,0.3,timeTxt);
	}
	

     for(int i=0;i<SIZEAICAR;i++)
     {
	if( cars[0].points>=15000 && carsAI[i].points<15000)
	{
		drawText(0.8,0.4,"YOU WIN!!!! "); 
	}
	else
	{
	  if( cars[0].points<15000 && carsAI[i].points>=15000)
	  {
			drawText(0.8,0.4,"YOU LOSE!!!! "); 
	  }
	 }
   
 	}
	
	hud3("data/HUD/fond_.bmp");
	hud4("data/HUD/fond_.bmp");
		
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
}

void reshape(int w, int h) {
    
    WINDOWSWIDTH=w;
    WINDOWSHEIGHT=h;
    
    centerX=WINDOWSWIDTH/2;
    centerY=WINDOWSHEIGHT/2;
    glViewport(0, 0, w, h); // Définit la zone d'affichage
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(cam.fov, (double)w / (double)h, 0.1, 500.0); // Projection perspective
    glMatrixMode(GL_MODELVIEW);
    //glEnable(GL_DEPTH_TEST); // Activer le test de profondeur
}

// Fonction pour afficher la scène avec OpenGL
void display() {

   updateClient();
       // Transformation de la caméra
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();
    
  //  reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)); 
  /* gluLookAt(7.0, 5.0, 10.0, // Position de la caméra
              0.0, 0.0, 0.0, // Point regardé
              0.0, 1.0, 0.0); // Orientation "haut" de la caméra*/
    updateCamera(cars[0].x,cars[0].y,cars[0].z);
              
    glPushMatrix();
    drawGrid();
    glPopMatrix();
    
    glPushMatrix();
    drawTrack();
    drawPlane(175);
    glScaled(0.5f,0.025f,0.5f);
    drawCube();
    glScaled(0.4,1,0.4);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    drawCity();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(cars[0].x, cars[0].y, cars[0].z);
    glRotatef(cars[0].rotation,0,0.5,0);

    drawCar(cars[0]);
    
   for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-1.2f , -0.2f, -0.9f+(i * 1.9f));
        glRotatef(roues[i].rot, 0.0f, 0.0f, 0.5f);
        drawRoues();
        glPopMatrix();
    }
   
      for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(1.2f , -0.2f, -0.9f+(i * 1.9f));
        glRotatef(roues[i].rot, 0.0f, 0.0f, 0.5f);
        drawRoues();
        glPopMatrix();
    }

    
    glPopMatrix();
    
      for(int i=0;i<SIZEAICAR;i++)
    {
    glPushMatrix(); 
    glTranslatef(carsAI[i].x, carsAI[i].y, carsAI[i].z);
    glRotatef(carsAI[i].rotation*180/M_PI,0,0.5,0);
    drawCar(carsAI[i]);
    
     for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-1.2f , -0.2f, -0.9f+(i * 1.9f));
        glRotatef(rouesAI[i].rot, 0.0f, 0.0f, 0.5f);
        drawRoues();
        glPopMatrix();
    }
   
      for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(1.2f , -0.2f, -0.9f+(i * 1.9f));
        glRotatef(rouesAI[i].rot, 0.0f, 0.0f, 0.5f);
        drawRoues();
        glPopMatrix();
    }
    
    glPopMatrix();
    }
     
     drawHud();

    glutPostRedisplay();
    glutSwapBuffers();
}




void setupLighting() {
    glEnable(GL_LIGHTING);   // Activer l'éclairage
    glEnable(GL_LIGHT0);     // Activer une lumière (LIGHT0)

    // Définir les propriétés de la lumière
    GLfloat lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };  // Direction (w = 0 pour directionnelle)
    GLfloat lightAmbient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };  // Lumière ambiante
    GLfloat lightDiffuse[]  = { 0.8f, 0.8f, 0.8f, 1.0f };  // Lumière diffuse
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Lumière spéculaire

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Activer le matériau par défaut
    GLfloat materialAmbient[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat materialDiffuse[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat materialShininess  = 50.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT,  materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);
}

void init()
{
glClearColor(0.8,0.8,0.9,1.0);
glEnable(GL_DEPTH_TEST); // Activer le test de profondeur
glEnable(GL_COLOR_MATERIAL);
glShadeModel(GL_SMOOTH); // Modèle de lissage pour les ombrages
setupLighting();

initialiseCity();
initialiseCamera();
initialiseCar();
initialiseCarsAI();
initialiseTimer();

 
generateTrack();
}



void mouseMove(int mx,int my)
{
      char command = ' '; // Commande par défaut : Stop
	
	if(mi==1)
	{
        if(mx>(centerX))
        {
	command='+';
	}
	 if(mx<(centerX))
        {
	command='-';
	}
	}
	
	
	if(mi2==1)
	{
        if(my>(centerY))
        {
	command='*';
	}
	 if(my<(centerY))
        {
	command='/';
	}
	}
	

	 
    

 if (sendCommand_(toServer[1], command))
        printf("Client : Commande envoyée à toServer : %c\n", command);

    if (sendCommand_(toServer2[1], command))
        printf("Client : Commande envoyée à toServer2 : %c\n", command);

    if (sendCommand_(toServer3[1], command))
        printf("Client : Commande envoyée à toServer3 : %c\n", command);
        
    if (sendCommand_(toServer4[1], command))
        printf("Client : Commande envoyée à toServer4 : %c\n", command);
        
   if (sendCommand_(toServer5[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
        
    if (sendCommand_(toServer6[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
        
    read_client();

    // Re-rendre l'écran
    glutPostRedisplay();
		
}


void mouseWheel(int button, int state, int x, int y) {

  char command = ' '; // Commande par défaut : Stop
   
    if (button == 3 || button == 4) {  // Si la molette a été utilisée (pour FreeGLUT)
        if (state == GLUT_DOWN) {
            if (button == 3) {  // Molette vers le haut
                command='8';
                
            }
            if (button == 4) {  // Molette vers le bas
              command='9';
            }
            }
            }
                printf("FOV: %f\n", cam.fov);
            
                glMatrixMode(GL_PROJECTION);
		 glLoadIdentity();
		 gluPerspective(cam.fov, (double)WINDOWSWIDTH / (double)WINDOWSHEIGHT, 0.1, 500.0); // Projection perspective
		 glMatrixMode(GL_MODELVIEW);
    
                 glutPostRedisplay();  // Demander un rafraîchissement de l'écran
    
 
    
     if (sendCommand_(toServer[1], command))
        printf("Client : Commande envoyée à toServer : %c\n", command);

    if (sendCommand_(toServer2[1], command))
        printf("Client : Commande envoyée à toServer2 : %c\n", command);

    if (sendCommand_(toServer3[1], command))
        printf("Client : Commande envoyée à toServer3 : %c\n", command);
        
     if (sendCommand_(toServer4[1], command))
        printf("Client : Commande envoyée à toServer4 : %c\n", command);
        
     if (sendCommand_(toServer5[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
        
      if (sendCommand_(toServer6[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);

    read_client();

    // Re-rendre l'écran
    glutPostRedisplay();
 	
 	
}

void mouseState(int button, int state, int x, int y)
{
  mouseWheel(button,state,x,y);
  mouse( button,  state,  x,  y);
	
}

void handleSpecialKey(int key, int x, int y)
{
char command = ' '; // Commande par défaut : Stop

    switch (key) {
    case GLUT_KEY_UP:
     command='W';
         break; // Haut
       case GLUT_KEY_DOWN:
        command = 'S';
         break; // Haut
       case GLUT_KEY_RIGHT:
        command = 'A';
         break; // Haut
       case GLUT_KEY_LEFT:
        command = 'D';
         break; // Haut
 
       default:
            printf("Client : Touche non reconnue : %c\n", key);
            return; // Ne rien faire pour les touches non reconnues
    }
    
    
     if (sendCommand_(toServer[1], command))
        printf("Client : Commande envoyée à toServer : %c\n", command);

    if (sendCommand_(toServer2[1], command))
        printf("Client : Commande envoyée à toServer2 : %c\n", command);

    if (sendCommand_(toServer3[1], command))
        printf("Client : Commande envoyée à toServer3 : %c\n", command);
    
     if (sendCommand_(toServer4[1], command))
        printf("Client : Commande envoyée à toServer4 : %c\n", command);
        
     if (sendCommand_(toServer5[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
        
       if (sendCommand_(toServer6[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
	
	read_client();

  
    // Re-rendre l'écran
    glutPostRedisplay();
}



void handleSpecialKeyUp(int key, int x, int y)
{
char command = ' '; // Commande par défaut : Stop

    switch (key) {
    case GLUT_KEY_UP:
     command='1';
         break; // Haut
       case GLUT_KEY_DOWN:
        command = '2';
         break; // Haut
       case GLUT_KEY_RIGHT:
        command = '3';
         break; // Haut
       case GLUT_KEY_LEFT:
        command = '4';
         break; // Haut
         
       default:
            printf("Client : Touche non reconnue : %c\n", key);
            return; // Ne rien faire pour les touches non reconnues
    }
    
 
    
     if (sendCommand_(toServer[1], command))
        printf("Client : Commande envoyée à toServer : %c\n", command);

    if (sendCommand_(toServer2[1], command))
        printf("Client : Commande envoyée à toServer2 : %c\n", command);

    if (sendCommand_(toServer3[1], command))
        printf("Client : Commande envoyée à toServer3 : %c\n", command);
        
      if (sendCommand_(toServer4[1], command))
        printf("Client : Commande envoyée à toServer4 : %c\n", command);
        
       if (sendCommand_(toServer5[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
        
       if (sendCommand_(toServer6[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);


	read_client();

 
    // Re-rendre l'écran
    glutPostRedisplay();
 
}

void handleKeyPress(unsigned char key, int x, int y) {


    char command = ' '; // Commande par défaut : Stop
    
    switch (key) {
        case 'w':
        command = 'W';
         break; // Haut
       case 's':
        command = 'S';
         break; // Haut
       case 'a':
        command = 'A';
         break; // Haut
       case 'd':
        command = 'D';
         break; // Haut
        case 'q': 
        command = 'Q';
         break; // Quitter
        case 32:
          command='E';
          break;
        default:
            printf("Client : Touche non reconnue : %c\n", key);
            return; // Ne rien faire pour les touches non reconnues
    }
    

    
     if (sendCommand_(toServer[1], command))
        printf("Client : Commande envoyée à toServer : %c\n", command);

    if (sendCommand_(toServer2[1], command))
        printf("Client : Commande envoyée à toServer2 : %c\n", command);

    if (sendCommand_(toServer3[1], command))
        printf("Client : Commande envoyée à toServer3 : %c\n", command);
        
       if (sendCommand_(toServer4[1], command))
        printf("Client : Commande envoyée à toServer4 : %c\n", command);
        
       if (sendCommand_(toServer5[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
        
       if (sendCommand_(toServer6[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
     
     
      read_client();
    
    // Re-rendre l'écran
    glutPostRedisplay();

    if (command == 'Q') {
        close(toClient[1]);
        close(toServer[0]);
        close(toClient2[1]); // Ferme l'écriture côté serveur
    	close(toServer2[0]); // Ferme la lecture côté serveur
    	close(toClient3[1]); // Ferme l'écriture côté serveur
    	close(toServer3[0]); // Ferme la lecture côté serveur
        exit(0);
        }
}


void handleKeyPressUp(unsigned char key, int x, int y) {


    char command = ' '; // Commande par défaut : Stop

    switch (key) {
        case 'w':
        command = '1';
         break; // Haut
       case 's':
        command = '2';
         break; // Haut
       case 'a':
        command = '3';
         break; // Haut
       case 'd':
        command = '4';
         break; // Haut
 
        default:
            printf("Client : Touche non reconnue : %c\n", key);
            return; // Ne rien faire pour les touches non reconnues
    }
    
  
    
     if (sendCommand_(toServer[1], command))
        printf("Client : Commande envoyée à toServer : %c\n", command);

    if (sendCommand_(toServer2[1], command))
        printf("Client : Commande envoyée à toServer2 : %c\n", command);

    if (sendCommand_(toServer3[1], command))
        printf("Client : Commande envoyée à toServer3 : %c\n", command);
     
      if (sendCommand_(toServer4[1], command))
        printf("Client : Commande envoyée à toServer4 : %c\n", command);
        
       if (sendCommand_(toServer5[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);
        
        if (sendCommand_(toServer6[1], command))
        printf("Client : Commande envoyée à toServer5 : %c\n", command);

      read_client();

   
        glutPostRedisplay();


}


// Fonction principale pour le processus client
void clientProcess(int toClient[2],int toServer[2],int toClient2[2],int toServer2[2],
int toClient3[2],int toServer3[2],int toClient4[2],int toServer4[2],int toClient5[2],int toServer5[2],
int toClient6[2],int toServer6[2]) {
    close(toClient[1]); // Ferme l'écriture côté serveur
    close(toServer[0]); // Ferme la lecture côté serveur
    close(toClient2[1]); // Ferme l'écriture côté serveur
    close(toServer2[0]); // Ferme la lecture côté serveur
    close(toClient3[1]); // Ferme l'écriture côté serveur
    close(toServer3[0]); // Ferme la lecture côté serveur
    close(toClient4[1]); // Ferme l'écriture côté serveur
    close(toServer4[0]); // Ferme la lecture côté serveur
    close(toClient5[1]); // Ferme l'écriture côté serveur
    close(toServer5[0]); // Ferme la lecture côté serveur
    close(toClient6[1]); // Ferme l'écriture côté serveur
    close(toServer6[0]); // Ferme la lecture côté serveur
    // Initialisation de GLUT et OpenGL
    int argc = 1;
    char *argv[1] = {(char *)"race_game"};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize(WINDOWSWIDTH, WINDOWSHEIGHT);
    glutCreateWindow("Car Game OpenGL - Tubes Anonymes!");
    init();
	
    // Définition des callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyPressUp);
    glutSpecialFunc(handleSpecialKey);
    glutSpecialUpFunc(handleSpecialKeyUp);

    glutMouseFunc(mouseState);
    glutMotionFunc(mouseMove);

    // Lancer la boucle principale
    glutMainLoop();
}

