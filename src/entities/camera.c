#include"camera.h"

void initialiseCamera()
{
   
   cam.fov=45.0f;
   cam.camPitch=0.0f;
   cam.camYaw=-90.0f;
   cam.mousevel=0.2f;
   cam.movevel=0.9f;
   cam.sensitivity = 0.05f;
   cam.cameraHeight=3.0f;
   cam.followDistance = 15.0f;
}

void lockCamera()
{
  if (cam.camPitch > 1.25f) cam.camPitch = 1.25f;
    if (cam.camPitch < -0.25f) cam.camPitch = -0.25f;
	
	if(cam.camYaw<0.0)
	  cam.camYaw+=360.0;
	if(cam.camYaw>360.0)
	  cam.camYaw-=360;
}

void mouseScroll(char command)
{

  if (command=='8') { // Roue vers le haut
        cam.fov -= 1.0f; // Réduit le champ de vision (zoom avant)
        if (cam.fov < 10.0f) cam.fov = 10.0f; // Limite minimale
    } else if(command=='9'){ // Roue vers le bas
        cam.fov += 1.0f; // Augmente le champ de vision (zoom arrière)
        if (cam.fov > 90.0f) cam.fov = 90.0f; // Limite maximale
    }
    printf("FoV ajusté : %.1f\n", cam.fov);
}

void controlCamera(char command)
{
		
if( command=='+')
{
    float deltaX = cam.sensitivity;

    cam.camYaw += deltaX;

    lockCamera();
}
else if( command=='-')
{
    float deltaX = cam.sensitivity;

    cam.camYaw -= deltaX;

    lockCamera();
}

if( command=='*')
{
    float deltaY = cam.sensitivity;

    cam.camPitch += deltaY;
    //glutWarpPointer(cam.MidX,cam.MidY);
    //glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    lockCamera();
}
else if( command=='/')
{
    float deltaY = cam.sensitivity;

    cam.camPitch -= deltaY;
    //glutWarpPointer(cam.MidX,cam.MidY);
    //glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    lockCamera();
}




}


void updateCamera(float objectPositionX,float objectPositionY,float objectPositionZ)
{
    float offsetX = cam.followDistance * cos(cam.camPitch) * sin(cam.camYaw);
    float offsetY = cam.followDistance * sin(cam.camPitch);
    float offsetZ = cam.followDistance * cos(cam.camPitch) * cos(cam.camYaw);


	double objectX = objectPositionX;
	double objectY = objectPositionY;
	double objectZ = objectPositionZ;

	double cameraX = objectX + offsetX;
	double cameraY = objectY + offsetY + cam.cameraHeight;
	double cameraZ = objectZ + offsetZ;

	 
	double cameraTargetX=objectPositionX;
	double cameraTargetY=objectPositionY;
	double cameraTargetZ=objectPositionZ;
	
	double upcamX=0.0f;
	double upcamY=1.0f;
	double upcamZ=0.0f;


    // Calculate the view matrix
   gluLookAt(cameraX,cameraY,cameraZ,cameraTargetX,cameraTargetY,cameraTargetZ,upcamX,upcamY,upcamZ);
}


void mouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON )
	{
	mi=1;
	}
	else if(state==GLUT_DOWN && button==GLUT_RIGHT_BUTTON)
	{
	mi2=1;
	}
	else
	{
	mi=0;
	mi2=0;
	}
	
}





