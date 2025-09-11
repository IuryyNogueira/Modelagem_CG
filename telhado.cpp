#include "telhado.h"
#include "constantes.h"

void desenha_telhas() {
    // Telhado colonial com 30% de inclinação conforme a planta
    float base_y = ALTURA_PLATAFORMA; // Base do telhado na altura da plataforma
    float altura_cumeeira = base_y + ALTURA + ALTURA_TELHADO;
    glColor3f(0.7f, 0.3f, 0.2f); // Cor de telha colonial

    // Água esquerda do telhado
    glNormal3f(-INCLINACAO_TELHADO, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, base_y + ALTURA, 0);
        glVertex3f(0, altura_cumeeira, 0);
        glVertex3f(0, altura_cumeeira, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, base_y + ALTURA, -COMPRIMENTO);
    glEnd();

    // Água direita do telhado
    glNormal3f(INCLINACAO_TELHADO, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(LARGURA/2, base_y + ALTURA, 0);
        glVertex3f(0, altura_cumeeira, 0);
        glVertex3f(0, altura_cumeeira, -COMPRIMENTO);
        glVertex3f(LARGURA/2, base_y + ALTURA, -COMPRIMENTO);
    glEnd();
    
    // Empenas (triângulos frontais e traseiros)
    glColor3f(0.95f, 0.95f, 0.9f); // Mesma cor das paredes
    
    // Empena frontal
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-LARGURA/2, base_y + ALTURA, 0);
        glVertex3f(LARGURA/2, base_y + ALTURA, 0);
        glVertex3f(0, altura_cumeeira, 0);
    glEnd();
    
    // Empena traseira
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-LARGURA/2, base_y + ALTURA, -COMPRIMENTO);
        glVertex3f(LARGURA/2, base_y + ALTURA, -COMPRIMENTO);
        glVertex3f(0, altura_cumeeira, -COMPRIMENTO);
    glEnd();
}
