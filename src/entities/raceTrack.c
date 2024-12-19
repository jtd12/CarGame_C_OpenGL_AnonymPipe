#include"raceTrack.h"

const float trackWidth = 20.5f; // Largeur de la piste

GLfloat vertices[8][3] = {
    {-100.0f, -100.0f, -100.0f}, // 0: Bas-gauche arrière
    { 100.0f, -100.0f, -100.0f}, // 1: Bas-droit arrière
    { 100.0f,  100.0f, -100.0f}, // 2: Haut-droit arrière
    {-100.0f,  100.0f, -100.0f}, // 3: Haut-gauche arrière
    {-100.0f, -100.0f,  100.0f}, // 4: Bas-gauche avant
    { 100.0f, -100.0f,  100.0f}, // 5: Bas-droit avant
    { 100.0f,  100.0f,  100.0f}, // 6: Haut-droit avant
    {-100.0f,  100.0f,  100.0f}  // 7: Haut-gauche avant
};


void generateTrack() {
    srand(time(NULL)); // Initialisation de la graine aléatoire

    for (int i = 0; i < NUMPOINTS; i++) {
        float angle = (float)i / NUMPOINTS * 2.0f * M_PI; // Angle en radians
        float radius = 30.0f + (rand() % 100) / 100.0f;    // Rayon aléatoire
        trackPoints[i][0] = radius * cos(angle);          // Coordonnée X
        trackPoints[i][1] = radius * sin(angle);          // Coordonnée Y
    }
}

void initialiseCity()
{
    srand((unsigned int)time(NULL));
  
  for(int i=0;i<NUMBERBLOC;i++)
  {
    scaleRandomX[i]=random_float(2, 5);
    scaleRandomY[i]=random_float(2, 20);
    scaleRandomZ[i]=random_float(2, 6);
    
    colorRandomR[i]=random_float(0.01,0.99);
    colorRandomG[i]=random_float(0.01,0.99);
    colorRandomB[i]=random_float(0.01,0.99);
    
   }
}

void drawTrack() {
    glPushMatrix();
    glColor3f(0.2, 0.9, 0.4); // Couleur grise pour la piste
	
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= NUMPOINTS; i++) {
        int idx = i % NUMPOINTS; // Boucle circulaire

        // Point central de la piste
        float x = trackPoints[idx][0];
        float y = trackPoints[idx][1];

        // Calcul d'un vecteur perpendiculaire
        float dx = -y;
        float dy = x;
        float length = sqrt(dx * dx + dy * dy);
        dx /= length;
        dy /= length;

        // Points à gauche et à droite de la piste
        float leftX = x + dx * trackWidth;
        float leftY = y + dy * trackWidth;
        float rightX = x - dx * trackWidth;
        float rightY = y - dy * trackWidth;

        // Ajout des points au strip
        glVertex3f(leftX, 0.0, leftY);  // Point à gauche
        glVertex3f(rightX, 0.0, rightY); // Point à droite
    }
    glEnd();
    glPopMatrix();
}

void drawCity()
{
for (int i=0;i<NUMBERBLOC;i++)
{
glPushMatrix();
glTranslated((i*15)-70,1,-80);
glScaled(scaleRandomX[i],scaleRandomY[i],scaleRandomZ[i]);
glColor3f(colorRandomR[i],colorRandomG[i],colorRandomB[i]);
glutSolidCube(2.5);
glPopMatrix();
}

for (int i=0;i<NUMBERBLOC;i++)
{
glPushMatrix();
glTranslated((i*15)-70,1,80);
glScaled(scaleRandomX[i],scaleRandomY[i],scaleRandomZ[i]);
glColor3f(colorRandomR[i],colorRandomG[i],colorRandomB[i]);
glutSolidCube(2.5);
glPopMatrix();
}

for (int i=0;i<NUMBERBLOC;i++)
{
glPushMatrix();
glTranslated((80),1,80+(i*-15));
glScaled(scaleRandomX[i],scaleRandomY[i],scaleRandomZ[i]);
glColor3f(colorRandomR[i],colorRandomG[i],colorRandomB[i]);
glutSolidCube(2.5);
glPopMatrix();
}

for (int i=0;i<NUMBERBLOC;i++)
{
glPushMatrix();
glTranslated((-80),1,80+(i*-15));
glScaled(scaleRandomX[i],scaleRandomY[i],scaleRandomZ[i]);
glColor3f(colorRandomR[i],colorRandomG[i],colorRandomB[i]);
glutSolidCube(2.5);
glPopMatrix();
}

}

void drawPlane(float size)
{
glPushMatrix();
  float half = size / 2.0f;

    glColor3f(0.8f, 0.2f, 0.4f); // Couleur verte pour le sol

    glBegin(GL_QUADS);
        glVertex3f(-half, 0.0f, -half);
        glVertex3f(half, 0.0f, -half);
        glVertex3f(half, 0.0f, half);
        glVertex3f(-half, 0.0f, half);
    glEnd();
glPopMatrix();
}

void drawCube()
{
glPushMatrix();
glBegin(GL_TRIANGLES);

    glColor3f(0.5,0.5,0.8);
    glVertex3fv(vertices[0]); // Bas-gauche arrière
    glVertex3fv(vertices[3]); // Haut-gauche arrière
    glVertex3fv(vertices[2]); // Haut-droit arrière
    
    glColor3f(0.25,0.15,0.15);
    glVertex3fv(vertices[0]); // Bas-gauche arrière
    glVertex3fv(vertices[2]); // Haut-droit arrière
    glVertex3fv(vertices[1]); // Bas-droit arrière

    // Face gauche (0, 3, 7, 4)
    glColor3f(0.4,0.5,0.8);
    glVertex3fv(vertices[0]); // Bas-gauche arrière
    glVertex3fv(vertices[3]); // Haut-gauche arrière
    glVertex3fv(vertices[7]); // Haut-gauche avant
    
    glColor3f(0.9,0.9,0.8);
    glVertex3fv(vertices[0]); // Bas-gauche arrière
    glVertex3fv(vertices[7]); // Haut-gauche avant
    glVertex3fv(vertices[4]); // Bas-gauche avant

    // Face droite (1, 2, 6, 5)
    glColor3f(0.78,0.75,0.1);
    glVertex3fv(vertices[1]); // Bas-droit arrière
    glVertex3fv(vertices[2]); // Haut-droit arrière
    glVertex3fv(vertices[6]); // Haut-droit avant
    
    glColor3f(0.51,0.8,0.9);
    glVertex3fv(vertices[1]); // Bas-droit arrière
    glVertex3fv(vertices[6]); // Haut-droit avant
    glVertex3fv(vertices[5]); // Bas-droit avant

    // Face avant (4, 5, 6, 7)
    glColor3f(0.4,0.5,0.5);
    glVertex3fv(vertices[4]); // Bas-gauche avant
    glVertex3fv(vertices[7]); // Haut-gauche avant
    glVertex3fv(vertices[6]); // Haut-droit avant
    
    glColor3f(0.2,0.9,0.1);
    glVertex3fv(vertices[4]); // Bas-gauche avant
    glVertex3fv(vertices[6]); // Haut-droit avant
    glVertex3fv(vertices[5]); // Bas-droit avant
	

    // Répétez pour les autres 3 faces latérales (gauche, droite, avant).

glEnd();
glPopMatrix();
}

