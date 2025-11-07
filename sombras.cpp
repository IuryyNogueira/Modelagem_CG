#include "sombras.h"
#include "interior.h"
#include "parede.h"
#include <iostream>
#include <cstring>

SistemaSombras sistema_sombras;

SistemaSombras::SistemaSombras() {
    // Inicializar matrizes como identidade
    memset(matriz_sombra_chao, 0, sizeof(matriz_sombra_chao));
    memset(matriz_sombra_plataforma, 0, sizeof(matriz_sombra_plataforma));
    
    matriz_sombra_chao[0] = matriz_sombra_chao[5] = 
    matriz_sombra_chao[10] = matriz_sombra_chao[15] = 1.0f;
    
    matriz_sombra_plataforma[0] = matriz_sombra_plataforma[5] = 
    matriz_sombra_plataforma[10] = matriz_sombra_plataforma[15] = 1.0f;
}

void SistemaSombras::inicializar() {
    std::cout << "Sistema de sombras inicializado" << std::endl;
}

void SistemaSombras::calcular_matriz_sombra_planar(GLfloat matriz[16], 
                                                    GLfloat luz_pos[4],
                                                    GLfloat plano[4]) {
    // Plano: ax + by + cz + d = 0
    // luz_pos: [x, y, z, w] onde w=0 para luz direcional, w=1 para pontual
    
    GLfloat a = plano[0];
    GLfloat b = plano[1];
    GLfloat c = plano[2];
    GLfloat d = plano[3];
    
    GLfloat lx = luz_pos[0];
    GLfloat ly = luz_pos[1];
    GLfloat lz = luz_pos[2];
    GLfloat lw = luz_pos[3];
    
    // dot = a*lx + b*ly + c*lz + d*lw
    GLfloat dot = a * lx + b * ly + c * lz + d * lw;
    
    // Construir matriz de projeção de sombra
    matriz[0]  = dot - a * lx;
    matriz[1]  = -b * lx;
    matriz[2]  = -c * lx;
    matriz[3]  = -d * lx;
    
    matriz[4]  = -a * ly;
    matriz[5]  = dot - b * ly;
    matriz[6]  = -c * ly;
    matriz[7]  = -d * ly;
    
    matriz[8]  = -a * lz;
    matriz[9]  = -b * lz;
    matriz[10] = dot - c * lz;
    matriz[11] = -d * lz;
    
    matriz[12] = -a * lw;
    matriz[13] = -b * lw;
    matriz[14] = -c * lw;
    matriz[15] = dot - d * lw;
}

void SistemaSombras::iniciar_sombra_chao(GLfloat luz_pos[4]) {
    // Plano do chão interno: y = 1.6 (altura do piso da igreja)
    GLfloat plano_chao[4] = {0.0f, 1.0f, 0.0f, -1.6f};
    calcular_matriz_sombra_planar(matriz_sombra_chao, luz_pos, plano_chao);
    
    // Configurar estado OpenGL para sombras
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST); // Habilitar depth test para evitar bugs
    glDepthMask(GL_FALSE); // Mas não escrever no depth buffer
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Sombra mais suave e sutil
    GLfloat cor_sombra_suave[4] = {0.0f, 0.0f, 0.0f, 0.25f};
    glColor4fv(cor_sombra_suave);
    
    // Usar polygon offset para evitar z-fighting
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);
    
    glPushMatrix();
    glMultMatrixf(matriz_sombra_chao);
}

void SistemaSombras::iniciar_sombra_plataforma(GLfloat luz_pos[4]) {
    // Plano da plataforma: y = 1.51 (topo da plataforma)
    GLfloat plano_plataforma[4] = {0.0f, 1.0f, 0.0f, -1.51f};
    calcular_matriz_sombra_planar(matriz_sombra_plataforma, luz_pos, plano_plataforma);
    
    // Configurar estado OpenGL para sombras
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glColor4fv(cor_sombra);
    
    glPushMatrix();
    glMultMatrixf(matriz_sombra_plataforma);
}

void SistemaSombras::finalizar_sombra() {
    glPopMatrix();
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDepthMask(GL_TRUE);
    glPopAttrib();
}

void SistemaSombras::desenhar_sombras_interiores() {
    // Desenhar geometria simplificada dos objetos internos
    // (as sombras serão projetadas pela matriz ativa)
    
    // Bancos (8 de cada lado) - sombras mais suaves e corretas
    for(int i = 0; i < 8; i++) {
        // Lado esquerdo
        glPushMatrix();
        glTranslatef(-8.0f, 1.6f, 15.0f - i * 4.0f);
        glScalef(3.8f, 1.8f, 2.3f);
        glutSolidCube(1.0);
        glPopMatrix();
        
        // Lado direito
        glPushMatrix();
        glTranslatef(8.0f, 1.6f, 15.0f - i * 4.0f);
        glScalef(3.8f, 1.8f, 2.3f);
        glutSolidCube(1.0);
        glPopMatrix();
    }
    
    // Altar - sombra mais definida
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, -35.0f);
    glScalef(9.0f, 3.5f, 4.5f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Velas (3 no altar) - sombras finas
    float posicoes_velas[][2] = {
        {-4.0f, -35.0f},  // Esquerda
        {0.0f, -35.0f},   // Centro
        {4.0f, -35.0f}    // Direita
    };
    
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(posicoes_velas[i][0], 4.5f, posicoes_velas[i][1]);
        glScalef(0.25f, 1.2f, 0.25f);
        glutSolidCube(1.0);
        glPopMatrix();
    }
}

void SistemaSombras::desenhar_sombras_exteriores() {
    // Sombras simplificadas da estrutura externa da igreja na plataforma
    
    // Paredes laterais principais
    for(int lado = -1; lado <= 1; lado += 2) {
        glPushMatrix();
        glTranslatef(lado * 12.0f, 8.0f, 0.0f);
        glScalef(2.0f, 14.0f, 40.0f);
        glutSolidCube(1.0);
        glPopMatrix();
    }
    
    // Parede frontal
    glPushMatrix();
    glTranslatef(0.0f, 8.0f, 22.0f);
    glScalef(24.0f, 14.0f, 2.0f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Parede traseira
    glPushMatrix();
    glTranslatef(0.0f, 8.0f, -38.0f);
    glScalef(24.0f, 14.0f, 2.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}
