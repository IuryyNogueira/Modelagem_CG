#include "feixes_luz.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

SistemaFeixesLuz sistema_feixes_luz;

SistemaFeixesLuz::SistemaFeixesLuz() 
    : intensidade_base(0.3f), comprimento_feixe(15.0f) {
}

void SistemaFeixesLuz::inicializar() {
    std::cout << "Sistema de feixes de luz inicializado" << std::endl;
}

void SistemaFeixesLuz::desenhar_feixe_individual(float origem_x, float origem_y, float origem_z,
                                                 float direcao_x, float direcao_y, float direcao_z,
                                                 float largura_base, float largura_fim,
                                                 float r, float g, float b, float alpha) {
    // Normalizar direção
    float len = sqrt(direcao_x*direcao_x + direcao_y*direcao_y + direcao_z*direcao_z);
    if (len < 0.001f) return;
    
    direcao_x /= len;
    direcao_y /= len;
    direcao_z /= len;
    
    // Calcular vetor perpendicular usando produto vetorial
    float perp_x, perp_y, perp_z;
    if (fabs(direcao_y) < 0.9f) {
        // Produto vetorial com (0, 1, 0)
        perp_x = -direcao_z;
        perp_y = 0.0f;
        perp_z = direcao_x;
    } else {
        // Produto vetorial com (1, 0, 0)
        perp_x = 0.0f;
        perp_y = direcao_z;
        perp_z = -direcao_y;
    }
    
    // Normalizar perpendicular
    len = sqrt(perp_x*perp_x + perp_y*perp_y + perp_z*perp_z);
    if (len < 0.001f) return;
    perp_x /= len;
    perp_y /= len;
    perp_z /= len;
    
    // Ponto final do feixe
    float fim_x = origem_x + direcao_x * comprimento_feixe;
    float fim_y = origem_y + direcao_y * comprimento_feixe;
    float fim_z = origem_z + direcao_z * comprimento_feixe;
    
    // Desenhar feixe como cone de triângulos
    int segmentos = 8;
    glBegin(GL_TRIANGLES);
    
    for (int i = 0; i < segmentos; i++) {
        float angulo1 = (i * 2.0f * M_PI) / segmentos;
        float angulo2 = ((i + 1) * 2.0f * M_PI) / segmentos;
        
        float cos1 = cos(angulo1);
        float sin1 = sin(angulo1);
        float cos2 = cos(angulo2);
        float sin2 = sin(angulo2);
        
        // Segundo vetor perpendicular
        float perp2_x = direcao_y * perp_z - direcao_z * perp_y;
        float perp2_y = direcao_z * perp_x - direcao_x * perp_z;
        float perp2_z = direcao_x * perp_y - direcao_y * perp_x;
        
        // Vértices na base
        float base1_x = origem_x + (perp_x * cos1 + perp2_x * sin1) * largura_base;
        float base1_y = origem_y + (perp_y * cos1 + perp2_y * sin1) * largura_base;
        float base1_z = origem_z + (perp_z * cos1 + perp2_z * sin1) * largura_base;
        
        float base2_x = origem_x + (perp_x * cos2 + perp2_x * sin2) * largura_base;
        float base2_y = origem_y + (perp_y * cos2 + perp2_y * sin2) * largura_base;
        float base2_z = origem_z + (perp_z * cos2 + perp2_z * sin2) * largura_base;
        
        // Vértices no fim
        float fim1_x = fim_x + (perp_x * cos1 + perp2_x * sin1) * largura_fim;
        float fim1_y = fim_y + (perp_y * cos1 + perp2_y * sin1) * largura_fim;
        float fim1_z = fim_z + (perp_z * cos1 + perp2_z * sin1) * largura_fim;
        
        float fim2_x = fim_x + (perp_x * cos2 + perp2_x * sin2) * largura_fim;
        float fim2_y = fim_y + (perp_y * cos2 + perp2_y * sin2) * largura_fim;
        float fim2_z = fim_z + (perp_z * cos2 + perp2_z * sin2) * largura_fim;
        
        // Triângulo 1 (base1 -> fim1 -> fim2)
        glColor4f(r, g, b, alpha * 0.7f);
        glVertex3f(base1_x, base1_y, base1_z);
        glColor4f(r, g, b, alpha * 0.05f);
        glVertex3f(fim1_x, fim1_y, fim1_z);
        glVertex3f(fim2_x, fim2_y, fim2_z);
        
        // Triângulo 2 (base1 -> fim2 -> base2)
        glColor4f(r, g, b, alpha * 0.7f);
        glVertex3f(base1_x, base1_y, base1_z);
        glColor4f(r, g, b, alpha * 0.05f);
        glVertex3f(fim2_x, fim2_y, fim2_z);
        glColor4f(r, g, b, alpha * 0.7f);
        glVertex3f(base2_x, base2_y, base2_z);
    }
    
    glEnd();
}

void SistemaFeixesLuz::desenhar_feixes_janelas() {
    // Feixes removidos - estavam fora da igreja
    // Apenas feixes internos das velas serão mantidos
}

void SistemaFeixesLuz::desenhar_feixes_velas() {
    // Feixes das velas no altar - ROTACIONADOS 90 GRAUS (horizontais)
    float posicoes_velas[][2] = {
        {-4.5f, -32.0f},  // Esquerda
        {0.0f, -32.0f},   // Centro
        {4.5f, -32.0f}    // Direita
    };
    
    for (int i = 0; i < 3; i++) {
        desenhar_feixe_individual(
            posicoes_velas[i][0], 4.5f, posicoes_velas[i][1],  // Origem (vela)
            1.0f, 0.0f, 0.0f,                                   // Direção HORIZONTAL (90° rotacionado)
            0.15f, 0.6f,                                        // Largura base e fim
            1.0f, 0.7f, 0.2f, 0.2f                             // Cor laranja suave
        );
    }
}

void SistemaFeixesLuz::desenhar_todos_feixes() {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDepthMask(GL_FALSE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    desenhar_feixes_janelas();
    desenhar_feixes_velas();
    
    glPopAttrib();
}
