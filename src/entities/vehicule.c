#include"vehicule.h"


void initialiseTimer()
{
srand((unsigned int)time(0)); // Conversion classique en C
timer=1000;
finishedGame=0;
}

void initialiseCar()
{
    srand((unsigned int)time(NULL));

    cars[0].x = 5.0f;
    cars[0].y = 1.7f;
    cars[0].z = 30.0f;
    cars[0].speed=0.0f;
    cars[0].maxSpeed=rand() % 15 + 8;
    cars[0].rotation=0.0f;
    cars[0].frein=0.2f;
    cars[0].acc=0.4f;
    cars[0].dec=0.15f;
    cars[0].turnSpeed=7.0f;
    cars[0].points=0;
    
    for(int i=0;i<COLORCAR;i++)
    {
    cars[0].colorCarRandomR[i]=random_float(0.01f, 0.99f);
    cars[0].colorCarRandomG[i]=random_float(0.01f, 0.99f);
    cars[0].colorCarRandomB[i]=random_float(0.01f, 0.99f);
    }
    
   for(int i=0;i<SIZEROUES;i++) 
   {
    roues[i].rot_=0;
    roues[i].rot=0;
    }
}

void initialiseCarsAI()
{
for(int i=0;i<SIZEAICAR;i++)
{
 carsAI[i].x=-5+(i*4);
 carsAI[i].y=2.0f;
 carsAI[i].z=30.0f+(i*3);
 carsAI[i].rotation=0.0f;
 carsAI[i].speed=rand() % 15 + 5;
 carsAI[i].nn=0;
 carsAI[i].points=0;
 carsAI[i].deviation=0;
 
 for(int j=0;j<COLORCAR;j++)
 {
  carsAI[i].colorCarRandomR[j]=random_float(0.01f, 0.99f);
  carsAI[i].colorCarRandomG[j]=random_float(0.01f, 0.99f);
  carsAI[i].colorCarRandomB[j]=random_float(0.01f, 0.99f);
 }
    
 }
 
  for(int i=0;i<SIZEROUESAI;i++) 
    rouesAI[i].rot=0;
   
}

void setPhysics()
{
cars[0].y-=0.01f;
if(cars[0].y<0.7f)
{
cars[0].y=0.7f;
}
}

void setPhysicsCarAI()
{
for(int i=0;i<SIZEAICAR;i++)
{
 carsAI[i].y-=0.05f;
 if(carsAI[i].y<0.7f)
{
carsAI[i].y=0.7f;
}
}
}


void checkPoints(float x,float y,float z)
{
	float dist=sqrt(cars[0].x-x)*(cars[0].x-x)+(cars[0].y-y)*(cars[0].y-y)+(cars[0].z-z)*(cars[0].z-z);
	
	if(dist<10)
	{
		cars[0].points+=5;
	}
}

void checkPointsAI(float x,float y,float z)
{
  for(int i=0;i<SIZEAICAR;i++)
      {
	float dist=sqrt(carsAI[i].x-x)*(carsAI[i].x-x)+(carsAI[i].y-y)*(carsAI[i].y-y)+(carsAI[i].z-z)*(carsAI[i].z-z);
	if(dist<10)
	{
    
	
		carsAI[i].points+=5;
	}
	}
}


void drawCheckPoints(float x, float y, float z,float rot,float r,float g,float b)
{
glPushMatrix();
glColor3f(r,g,b);
glTranslated(x,y,z);
glRotated(rot,0,0.5,0);
glScaled(1,1,1);
glutSolidTeapot(3);
glPopMatrix();	   	 
}

void resetCar(char command)
{
	
	
	if(cars[0].points>=15000)
	{
		finishedGame=0;
	}
 

 
 
 if(command=='E' && timer>0 && finishedGame==1)
 {
 	finishedGame=0;
 }
	
    if( finishedGame==0)
		 timer-=0.1f;
		
  else if(finishedGame==1)
 {

   timer=800;
   initialiseCar();
   setPhysics();
   
   }
  }
   
   
 void resetCarAI(char command)
 {
 
 	for(int i=0;i<SIZEAICAR;i++)
	{
	if(carsAI[i].points>=15000)
	{
		finishedGame=1;

	}
     }
      
 if(command=='E' && timer>0 && finishedGame==1)
 {
 	finishedGame=0;
 }
	
    if( finishedGame==0)
		 timer-=0.1f;
		 
    else if(finishedGame==1)
 {
     
        timer=800;
        initialiseCarsAI();
        setPhysicsCarAI();

  	
  }
  	
  	

}


