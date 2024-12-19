#include"grid.h"

const int gridSize = 100;
const float cellSize = 1.0f; // Taille d'une cellule

void drawGrid()
{
     glPushMatrix();
     glColor3f(0.5, 0.8, 0.9); // Couleur grise pour la grille
    glBegin(GL_LINES);
    for (int i = -gridSize; i <= gridSize; i++) {
        // Lignes verticales
        glVertex3f(i * cellSize, 0.0, -gridSize * cellSize);
        glVertex3f(i * cellSize, 0.0, gridSize * cellSize);

        // Lignes horizontales
        glVertex3f(-gridSize * cellSize, 0.0, i * cellSize);
        glVertex3f(gridSize * cellSize, 0.0, i * cellSize);
    }
    glEnd();
    glPopMatrix();
}
