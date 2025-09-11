#include "inicializacao.h"

void inicializa() {
    glClearColor(0.75f, 0.87f, 1.0f, 1.0f); // Céu azul claro como na imagem
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Configurar luz mais brilhante e natural
    GLfloat luz_pos[] = {-30.0f, 80.0f, 50.0f, 1.0f}; // Posição do sol
    GLfloat luz_ambiente[] = {0.4f, 0.4f, 0.4f, 1.0f}; // Luz ambiente
    GLfloat luz_difusa[] = {0.8f, 0.8f, 0.8f, 1.0f}; // Luz difusa
    GLfloat luz_especular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Luz especular
    
    glLightfv(GL_LIGHT0, GL_POSITION, luz_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
}
