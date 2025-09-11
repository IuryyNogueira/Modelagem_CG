#include "parede.h"
#include "constantes.h"
#include <cmath>

void desenha_plataforma() {
    glColor3f(0.6f, 0.6f, 0.62f); // Cor de concreto
    
    // Dimensões da plataforma
    float largura_plataforma = LARGURA + 10.0f; // Um pouco maior que a igreja
    float profundidade_plataforma = COMPRIMENTO + 5.0f;
    
    // Plataforma principal
    glBegin(GL_QUADS);
        // Topo da plataforma
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-largura_plataforma/2, ALTURA_PLATAFORMA, -profundidade_plataforma);
        glVertex3f(largura_plataforma/2, ALTURA_PLATAFORMA, -profundidade_plataforma);
        glVertex3f(largura_plataforma/2, ALTURA_PLATAFORMA, 0);
        glVertex3f(-largura_plataforma/2, ALTURA_PLATAFORMA, 0);
        
        // Frente da plataforma
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-largura_plataforma/2, 0, 0);
        glVertex3f(largura_plataforma/2, 0, 0);
        glVertex3f(largura_plataforma/2, ALTURA_PLATAFORMA, 0);
        glVertex3f(-largura_plataforma/2, ALTURA_PLATAFORMA, 0);
        
        // Traseira da plataforma
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-largura_plataforma/2, 0, -profundidade_plataforma);
        glVertex3f(largura_plataforma/2, 0, -profundidade_plataforma);
        glVertex3f(largura_plataforma/2, ALTURA_PLATAFORMA, -profundidade_plataforma);
        glVertex3f(-largura_plataforma/2, ALTURA_PLATAFORMA, -profundidade_plataforma);
        
        // Laterais da plataforma
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-largura_plataforma/2, 0, 0);
        glVertex3f(-largura_plataforma/2, 0, -profundidade_plataforma);
        glVertex3f(-largura_plataforma/2, ALTURA_PLATAFORMA, -profundidade_plataforma);
        glVertex3f(-largura_plataforma/2, ALTURA_PLATAFORMA, 0);
        
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(largura_plataforma/2, 0, 0);
        glVertex3f(largura_plataforma/2, 0, -profundidade_plataforma);
        glVertex3f(largura_plataforma/2, ALTURA_PLATAFORMA, -profundidade_plataforma);
        glVertex3f(largura_plataforma/2, ALTURA_PLATAFORMA, 0);
    glEnd();
}

