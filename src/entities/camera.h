#ifndef DEF_CAMERA_H
#define DEF_CAMERA_H
#include <GL/gl.h>
#include<GL/glu.h>
#include<stdio.h>
#include<math.h>
#include<GL/freeglut.h>

	typedef struct 
		{
			int up,down,left,right;
			float camYaw;
			float camPitch;
			float fov;
			float mousevel;
			float movevel;
			float x,y,z;
			int ismoved;
			float cameraHeight;
			int MidX;
			int MidY;
			int actif;
			float speed;
			float sensitivity;
			float followDistance;
			int posX,posY;
		 } Camera;
		 
		Camera cam;
		
		int mi;
		int mi2;
		void initialiseCamera();
		void controlCamera(char command);
		void mouseScroll(char command);
		void updateCamera(float objectPositionX,float objectPositionY,float objectPositionZ);
		void lockCamera();
		void mouse(int button, int state, int x, int y);
		int isMoved();
		

#endif
		
