#include "janela.h"
#include "texturas.h"
#include "iluminacao.h"
#include "constantes.h"
#include <GL/glut.h>

void desenha_janela(float largura, float altura, bool com_vitral) {
    // Moldura da janela (madeira escura)
    sistema_iluminacao.configurar_material_madeira();
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.madeira_escura);
    
    float espessura_moldura = 0.15f;
    
    // Moldura esquerda (vertical)
    glPushMatrix();
    glTranslatef(-largura/2.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        // Frente
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(0, 0, espessura_moldura);
        glTexCoord2f(1, 0); glVertex3f(espessura_moldura, 0, espessura_moldura);
        glTexCoord2f(1, 1); glVertex3f(espessura_moldura, altura, espessura_moldura);
        glTexCoord2f(0, 1); glVertex3f(0, altura, espessura_moldura);
    glEnd();
    glPopMatrix();
    
    // Moldura direita (vertical)
    glPushMatrix();
    glTranslatef(largura/2.0f - espessura_moldura, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(0, 0, espessura_moldura);
        glTexCoord2f(1, 0); glVertex3f(espessura_moldura, 0, espessura_moldura);
        glTexCoord2f(1, 1); glVertex3f(espessura_moldura, altura, espessura_moldura);
        glTexCoord2f(0, 1); glVertex3f(0, altura, espessura_moldura);
    glEnd();
    glPopMatrix();
    
    // Moldura superior (horizontal)
    glPushMatrix();
    glTranslatef(-largura/2.0f, altura - espessura_moldura, 0.0f);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(0, 0, espessura_moldura);
        glTexCoord2f(2, 0); glVertex3f(largura, 0, espessura_moldura);
        glTexCoord2f(2, 1); glVertex3f(largura, espessura_moldura, espessura_moldura);
        glTexCoord2f(0, 1); glVertex3f(0, espessura_moldura, espessura_moldura);
    glEnd();
    glPopMatrix();
    
    // Moldura inferior (horizontal)
    glPushMatrix();
    glTranslatef(-largura/2.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(0, 0, espessura_moldura);
        glTexCoord2f(2, 0); glVertex3f(largura, 0, espessura_moldura);
        glTexCoord2f(2, 1); glVertex3f(largura, espessura_moldura, espessura_moldura);
        glTexCoord2f(0, 1); glVertex3f(0, espessura_moldura, espessura_moldura);
    glEnd();
    glPopMatrix();
    
    // Vidro/Vitral (sempre com blend para transparência)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (com_vitral) {
        glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.vitral);
        sistema_iluminacao.configurar_material_parede();
        glColor4f(1.0f, 1.0f, 1.0f, 0.85f); // Levemente transparente
    } else {
        glDisable(GL_TEXTURE_2D);
        glColor4f(0.7f, 0.85f, 0.95f, 0.5f); // Azul céu semi-transparente
    }
    
    float margem = espessura_moldura + 0.02f;
    glPushMatrix();
    glTranslatef(-largura/2.0f + margem, margem, 0.08f);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(1, 0); glVertex3f(largura - 2*margem, 0, 0);
        glTexCoord2f(1, 1); glVertex3f(largura - 2*margem, altura - 2*margem, 0);
        glTexCoord2f(0, 1); glVertex3f(0, altura - 2*margem, 0);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
}

void desenha_janelas_laterais() {
    // Calcular posições exatas onde estão os buracos das janelas nas paredes
    float janela_largura = 2.0f;
    float janela_altura = 1.5f;
    float espaco_janelas = (Z_INTERNO - (ESPESSURA_PAREDE * 2)) / 4.0f;
    
    // Altura ajustada: desce uma vez a altura da janela para encaixar perfeitamente
    float altura_base = ALTURA_PLATAFORMA + (PE_DIREITO_IGREJA - janela_altura)/2;
    
    // Apenas as 2 primeiras janelas (mais próximas da frente/entrada)
    float pos_z_esquerdo[] = {
        -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura/2,  // Janela 1 (mais à frente)
        -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + janela_largura + janela_largura/2  // Janela 2
    };
    
    // Janelas do lado esquerdo (2 janelas)
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-X_INTERNO/2, altura_base, pos_z_esquerdo[i]);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotacionar para face lateral
        desenha_janela(janela_largura, janela_altura, true);
        glPopMatrix();
    }
    
    // Janelas do lado direito (2 janelas espelhadas)
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(X_INTERNO/2, altura_base, pos_z_esquerdo[i]);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Rotacionar para face lateral
        desenha_janela(janela_largura, janela_altura, true);
        glPopMatrix();
    }
}