void desenha_parede() {
    float base_y = ALTURA_PLATAFORMA;
    
    // Parede frontal - estilo moderno com nicho laranja
    glColor3f(0.85f, 0.85f, 0.82f); // Cor cinza claro para paredes principais
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        // Lado esquerdo da entrada
        glVertex3f(-LARGURA/2, base_y, 0);
        glVertex3f(-LARGURA_ESCADA/2, base_y, 0);
        glVertex3f(-LARGURA_ESCADA/2, base_y + ALTURA, 0);
        glVertex3f(-LARGURA/2, base_y + ALTURA, 0);
        
        // Lado direito da entrada  
        glVertex3f(LARGURA_ESCADA/2, base_y, 0);
        glVertex3f(LARGURA/2, base_y, 0);
        glVertex3f(LARGURA/2, base_y + ALTURA, 0);
        glVertex3f(LARGURA_ESCADA/2, base_y + ALTURA, 0);
        
        // Parte superior da entrada (dintel)
        glVertex3f(-LARGURA_ESCADA/2, base_y + ALTURA * 0.75f, 0);
        glVertex3f(LARGURA_ESCADA/2, base_y + ALTURA * 0.75f, 0);
        glVertex3f(LARGURA_ESCADA/2, base_y + ALTURA, 0);
        glVertex3f(-LARGURA_ESCADA/2, base_y + ALTURA, 0);
    glEnd();
    
    // Nicho laranja na fachada (como na imagem de referência)
    glColor3f(0.9f, 0.5f, 0.3f); // Cor laranja/terracota
    glPushMatrix();
    glTranslatef(0.0f, base_y + ALTURA * 0.4f, 0.5f); // Ligeiramente à frente da parede
    
    // Fundo do nicho
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-8.0f, -ALTURA * 0.25f, 0);
        glVertex3f(8.0f, -ALTURA * 0.25f, 0);
        glVertex3f(8.0f, ALTURA * 0.25f, 0);
        glVertex3f(-8.0f, ALTURA * 0.25f, 0);
    glEnd();
    
    // Laterais do nicho
    glBegin(GL_QUADS);
        // Lateral esquerda
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-8.0f, -ALTURA * 0.25f, -0.5f);
        glVertex3f(-8.0f, -ALTURA * 0.25f, 0);
        glVertex3f(-8.0f, ALTURA * 0.25f, 0);
        glVertex3f(-8.0f, ALTURA * 0.25f, -0.5f);
        
        // Lateral direita
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(8.0f, -ALTURA * 0.25f, -0.5f);
        glVertex3f(8.0f, -ALTURA * 0.25f, 0);
        glVertex3f(8.0f, ALTURA * 0.25f, 0);
        glVertex3f(8.0f, ALTURA * 0.25f, -0.5f);
        
        // Topo do nicho
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-8.0f, ALTURA * 0.25f, -0.5f);
        glVertex3f(8.0f, ALTURA * 0.25f, -0.5f);
        glVertex3f(8.0f, ALTURA * 0.25f, 0);
        glVertex3f(-8.0f, ALTURA * 0.25f, 0);
        
        // Base do nicho
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-8.0f, -ALTURA * 0.25f, -0.5f);
        glVertex3f(8.0f, -ALTURA * 0.25f, -0.5f);
        glVertex3f(8.0f, -ALTURA * 0.25f, 0);
        glVertex3f(-8.0f, -ALTURA * 0.25f, 0);
    glEnd();
    glPopMatrix();

    // Restante das paredes - mais espessas para evitar atravessar
    glColor3f(0.85f, 0.85f, 0.82f); // Cor cinza claro uniforme
    
    // Parede traseira (mais espessa)
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, base_y, -COMPRIMENTO);
        glVertex3f(LARGURA/2, base_y, -COMPRIMENTO);
        glVertex3f(LARGURA/2, base_y + ALTURA, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, base_y + ALTURA, -COMPRIMENTO);
    glEnd();
    
    // Adicionar espessura à parede traseira
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-LARGURA/2, base_y, -COMPRIMENTO + 1.0f);
        glVertex3f(LARGURA/2, base_y, -COMPRIMENTO + 1.0f);
        glVertex3f(LARGURA/2, base_y + ALTURA, -COMPRIMENTO + 1.0f);
        glVertex3f(-LARGURA/2, base_y + ALTURA, -COMPRIMENTO + 1.0f);
    glEnd();

    // Parede lateral esquerda (mais espessa)
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, base_y, 0);
        glVertex3f(-LARGURA/2, base_y, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, base_y + ALTURA, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, base_y + ALTURA, 0);
    glEnd();
    
    // Adicionar espessura à parede esquerda
    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-LARGURA/2 + 1.0f, base_y, 0);
        glVertex3f(-LARGURA/2 + 1.0f, base_y, -COMPRIMENTO);
        glVertex3f(-LARGURA/2 + 1.0f, base_y + ALTURA, -COMPRIMENTO);
        glVertex3f(-LARGURA/2 + 1.0f, base_y + ALTURA, 0);
    glEnd();

    // Parede lateral direita (mais espessa)
    glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(LARGURA/2, base_y, 0);
        glVertex3f(LARGURA/2, base_y, -COMPRIMENTO);
        glVertex3f(LARGURA/2, base_y + ALTURA, -COMPRIMENTO);
        glVertex3f(LARGURA/2, base_y + ALTURA, 0);
    glEnd();
    
    // Adicionar espessura à parede direita
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(LARGURA/2 - 1.0f, base_y, 0);
        glVertex3f(LARGURA/2 - 1.0f, base_y, -COMPRIMENTO);
        glVertex3f(LARGURA/2 - 1.0f, base_y + ALTURA, -COMPRIMENTO);
        glVertex3f(LARGURA/2 - 1.0f, base_y + ALTURA, 0);
    glEnd();
}
