#include "telhado.h"
#include "constantes.h"
#include "texturas.h"
#include "iluminacao.h"

void desenha_telhas() {
    glPushMatrix();
    
    // Calcular altura da cumeeira baseado nas constantes
    float base_y = NIVEL_IGREJA; // Base do telhado na altura da plataforma
    float altura_cumeeira = base_y + PE_DIREITO_IGREJA + ALTURA_TELHADO;
    
    // Aplicar textura de telhas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.telha_colonial);
    sistema_iluminacao.configurar_material_parede();
    glColor3f(0.9f, 0.9f, 0.9f); // Branco para não alterar a cor da textura
    
    // Água esquerda do telhado
    glNormal3f(-INCLINACAO_TELHADO, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-X_INTERNO/2 - 0.075, base_y + PE_DIREITO_IGREJA, Z_INTERNO/2);
        glTexCoord2f(2.0f, 0.0f); glVertex3f(0, altura_cumeeira, Z_INTERNO/2);
        glTexCoord2f(2.0f, 3.0f); glVertex3f(0, altura_cumeeira, -Z_INTERNO/2);
        glTexCoord2f(0.0f, 3.0f); glVertex3f(-X_INTERNO/2 - 0.075, base_y + PE_DIREITO_IGREJA, -Z_INTERNO/2);
    glEnd();
    
    // Água direita do telhado
    glNormal3f(INCLINACAO_TELHADO, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X_INTERNO/2 + 0.075, base_y + PE_DIREITO_IGREJA, Z_INTERNO/2);
        glTexCoord2f(2.0f, 0.0f); glVertex3f(0, altura_cumeeira, Z_INTERNO/2);
        glTexCoord2f(2.0f, 3.0f); glVertex3f(0, altura_cumeeira, -Z_INTERNO/2);
        glTexCoord2f(0.0f, 3.0f); glVertex3f(X_INTERNO/2 + 0.075, base_y + PE_DIREITO_IGREJA, -Z_INTERNO/2);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    // Parâmetros para os prismas triangulares das empenas
    float largura_empena = X_INTERNO + ESPESSURA_PAREDE/2;
    float altura_empena = ALTURA_TELHADO;
    float profundidade_empena = ESPESSURA_PAREDE;
    
    // Posição Y base das empenas (no topo das paredes)
    float pos_y_empena = base_y + PE_DIREITO_IGREJA;
    
    // Empena frontal - com textura de parede externa (MESMA COR DAS OUTRAS PAREDES)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.parede_externa);
    sistema_iluminacao.configurar_material_parede();
    glColor3f(0.95f, 0.95f, 0.9f);  // COR IDÊNTICA às outras paredes
    desenha_prisma_triangular(largura_empena, altura_empena, profundidade_empena,
                              0.0f, pos_y_empena, Z_INTERNO/2 - ESPESSURA_PAREDE/2);
    glDisable(GL_TEXTURE_2D);
    
    // Empena traseira - com vitral colorido
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.vitral);
    sistema_iluminacao.configurar_material_parede();
    glColor3f(0.9f, 0.9f, 0.9f); // Branco para não alterar cor do vitral
    
    desenha_prisma_triangular(largura_empena, altura_empena, profundidade_empena,
                              0.0f, pos_y_empena, -Z_INTERNO/2);
    
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
}
