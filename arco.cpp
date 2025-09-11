#include "arco.h"
#include "constantes.h"
#include <cmath>

void desenha_cruz() {
    // Cruz no topo do arco parabólico
    float altura_cruz = 4.0f;
    float largura_cruz = 3.0f;
    float espessura = 0.5f;
    
    glColor3f(0.15f, 0.15f, 0.15f); // Cinza bem escuro para destaque
    
    glPushMatrix();
    // Posicionar no topo do arco parabólico (ponto mais alto)
    glTranslatef(0.0f, ALTURA_PLATAFORMA + ALTURA + 12.0f + 2.0f, 10.0f); // No topo do arco
    
    // Haste vertical da cruz
    glPushMatrix();
    glScalef(espessura, altura_cruz, espessura);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Haste horizontal da cruz
    glPushMatrix();
    glTranslatef(0.0f, altura_cruz/4, 0.0f); // Posicionamento na haste
    glScalef(largura_cruz, espessura, espessura);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Base da cruz para melhor fixação no arco
    glColor3f(0.25f, 0.25f, 0.25f);
    glPushMatrix();
    glTranslatef(0.0f, -altura_cruz/2 - 0.4f, 0.0f);
    glScalef(espessura * 2.5f, 0.8f, espessura * 2.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPopMatrix();
}

void desenha_arco_moderno() {
    // Arco parabólico que vai até o chão
    float base_y = 0.0f; // Começar do chão
    float altura_maxima_arco = ALTURA + 12.0f; // Bem alto como na imagem
    float largura_total_arco = LARGURA * 0.7f; // Achatado - metade da largura da igreja
    float profundidade_arco = 2.0f;
    
    glColor3f(0.92f, 0.92f, 0.90f); // Cor branca como na imagem
    
    // Desenhar arco parabólico usando muitos segmentos para suavidade
    int num_segmentos = 30;
    
    glPushMatrix();
    // Posicionar mais à frente da igreja
    glTranslatef(0.0f, 0.0f, 10.0f);
    
    // Criar arco parabólico achatado
    for (int i = 0; i < num_segmentos; ++i) {
        // Parâmetro t vai de -1 a 1 para criar parábola simétrica
        float t1 = -1.0f + (2.0f * i) / num_segmentos;
        float t2 = -1.0f + (2.0f * (i + 1)) / num_segmentos;
        
        // Fórmula parabólica: y = a * (1 - t²) onde t vai de -1 a 1
        float y1 = altura_maxima_arco * (1.0f - t1 * t1);
        float y2 = altura_maxima_arco * (1.0f - t2 * t2);
        float x1 = t1 * (largura_total_arco / 2);
        float x2 = t2 * (largura_total_arco / 2);
        
        // Pontos internos (arco oco)
        float fator_interno = 0.93f; // 93% do tamanho para criar espessura mais fina
        float y1_int = y1 * fator_interno;
        float y2_int = y2 * fator_interno;
        float x1_int = x1 * fator_interno;
        float x2_int = x2 * fator_interno;
        
        // Desenhar segmento do arco
        glBegin(GL_QUADS);
            // Face frontal
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(x1, base_y + y1, profundidade_arco/2);
            glVertex3f(x2, base_y + y2, profundidade_arco/2);
            glVertex3f(x2_int, base_y + y2_int, profundidade_arco/2);
            glVertex3f(x1_int, base_y + y1_int, profundidade_arco/2);
            
            // Face traseira
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(x1, base_y + y1, -profundidade_arco/2);
            glVertex3f(x2, base_y + y2, -profundidade_arco/2);
            glVertex3f(x2_int, base_y + y2_int, -profundidade_arco/2);
            glVertex3f(x1_int, base_y + y1_int, -profundidade_arco/2);
            
            // Face externa (calculando normal aproximada)
            float dx = x2 - x1;
            float dy = y2 - y1;
            float len = sqrt(dx*dx + dy*dy);
            float nx = -dy / len; // Normal perpendicular à tangente
            float ny = dx / len;
            
            glNormal3f(nx, ny, 0.0f);
            glVertex3f(x1, base_y + y1, profundidade_arco/2);
            glVertex3f(x1, base_y + y1, -profundidade_arco/2);
            glVertex3f(x2, base_y + y2, -profundidade_arco/2);
            glVertex3f(x2, base_y + y2, profundidade_arco/2);
            
            // Face interna
            glNormal3f(-nx, -ny, 0.0f);
            glVertex3f(x1_int, base_y + y1_int, profundidade_arco/2);
            glVertex3f(x1_int, base_y + y1_int, -profundidade_arco/2);
            glVertex3f(x2_int, base_y + y2_int, -profundidade_arco/2);
            glVertex3f(x2_int, base_y + y2_int, profundidade_arco/2);
        glEnd();
    }
    
    glPopMatrix();
}

void desenha_arco() {
    desenha_arco_moderno();
    desenha_cruz();
}