int checkCollision(float carMinX,float carMinY,float carMinZ, float carMaxX,float carMaxY,float carMaxZ, float cubeMinX,float cubeMinY,float cubeMinZ, float cubeMaxX,float cubeMaxY,float cubeMaxZ) {
    return (carMinX <= cubeMaxX && carMaxX >= cubeMinX) &&
           (carMinY <= cubeMaxY && carMaxY >= cubeMinY) &&
           (carMinZ <= cubeMaxZ && carMaxZ >= cubeMinZ);
}

int checkCollisionAABB(float x1_min, float x1_max, float y1_min, float y1_max,float z1_min, float z1_max,
                       float x2_min, float x2_max, float y2_min, float y2_max,float z2_min, float z2_max) {
    return (x1_min < x2_max && x1_max > x2_min &&
            y1_min < y2_max && y1_max > y2_min &&
            z1_min < z2_max && z1_max > z2_min );
}

void collisionBetweenCar_CARAI()
{
for (int i = 0; i < SIZECAR; i++) {
    for (int j = i + 1; j < SIZEAICAR; j++) {
     if(checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, 45,0,-50, 50,10,50)==0
      && (checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -50,0,-50, -45,10,50)==0
      && checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -40,0,50, 40,15,52)==0
      && checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -40,0,-52, 40,15,-50)==0
      
      && checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, 15,0,-20, 20,10,20)==0
      && checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -20,0,-20, -15,10,20)==0
      && checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -10,0,15, 10,15,20)==0
      && checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -10,0,-20, 10,15,-15)==0))
      {
        if (checkCollisionAABB(cars[i].x-2, cars[i].x+2, 
                               cars[i].y-2, cars[i].y+2,
                               cars[i].z-2, cars[i].z+2, 
                               carsAI[j].x-2, carsAI[j].x+2, 
                               carsAI[j].y-2, carsAI[j].y+2,
                               carsAI[j].z-2, carsAI[j].z+2)) {
                               
                               cars[i].x-=0.1f;
                               cars[i].z-=0.1f;
                               carsAI[j].x+=0.1f;
                               carsAI[j].z+=0.1f;
                               
                               cars[i].points-=10;
            // Collision détectée entre car[i] et car[j]
        }
       }
    }
}
}

void collisionBetweenCarAI()
{
for (int i = 0; i < SIZEAICAR; i++) {
    for (int j = i + 1; j < SIZEAICAR; j++) {
        if (checkCollisionAABB(carsAI[i].x-2, carsAI[i].x+2, 
                               carsAI[i].y-2, carsAI[i].y+2,
                               carsAI[i].z-2, carsAI[i].z+2, 
                               carsAI[j].x-2, carsAI[j].x+2, 
                               carsAI[j].y-2, carsAI[j].y+2,
                               carsAI[j].z-2, carsAI[j].z+2)) {
                               
                               carsAI[i].x-=0.1f;
                               carsAI[i].z-=0.1f;
                               carsAI[j].x+=0.1f;
                               carsAI[j].z+=0.1f;
                               
                               carsAI[i].points-=10;
                               
            // Collision détectée entre car[i] et car[j]
        }
    }
}
}

void collisionExterior()
{
   if(checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, 45,0,-50, 50,10,50)) {
	    cars[0].x-=5.0f;
	    cars[0].points-=10;
	}
	
 	if(checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -50,0,-50, -45,10,50)) {
	     cars[0].x-=-5.0f;
	     cars[0].points-=10;
	}
	if(checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -40,0,50, 40,15,52)) {
	   cars[0].z-=5.0f;
	   cars[0].points-=10;
	}
	if(checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -40,0,-52, 40,15,-50)) {
	    cars[0].z-=-5.0f;
	    cars[0].points-=10;
	}
	   
}

void collisionInterior()
{
   if(checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, 15,0,-20, 20,10,20)) {
	    cars[0].x-=-5.0f;
	    cars[0].points-=10;
	}
	
 	if(checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -20,0,-20, -15,10,20)) {
	      cars[0].x-=5.0f;
	      cars[0].points-=10;
	}
	if(checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -10,0,15, 10,15,20)) {
	   cars[0].z-=-5.0f;
	   cars[0].points-=10;
	}
	if(checkCollision(cars[0].x-2,cars[0].y,cars[0].z-2, cars[0].x+2,cars[0].y,cars[0].z+2, -10,0,-20, 10,15,-15)) {
	    cars[0].z-=5.0f;
	    cars[0].points-=10;
	}
	
  
}

