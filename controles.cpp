#include "controles.h"
#include "constantes.h"
#include "igreja.h"
#include <cmath>
#include <iostream>

// Função para desenhar o chão
void desenha_chao() {
    float tamanho = 200.0f;
    glColor3f(0.3f, 0.7f, 0.3f); // Verde grama
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-tamanho, 0.0f, -tamanho);
        glVertex3f( tamanho, 0.0f, -tamanho);
        glVertex3f( tamanho, 0.0f,  tamanho);
        glVertex3f(-tamanho, 0.0f,  tamanho);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Cálculo da direção da câmera
    float dx = sin(dir) * cos(pitch);
    float dy = sin(pitch);
    float dz = -cos(dir) * cos(pitch);

    gluLookAt(
        pos_x, pos_y, pos_z, // posição da câmera
        pos_x + dx, pos_y + dy, pos_z + dz, // ponto para onde olha
        0.0f, 1.0f, 0.0f // vetor up
    );

    desenha_chao();
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
    keyStates[key] = true;
    if (key == 27) // ESC
        exit(0);
}

void teclado_up(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void atualiza_camera_mouse(int x, int y) {
    if (!mouse_initialized) {
        last_mouse_x = x;
        last_mouse_y = y;
        mouse_initialized = true;
        return;
    }
    int dx = x - last_mouse_x;
    int dy = y - last_mouse_y;
    last_mouse_x = x;
    last_mouse_y = y;

    dir += dx * SENS_MOUSE;
    pitch += -dy * SENS_MOUSE;
    if (pitch > 1.2f) pitch = 1.2f;
    if (pitch < -1.2f) pitch = -1.2f;

    glutPostRedisplay();
}

void atualiza_movimento() {
    float move_x = 0.0f, move_z = 0.0f;
    if (keyStates['w']) {
        move_x += sin(dir);
        move_z += -cos(dir);
    }
    if (keyStates['s']) {
        move_x -= sin(dir);
        move_z -= -cos(dir);
    }
    if (keyStates['a']) {
        move_x -= cos(dir);
        move_z -= sin(dir);
    }
    if (keyStates['d']) {
        move_x += cos(dir);
        move_z += sin(dir);
    }
    // Normaliza para não andar mais rápido na diagonal
    float len = sqrt(move_x * move_x + move_z * move_z);
    if (len > 0.01f) {
        move_x /= len;
        move_z /= len;
        pos_x += move_x * VELOCIDADE * 0.2f;
        pos_z += move_z * VELOCIDADE * 0.2f;
    }
    glutPostRedisplay();
}
