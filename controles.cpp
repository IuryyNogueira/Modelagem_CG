#include "controles.h"
#include "constantes.h"
#include "igreja.h"
#include <iostream>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -10.0f, -distancia_camera);
    glRotatef(angulo_x, 1.0f, 0.0f, 0.0f);
    glRotatef(angulo_y, 0.0f, 1.0f, 0.0f);

    desenha_igreja();
    glutSwapBuffers();
}

void redimensiona(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': angulo_x -= 5.0f; break;
        case 's': angulo_x += 5.0f; break;
        case 'a': angulo_y -= 5.0f; break;
        case 'd': angulo_y += 5.0f; break;
        case 'q': distancia_camera -= 5.0f; break;
        case 'e': distancia_camera += 5.0f; break;
        case 27: // Tecla ESC
            exit(0);
            break;
    }
    glutPostRedisplay();
}
