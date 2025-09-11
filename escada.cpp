#include "escada.h"

void desenha_escada() {
    float largura = 12.0f;
    float profundidade_total = 8.0f;
    float altura_total = 1.5f;
    int degraus = 8;

    float altura_degrau = altura_total / degraus;
    float profundidade_degrau = profundidade_total / degraus;

    glColor3f(0.5f, 0.5f, 0.5f);
    for (int i = 0; i < degraus; ++i) {
        float y_baixo = i * altura_degrau;
        float y_cima = (i + 1) * altura_degrau;
        float z_frente = (i + 1) * profundidade_degrau;
        float z_tras = i * profundidade_degrau;

        // Topo do degrau
        glNormal3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(-largura/2, y_cima, z_tras);
            glVertex3f(largura/2, y_cima, z_tras);
            glVertex3f(largura/2, y_cima, z_frente);
            glVertex3f(-largura/2, y_cima, z_frente);
        glEnd();

        // Frente do degrau
        glNormal3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
            glVertex3f(-largura/2, y_baixo, z_frente);
            glVertex3f(largura/2, y_baixo, z_frente);
            glVertex3f(largura/2, y_cima, z_frente);
            glVertex3f(-largura/2, y_cima, z_frente);
        glEnd();
    }
}
