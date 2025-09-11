#include "telhado.h"
#include "constantes.h"

void desenha_telhas() {
    float altura_telhas = ALTURA + (LARGURA/2) * INCLINACAO_TELHADO;
    glColor3f(0.8f, 0.2f, 0.2f); // Vermelho telha

    float normal_x = INCLINACAO_TELHADO;
    float normal_y = 1.0f - INCLINACAO_TELHADO;

    // Lado esquerdo
    glNormal3f(-normal_x, normal_y, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, ALTURA, 0);
        glVertex3f( 0, altura_telhas, 0);
        glVertex3f( 0, altura_telhas, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, ALTURA, -COMPRIMENTO);
    glEnd();

    // Lado direito
    glNormal3f(normal_x, normal_y, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(LARGURA/2, ALTURA, 0);
        glVertex3f(0, altura_telhas, 0);
        glVertex3f(0, altura_telhas, -COMPRIMENTO);
        glVertex3f(LARGURA/2, ALTURA, -COMPRIMENTO);
    glEnd();
}
