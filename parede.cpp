#include "parede.h"
#include "constantes.h"
#include <cmath>

void desenha_plataforma() {
    desenha_bloco(X_PLATAFORMA_IGREJA, ALTURA_PLATAFORMA, Z_PLATAFORMA_IGREJA);
}

void desenha_parede() {
    glColor3f(0.95f, 0.95f, 0.9f);
    
    // Parede esquerda com buracos para janelas (3 janelas)
    float janela_largura = 2.0f;
    float janela_altura = 1.5f;
    float espaco_janelas = (Z_INTERNO - (ESPESSURA_PAREDE * 2)) / 4.0f; // 4 espaços entre 3 janelas
    
    // Segmentos da parede esquerda
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura/2); // Base janela 1
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura/2); // Topo janela 1
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + janela_largura + janela_largura/2); // Base janela 2
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + janela_largura + janela_largura/2); // Topo janela 2
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + 2*janela_largura + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 3*espaco_janelas + 2*janela_largura + janela_largura/2); // Base janela 3
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, -X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + 3*espaco_janelas + 2*janela_largura + janela_largura/2); // Topo janela 3
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, -X_INTERNO/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - ESPESSURA_PAREDE - espaco_janelas/2);
    
    // Parede direita com buracos para janelas (3 janelas) - espelhada
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura/2); // Base janela 1
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura/2); // Topo janela 1
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + espaco_janelas + janela_largura + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + janela_largura + janela_largura/2); // Base janela 2
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + janela_largura + janela_largura/2); // Topo janela 2
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 2*espaco_janelas + 2*janela_largura + espaco_janelas/2);
    desenha_bloco(ESPESSURA_PAREDE, janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA, -Z_INTERNO/2 + ESPESSURA_PAREDE + 3*espaco_janelas + 2*janela_largura + janela_largura/2); // Base janela 3
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - janela_altura, janela_largura, X_INTERNO/2, ALTURA_PLATAFORMA + janela_altura + (PE_DIREITO_IGREJA - janela_altura)/2, -Z_INTERNO/2 + ESPESSURA_PAREDE + 3*espaco_janelas + 2*janela_largura + janela_largura/2); // Topo janela 3
    
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, espaco_janelas, X_INTERNO/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - ESPESSURA_PAREDE - espaco_janelas/2);
    
    // Parede traseira (sem mudança)
    desenha_bloco(X_INTERNO, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, 0.0, ALTURA_PLATAFORMA, -Z_INTERNO/2);
    
    // Paredes frontais (sem mudança)
    desenha_bloco(12.0f, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, -X_INTERNO/2 + 12.0f/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - .075);
    desenha_bloco(12.0f, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, X_INTERNO/2 - 12.0f/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - .075);

    glColor3f(0.59f, 0.29f, 0.0);
    
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

    glColor3f(1.0f, 0.7f, 0.5f);
    desenha_bloco(8.3f, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, 0.0f, ALTURA_PLATAFORMA, Z_INTERNO/2 - 1.4f); // Parede frontal central (com porta)
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - 2.1f, 1.2f, -X_INTERNO/2 + 12.0f - .075f, ALTURA_PLATAFORMA + 2.1, Z_INTERNO/2 - .75f); // Parede frontal entre porta e parede esquerda
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - 2.1f, 1.2f, X_INTERNO/2 - 12.0f + .075f, ALTURA_PLATAFORMA + 2.1, Z_INTERNO/2 - .75f); // Parede frontal entre porta e parede direita
    desenha_bloco(8.3f, ESPESSURA_PAREDE, 1.2f, 0.0f, ALTURA_PLATAFORMA + PE_DIREITO_IGREJA, Z_INTERNO/2 - .75f); // Parte superior da parede frontal (acima da porta)

}
