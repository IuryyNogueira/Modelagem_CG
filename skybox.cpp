#include "skybox.h"
#include "constantes.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

void inicializar_skybox() {
    // Skybox procedural não precisa carregar textura
}

void desenha_skybox() {
    // Salvar estado atual
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
    
    // Desabilitar TUDO que pode interferir
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    
    // Tamanho do skybox (gigante para nunca ver as bordas)
    float tamanho = 600.0f;
    float altura = 500.0f;
    
    // Cores FIXAS do céu (sem variação)
    // Horizonte: azul claro/ciano
    float r_horizonte = 0.7f;
    float g_horizonte = 0.85f;
    float b_horizonte = 0.95f;
    
    // Zênite (topo): azul médio
    float r_zenite = 0.3f;
    float g_zenite = 0.6f;
    float b_zenite = 0.9f;
    
    glPushMatrix();
    // NÃO usar glLoadIdentity() - manter transformação da câmera
    
    glShadeModel(GL_SMOOTH); // Gradiente suave
    
    // FACE NORTE (Traseira)
    glBegin(GL_QUADS);
        glColor3f(r_zenite, g_zenite, b_zenite);
        glVertex3f(-tamanho, altura, -tamanho);
        glVertex3f(tamanho, altura, -tamanho);
        glColor3f(r_horizonte, g_horizonte, b_horizonte);
        glVertex3f(tamanho, 0.0f, -tamanho);
        glVertex3f(-tamanho, 0.0f, -tamanho);
    glEnd();
    
    // FACE SUL (Frontal)
    glBegin(GL_QUADS);
        glColor3f(r_zenite, g_zenite, b_zenite);
        glVertex3f(tamanho, altura, tamanho);
        glVertex3f(-tamanho, altura, tamanho);
        glColor3f(r_horizonte, g_horizonte, b_horizonte);
        glVertex3f(-tamanho, 0.0f, tamanho);
        glVertex3f(tamanho, 0.0f, tamanho);
    glEnd();
    
    // FACE OESTE (Esquerda)
    glBegin(GL_QUADS);
        glColor3f(r_zenite, g_zenite, b_zenite);
        glVertex3f(-tamanho, altura, tamanho);
        glVertex3f(-tamanho, altura, -tamanho);
        glColor3f(r_horizonte, g_horizonte, b_horizonte);
        glVertex3f(-tamanho, 0.0f, -tamanho);
        glVertex3f(-tamanho, 0.0f, tamanho);
    glEnd();
    
    // FACE LESTE (Direita)
    glBegin(GL_QUADS);
        glColor3f(r_zenite, g_zenite, b_zenite);
        glVertex3f(tamanho, altura, -tamanho);
        glVertex3f(tamanho, altura, tamanho);
        glColor3f(r_horizonte, g_horizonte, b_horizonte);
        glVertex3f(tamanho, 0.0f, tamanho);
        glVertex3f(tamanho, 0.0f, -tamanho);
    glEnd();
    
    // FACE SUPERIOR (Topo do céu)
    glBegin(GL_QUADS);
        glColor3f(r_zenite * 0.85f, g_zenite * 0.85f, b_zenite);
        glVertex3f(-tamanho, altura, -tamanho);
        glVertex3f(-tamanho, altura, tamanho);
        glVertex3f(tamanho, altura, tamanho);
        glVertex3f(tamanho, altura, -tamanho);
    glEnd();
    
    // SOL (esfera amarela brilhante em posição fixa) - GIGANTE E MUITO VISÍVEL
    float pos_sol_x = 200.0f;
    float pos_sol_y = 250.0f;
    float pos_sol_z = -150.0f;
    
    // HALO EXTERNO DO SOL (grande e brilhante)
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    glPushMatrix();
    glTranslatef(pos_sol_x, pos_sol_y, pos_sol_z);
    
    // Halo externo gigante
    glColor4f(1.0f, 0.9f, 0.5f, 0.15f);
    glutSolidSphere(120.0f, 20, 20);
    
    // Halo médio
    glColor4f(1.0f, 0.95f, 0.7f, 0.3f);
    glutSolidSphere(85.0f, 24, 24);
    
    // Halo interno
    glColor4f(1.0f, 1.0f, 0.85f, 0.6f);
    glutSolidSphere(65.0f, 28, 28);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // SOL PRINCIPAL (núcleo super brilhante)
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Material emissivo EXTREMAMENTE brilhante
    GLfloat sol_emissao[] = {1.5f, 1.4f, 0.9f, 1.0f};
    GLfloat sol_difusa[] = {1.0f, 1.0f, 0.95f, 1.0f};
    GLfloat sol_especular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, sol_emissao);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sol_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sol_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    
    glColor3f(1.0f, 1.0f, 0.9f);
    glutSolidSphere(55.0f, 40, 40); // Sol GIGANTE
    
    // Resetar emissão
    GLfloat sem_emissao[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, sem_emissao);
    
    glPopMatrix();
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    
    // NUVENS ESTÁTICAS (MUITAS nuvens em posições fixas)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Array com 20 nuvens espalhadas pelo céu
    float nuvens_pos[20][3] = {
        {-280.0f, 280.0f, -200.0f},
        {200.0f, 260.0f, -250.0f},
        {-150.0f, 300.0f, 140.0f},
        {300.0f, 270.0f, 80.0f},
        {50.0f, 290.0f, -300.0f},
        {-300.0f, 275.0f, 240.0f},
        {-100.0f, 255.0f, -120.0f},
        {240.0f, 295.0f, 200.0f},
        {-200.0f, 265.0f, -280.0f},
        {160.0f, 285.0f, -70.0f},
        {-240.0f, 250.0f, 100.0f},
        {120.0f, 278.0f, -180.0f},
        {-60.0f, 268.0f, 220.0f},
        {280.0f, 262.0f, -140.0f},
        {-320.0f, 288.0f, -50.0f},
        {20.0f, 272.0f, 260.0f},
        {180.0f, 292.0f, -220.0f},
        {-180.0f, 258.0f, -160.0f},
        {260.0f, 282.0f, 120.0f},
        {-140.0f, 298.0f, -240.0f}
    };
    
    glColor4f(1.0f, 1.0f, 1.0f, 0.9f); // Branco bem visível
    
    for (int i = 0; i < 20; i++) {
        float x = nuvens_pos[i][0];
        float y = nuvens_pos[i][1];
        float z = nuvens_pos[i][2];
        
        // Variação de tamanho para realismo
        float escala_base = 1.0f + (i % 3) * 0.4f;
        
        // Nuvem como elipse achatada (5 quads sobrepostos para dar mais volume)
        for (int j = 0; j < 5; j++) {
            float offset_y = (j - 2.0f) * 8.0f;
            float offset_x = (j - 2.0f) * 3.0f;
            float escala = escala_base * (1.0f - abs(j - 2.0f) * 0.15f);
            
            glBegin(GL_QUADS);
                glVertex3f(x - 90.0f * escala + offset_x, y + offset_y, z - 45.0f * escala);
                glVertex3f(x + 90.0f * escala + offset_x, y + offset_y, z - 45.0f * escala);
                glVertex3f(x + 90.0f * escala + offset_x, y + offset_y, z + 45.0f * escala);
                glVertex3f(x - 90.0f * escala + offset_x, y + offset_y, z + 45.0f * escala);
            glEnd();
        }
    }
    
    glDisable(GL_BLEND);
    glShadeModel(GL_FLAT);
    
    glPopMatrix();
    
    glDepthMask(GL_TRUE);
    
    // Restaurar estado
    glPopAttrib();
}
