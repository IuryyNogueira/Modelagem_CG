#include "parede.h"
#include "constantes.h"

void desenha_parede() {
    // Frente
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, 0, 0);
        glVertex3f( LARGURA/2, 0, 0);
        glVertex3f( LARGURA/2, ALTURA, 0);
        glVertex3f(-LARGURA/2, ALTURA, 0);
    glEnd();

    // Fundo
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, 0, -COMPRIMENTO);
        glVertex3f( LARGURA/2, 0, -COMPRIMENTO);
        glVertex3f( LARGURA/2, ALTURA, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, ALTURA, -COMPRIMENTO);
    glEnd();

    // Lateral Esquerda
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, 0, 0);
        glVertex3f(-LARGURA/2, 0, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, ALTURA, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, ALTURA, 0);
    glEnd();

    // Lateral Direita
    glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(LARGURA/2, 0, 0);
        glVertex3f(LARGURA/2, 0, -COMPRIMENTO);
        glVertex3f(LARGURA/2, ALTURA, -COMPRIMENTO);
        glVertex3f(LARGURA/2, ALTURA, 0);
    glEnd();
}