void collisionExteriorCarAI()
{
for(int i=0;i<SIZEAICAR;i++)
{
   if(checkCollision(carsAI[i].x-2,carsAI[i].y,cars[0].z-2, carsAI[i].x+2,carsAI[i].y,carsAI[i].z+2, 45,0,-50, 50,10,50)) {
       carsAI[i].x-=5.0f;
       carsAI[i].points-=10;
      
	}
	
 	if(checkCollision(carsAI[i].x-2,carsAI[i].y,carsAI[i].z-2, carsAI[i].x+2,carsAI[i].y,carsAI[i].z+2, -50,0,-50, -45,10,50)) {
	carsAI[i].x-=-5.0f;
	carsAI[i].points-=10;
          
	}
	if(checkCollision(carsAI[i].x-2,carsAI[i].y,carsAI[i].z-2,carsAI[i].x+2,carsAI[i].y,carsAI[i].z+2, -40,0,50, 40,15,52)) {

          carsAI[i].z-=5.0f;
          carsAI[i].points-=10;
	}
	if(checkCollision(carsAI[i].x-2,carsAI[i].y,carsAI[i].z-2, carsAI[i].x+2,carsAI[i].y,carsAI[i].z+2, -40,0,-52, 40,15,-50)) {
	
           carsAI[i].z-=-5.0f;
           carsAI[i].points-=10;
	}
}
	   
}

void collisionInteriorCarAI()
{
for(int i=0;i<SIZEAICAR;i++)
{
   if(checkCollision(carsAI[i].x-2,cars[i].y,carsAI[i].z-2, carsAI[i].x+2,carsAI[i].y,carsAI[i].z+2, 15,0,-20, 20,10,20)) {
	   carsAI[i].x-=-5.0f;
	   carsAI[i].points-=10;
	}
	
 	if(checkCollision(carsAI[i].x-2,cars[i].y,carsAI[i].z-2, carsAI[i].x+2,carsAI[i].y,carsAI[i].z+2, -20,0,-20, -15,10,20)) {
	      carsAI[i].x-=5.0f;
	      carsAI[i].points-=10;
	}
	if(checkCollision(carsAI[i].x-2,carsAI[i].y,carsAI[i].z-2, carsAI[i].x+2,carsAI[i].y,carsAI[i].z+2, -10,0,15, 10,15,20)) {
	  carsAI[i].z-=-5.0f;
	  carsAI[i].points-=10;
	}
	if(checkCollision(carsAI[i].x-2,carsAI[i].y,carsAI[i].z-2, carsAI[i].x+2,carsAI[i].y,carsAI[i].z+2, -10,0,-20, 10,15,-15)) {
	     carsAI[i].z-=5.0f;
	     carsAI[i].points-=10;
	}
}
  
}

void rotationRoues(char command,float deltaTime)
{
for(int i=0;i<SIZEROUES;i++)
{
if(command=='W')
{
roues[i].rot_=1;
}

else if(command=='S')
{
roues[i].rot_=1;
}

if(command=='1' || command=='2')
{
roues[i].rot_=0;
}

if(roues[i].rot_==1)
{
 roues[i].rot+=100.0f*deltaTime;
 }
 }
}

void rotationRouesAI(float deltaTime)
{
for(int i=0;i<SIZEROUESAI;i++)
{
for(int j=0;j<SIZEAICAR;j++)
{
if(carsAI[j].speed>0.2f)
{
  rouesAI[i].rot+=100.0f*deltaTime;
}

}
}
}


void drawRoues()
{
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glScaled(1,1,1);
    glutSolidTorus(0.5, 0.05, 10, 20);
    glPopMatrix();
    
}


