#include "telhado.h"
#include "constantes.h"

void desenha_telhas() {
    glPushMatrix();
    
    // Calcular altura da cumeeira baseado nas constantes
    float base_y = NIVEL_IGREJA; // Base do telhado na altura da plataforma
    float altura_cumeeira = base_y + PE_DIREITO_IGREJA + ALTURA_TELHADO;
    
    // Cor de telha colonial
    glColor3f(0.7f, 0.3f, 0.2f);
    
    // Água esquerda do telhado
    glNormal3f(-INCLINACAO_TELHADO, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-X_INTERNO/2 - 0.075, base_y + PE_DIREITO_IGREJA, Z_INTERNO/2);
        glVertex3f(0, altura_cumeeira, Z_INTERNO/2);
        glVertex3f(0, altura_cumeeira, -Z_INTERNO/2);
        glVertex3f(-X_INTERNO/2 - 0.075, base_y + PE_DIREITO_IGREJA, -Z_INTERNO/2);
    glEnd();
    
    // Água direita do telhado
    glNormal3f(INCLINACAO_TELHADO, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(X_INTERNO/2 + 0.075, base_y + PE_DIREITO_IGREJA, Z_INTERNO/2);
        glVertex3f(0, altura_cumeeira, Z_INTERNO/2);
        glVertex3f(0, altura_cumeeira, -Z_INTERNO/2);
        glVertex3f(X_INTERNO/2 + 0.075, base_y + PE_DIREITO_IGREJA, -Z_INTERNO/2);
    glEnd();
    
    // Empenas (prismas triangulares frontais e traseiros) - mesma cor das paredes
    glColor3f(0.95f, 0.95f, 0.9f);
    
    // Parâmetros para os prismas triangulares das empenas
    float largura_empena = X_INTERNO + ESPESSURA_PAREDE/2;
    float altura_empena = ALTURA_TELHADO;
    float profundidade_empena = ESPESSURA_PAREDE;
    
    // Posição Y base das empenas (no topo das paredes)
    float pos_y_empena = base_y + PE_DIREITO_IGREJA;
    
    // Empena frontal - usando desenha_prisma_triangular
    desenha_prisma_triangular(largura_empena, altura_empena, profundidade_empena,
                              0.0f, pos_y_empena, Z_INTERNO/2 - ESPESSURA_PAREDE/2);
    
    // Empena traseira - usando desenha_prisma_triangular
    desenha_prisma_triangular(largura_empena, altura_empena, profundidade_empena,
                              0.0f, pos_y_empena, -Z_INTERNO/2);
    
    glPopMatrix();
}
