#include "inicializacao.h"

void inicializa() {
    glClearColor(0.7f, 0.85f, 1.0f, 1.0f); // Céu azul claro
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Posição da luz
    GLfloat luz_pos[] = {50.0f, 100.0f, 80.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, luz_pos);
}
