#ifndef CONTROLES_H
#define CONTROLES_H

#include <GL/glut.h>

void display();
void redimensiona(int w, int h);
void teclado(unsigned char key, int x, int y);
void teclado_up(unsigned char key, int x, int y);
void atualiza_camera_mouse(int x, int y);
void atualiza_movimento();

#endif
