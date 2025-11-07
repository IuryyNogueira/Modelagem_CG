#include "parede.h"
#include "constantes.h"
#include "texturas.h"
#include "iluminacao.h"
#include <cmath>

void desenha_plataforma() {
    // Aplicar textura de mármore na plataforma externa
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.piso_marmore);
    sistema_iluminacao.configurar_material_marmore();
    glColor3f(0.95f, 0.95f, 0.95f); // Branco levemente cinza
    
    // Desenhar o bloco da plataforma
    desenha_bloco(X_PLATAFORMA_IGREJA, ALTURA_PLATAFORMA, Z_PLATAFORMA_IGREJA);
    
    // Desenhar a superfície superior com coordenadas de textura apropriadas
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-X_PLATAFORMA_IGREJA/2, ALTURA_PLATAFORMA, -Z_PLATAFORMA_IGREJA/2);
        glTexCoord2f(8.0f, 0.0f); 
        glVertex3f(X_PLATAFORMA_IGREJA/2, ALTURA_PLATAFORMA, -Z_PLATAFORMA_IGREJA/2);
        glTexCoord2f(8.0f, 10.0f); 
        glVertex3f(X_PLATAFORMA_IGREJA/2, ALTURA_PLATAFORMA, Z_PLATAFORMA_IGREJA/2);
        glTexCoord2f(0.0f, 10.0f); 
        glVertex3f(-X_PLATAFORMA_IGREJA/2, ALTURA_PLATAFORMA, Z_PLATAFORMA_IGREJA/2);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void desenha_parede() {
    // Configurar textura e material das paredes
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.parede_externa);
    sistema_iluminacao.configurar_material_parede();
    glColor3f(0.95f, 0.95f, 0.9f);
    
    // Parede esquerda com buracos para janelas (3 janelas)
    // ESTENDIDA para cobrir toda a profundidade até as extremidades
    float janela_largura = 2.0f;
    float janela_altura = 1.5f;
    float espaco_janelas = (Z_INTERNO - (ESPESSURA_PAREDE * 2)) / 4.0f; // 4 espaços entre 3 janelas
    
    // Segmentos da parede esquerda - ESTENDIDOS para cobrir até as extremidades
    // Segmento traseiro (mais para trás)
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas + ESPESSURA_PAREDE, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + (espaco_janelas + ESPESSURA_PAREDE)/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura/2); // Base janela 1
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura/2); // Topo janela 1
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + janela_largura + janela_largura/2); // Base janela 2
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + janela_largura + janela_largura/2); // Topo janela 2
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + 2*janela_largura + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 3*espaco_janelas + 2*janela_largura + janela_largura/2); // Base janela 3
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + 3*espaco_janelas + 2*janela_largura + janela_largura/2); // Topo janela 3
    
    // Segmento frontal (mais para frente) - ESTENDIDO até a frente
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas + ESPESSURA_PAREDE, -X_INTERNO/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - (espaco_janelas + ESPESSURA_PAREDE)/2);
    
    // Parede direita com buracos para janelas (3 janelas) - espelhada e ESTENDIDA
    // Segmento traseiro (mais para trás)
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas + ESPESSURA_PAREDE, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + (espaco_janelas + ESPESSURA_PAREDE)/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura/2); // Base janela 1
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura/2); // Topo janela 1
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + janela_largura + janela_largura/2); // Base janela 2
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + janela_largura + janela_largura/2); // Topo janela 2
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + 2*janela_largura + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 3*espaco_janelas + 2*janela_largura + janela_largura/2); // Base janela 3
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + 3*espaco_janelas + 2*janela_largura + janela_largura/2); // Topo janela 3
    
    // Segmento frontal (mais para frente) - ESTENDIDO até a frente
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas + ESPESSURA_PAREDE, X_INTERNO/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - (espaco_janelas + ESPESSURA_PAREDE)/2);
    
    // Parede traseira com textura de parede externa (mesma das outras)
    // ESTENDIDA para cobrir toda a largura incluindo cantos
    glColor3f(0.95f, 0.95f, 0.9f);
    desenha_bloco(X_INTERNO + ESPESSURA_PAREDE, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, 0.0, ALTURA_PLATAFORMA, -Z_INTERNO/2);
    
    // Paredes frontais laterais (próximas à porta) - mesma textura
    // ESTENDIDAS para cobrir melhor os cantos
    desenha_bloco(12.0f + ESPESSURA_PAREDE/2, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, -X_INTERNO/2 + 12.0f/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - .075);
    desenha_bloco(12.0f + ESPESSURA_PAREDE/2, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, X_INTERNO/2 - 12.0f/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - .075);
    
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.madeira_escura);
    sistema_iluminacao.configurar_material_madeira();
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.6f, 0.4f, 0.2f); // Cor de madeira escura
    
    // Porta esquerda com rotação - buraco está entre (-X_INTERNO/2 + 12.0f) e centro
    // Centro do buraco esquerdo: (-X_INTERNO/2 + 12.0f + 0.0f) / 2 = -X_INTERNO/2 + 6.0f
    glPushMatrix();
    glTranslatef(-X_INTERNO/2 + 12.0f - 0.6f, ALTURA_PLATAFORMA, Z_INTERNO/2 - 0.75f); // Porta um pouco mais à frente
    glRotatef(angulo_porta, 0.0f, 1.0f, 0.0f); // Abre para fora (sentido correto)
    desenha_bloco(0.05f, 2.1f, 1.2f, 0.6f, 0.0f, 0.0f); // Porta esquerda
    glPopMatrix();
    
    // Porta direita com rotação - buraco está entre centro e (X_INTERNO/2 - 12.0f)
    // Centro do buraco direito: (0.0f + X_INTERNO/2 - 12.0f) / 2 = X_INTERNO/2 - 6.0f  
    glPushMatrix();
    glTranslatef(X_INTERNO/2 - 12.0f + 0.6f, ALTURA_PLATAFORMA, Z_INTERNO/2 - 0.75f); // Porta um pouco mais à frente
    glRotatef(-angulo_porta, 0.0f, 0.5f, 0.0f); // Abre para fora (sentido correto)
    desenha_bloco(0.05f, 2.1f, 1.2f, -0.6f, 0.0f, 0.0f); // Porta direita
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    
    // Parede frontal central (área entre as portas) - textura padrão
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.parede_externa);
    sistema_iluminacao.configurar_material_parede();
    glColor3f(0.95f, 0.95f, 0.9f);
    desenha_bloco(8.3f, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, 0.0f, ALTURA_PLATAFORMA, Z_INTERNO/2 - 1.4f); // Parede frontal central (com porta)
    
    // Paredes finas entre porta e paredes laterais
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - 2.1f, 1.2f, -X_INTERNO/2 + 12.0f - .075f, ALTURA_PLATAFORMA + 2.1, Z_INTERNO/2 - .75f); // Parede frontal entre porta e parede esquerda
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - 2.1f, 1.2f, X_INTERNO/2 - 12.0f + .075f, ALTURA_PLATAFORMA + 2.1, Z_INTERNO/2 - .75f); // Parede frontal entre porta e parede direita
    
    // Parte superior da parede frontal (acima da porta)
    desenha_bloco(8.3f, ESPESSURA_PAREDE, 1.2f, 0.0f, ALTURA_PLATAFORMA + PE_DIREITO_IGREJA, Z_INTERNO/2 - .75f);
    glDisable(GL_TEXTURE_2D);

}