void findTarget()
{
for(int i=0;i<SIZEAICAR;i++)
{
    float tx=points[carsAI[i].nn][0];
    float ty=points[carsAI[i].nn][1];
    
     if (carsAI[i].deviation == 0) { // Générer la déviation si elle n'est pas encore définie
            int direction = (rand() % 2 == 0) ? -1 : 1; // -1 = gauche, 1 = droite
            carsAI[i].deviation = direction * 2.0f;     // Déviation fixe (2 unités, ajustez si nécessaire)
        }

        // Ajoutez la déviation à la position cible
        float angleToTarget = atan2(ty - carsAI[i].z, tx - carsAI[i].x);
        float offsetX = carsAI[i].deviation * cos(angleToTarget + M_PI_2);
        float offsetY = carsAI[i].deviation * sin(angleToTarget + M_PI_2);
        
         float adjustedTx = tx + offsetX;
         float adjustedTy = ty + offsetY;
     
    float beta = carsAI[i].rotation - atan2(-adjustedTy + carsAI[i].z, adjustedTx - carsAI[i].x);
    
    if (sin(beta)<0) carsAI[i].rotation+=0.005*carsAI[i].speed; else carsAI[i].rotation-=0.005*carsAI[i].speed;
   
        
    if ((carsAI[i].x-tx)*(carsAI[i].x-tx)+(carsAI[i].z-ty)*(carsAI[i].z-ty)<5*5)     
    carsAI[i].nn=(carsAI[i].nn+1)%NUM;
    carsAI[i].deviation = 0;  
    }
}


void updateCar(Car *car, float deltaTime) {
    car->x += cos(-car->rotation*M_PI/180) * car->speed*deltaTime;
    car->z += sin(-car->rotation*M_PI/180) * car->speed*deltaTime;
}

void updateCarAI(float deltaTime) {

for(int i=0;i<SIZEAICAR;i++)
{
    carsAI[i].x += cos(-carsAI[i].rotation) * carsAI[i].speed*deltaTime;
    carsAI[i].z += sin(-carsAI[i].rotation) * carsAI[i].speed*deltaTime;
    }
    
}


void drawCar(Car car)
{
    glPushMatrix();

    glColor3f(car.colorCarRandomR[0], car.colorCarRandomG[0], car.colorCarRandomB[0]); // Rouge
    glScaled(3,1,1);
    glutSolidCube(1.25f); 
     

    glColor3f(car.colorCarRandomR[1], car.colorCarRandomG[1], car.colorCarRandomB[1]); // vert
    glTranslatef(0.0f,1.25f,0.0f);
    glScaled(0.5f,1,1.0f);
    glutSolidCube(1.25f);
    

    glColor3f(car.colorCarRandomR[2], car.colorCarRandomG[2], car.colorCarRandomB[2]); // vert
    glTranslatef(1.2f,-0.8f,0.5f);
    glScaled(0.35f,0.35f,0.35f);
    glutSolidCube(1.25f);

    glTranslatef(0.0f,0.0f,-3.5f);
    glutSolidCube(1.25f);
    
    glColor3f(car.colorCarRandomR[3], car.colorCarRandomG[3], car.colorCarRandomB[3]); // vert
    glTranslatef(-7.0f,-0.0f,0.0f);
    glutSolidCube(1.25f);
    
    glTranslatef(0.0f,0.0f,3.5f);
    glutSolidCube(1.25f);
    glPopMatrix();
}



void controlCar(Car *car,char command)
{
   if(command=='W' && car->speed<car->maxSpeed)
			{
			
				if(car->speed<0)
				{
					
					car->speed+=car->dec;
			 }
				else
				{
					car->speed+=car->acc;
				}
			}
			if(command=='S' && car->speed>-car->maxSpeed)
			{
				 
				if(car->speed>0)
				{
				
					car->speed-=car->dec;
				}
				else
				{
					car->speed-=car->acc;
				}
				
			}
			
			 if(command=='E')
			 {
				if(car->speed-car->frein>0)
				{
					car->speed-=car->frein;
				}
				else if(car->speed+car->frein<0)
				{
					car->speed+=car->frein;
				}
				else
				{
					car->speed=0;
				}
			    }
			
			
			if(command=='1')
			{
			if(car->speed-car->dec>0)
				{
					car->speed-=car->dec;
				}
				else if(car->speed+car->dec<0)
				{
					car->speed+=car->dec;
				}
				else
				{
					car->speed=0;
				}
			}
	

			if(command=='A')
		{
		    if(car->speed>0.1f || car->speed<-0.1f )
			car->rotation-=car->turnSpeed*(car->speed/car->maxSpeed);
		}
			if(command=='D')
		{
		    if(car->speed>0.1f || car->speed<-0.1f)
			car->rotation+=car->turnSpeed*(car->speed/car->maxSpeed);
		}
		
	
	

}
