#include "escada.h"
#include "constantes.h"

void desenha_rampas_laterais() {
    // Rampas laterais que conectam as laterais da igreja ao último degrau da escada
    glColor3f(0.55f, 0.55f, 0.57f); // Cor ligeiramente diferente para as rampas
    
    // Calcular parâmetros das rampas
    float altura_inicial = 0.2f; // Altura inicial das rampas
    float altura_final = (NUM_DEGRAUS - 1) * ALTURA_DEGRAU; // Altura do último degrau
    float altura_total_rampa = altura_final - altura_inicial;
    
    // Posição Z do último degrau da escada
    float z_ultimo_degrau = Z_INTERNO/2 + Z_ESCADA - ((NUM_DEGRAUS - 1) * PROFUNDIDADE_DEGRAU) + 0.3f;
    
    // Largura das rampas
    float largura_rampa = 2.0f;
    
    // Número de segmentos para criar a rampa (usando vários blocos)
    int num_segmentos_rampa = 8;
    float altura_segmento = altura_total_rampa / num_segmentos_rampa;
    
    // Distância horizontal total de cada rampa
    float distancia_horizontal = X_INTERNO/2 - X_ESCADA/2; // Da lateral da igreja até o centro da escada
    float profundidade_segmento = 1.5f; // Profundidade de cada segmento da rampa
    
    // Rampa esquerda (parte de -X_INTERNO/2 e termina em -X_ESCADA/2)
    for (int i = 0; i < num_segmentos_rampa; ++i) {
        float y_segmento = altura_inicial + (i * altura_segmento);
        float x_segmento = -X_INTERNO/2 + (i * (distancia_horizontal / num_segmentos_rampa));
        
        desenha_bloco(largura_rampa, altura_segmento, profundidade_segmento,
                      x_segmento + .3f, y_segmento, z_ultimo_degrau);
    }
    
    // Rampa direita (parte de +X_INTERNO/2 e termina em +X_ESCADA/2)
    for (int i = 0; i < num_segmentos_rampa; ++i) {
        float y_segmento = altura_inicial + (i * altura_segmento);
        float x_segmento = X_INTERNO/2 - (i * (distancia_horizontal / num_segmentos_rampa));
        
        desenha_bloco(largura_rampa, altura_segmento, profundidade_segmento,
                      x_segmento - .3f, y_segmento, z_ultimo_degrau);
    }
}

void desenha_blocos_grama() {
    // Blocos de grama laterais dos lados da escada, embaixo da altura do arco
    glColor3f(0.2f, 0.6f, 0.2f); // Verde da grama
    
    float altura_grama = 0.3f; // Altura dos blocos de grama
    
    // Posição dos blocos - dos lados da escada
    float largura_grama = 6.0f;
    float profundidade_grama = 6.0f;
    float pos_z_grama = Z_INTERNO/2 + 4.0f; // Ligeiramente à frente da escada
    
    // Bloco de grama esquerdo
    desenha_bloco(largura_grama, altura_grama*2, profundidade_grama, 
                  -X_ESCADA/2 - largura_grama/2 - 1.0f, altura_grama/2, pos_z_grama);
    
    // Bloco de grama direito
    desenha_bloco(largura_grama, altura_grama, profundidade_grama, 
                  X_ESCADA/2 + largura_grama/2 + 1.0f, altura_grama/2, pos_z_grama);
}

void desenha_corrimao_escada() {
    // Corrimãos laterais da escada principal
    glColor3f(0.4f, 0.3f, 0.2f); // Cor de madeira escura
    
    float altura_corrimao = 1.0f;
    float espessura_corrimao = 0.1f;
    
    // Postes verticais nas laterais da escada
    for (int i = 0; i < NUM_DEGRAUS; ++i) {
        float z_degrau = Z_INTERNO/2 + Z_ESCADA - (i * PROFUNDIDADE_DEGRAU) + 0.3f;
        float altura_degrau = i * ALTURA_DEGRAU;
        
        // Poste vertical na lateral esquerda da escada
        desenha_bloco(espessura_corrimao, altura_corrimao, espessura_corrimao,
                      -X_ESCADA/2 - 0.2f, altura_degrau + altura_corrimao/2, z_degrau);
        
        // Poste vertical na lateral direita da escada
        desenha_bloco(espessura_corrimao, altura_corrimao, espessura_corrimao,
                      X_ESCADA/2 + 0.2f, altura_degrau + altura_corrimao/2, z_degrau);
    }
    
    // Corrimão horizontal inclinado - seguindo a inclinação da escada
    int num_segmentos_horizontal = 10;
    float comprimento_segmento = Z_ESCADA / num_segmentos_horizontal;
    
    for (int i = 0; i < num_segmentos_horizontal; ++i) {
        float z_segmento = Z_INTERNO/2 + Z_ESCADA - (i * comprimento_segmento) + 0.3f;
        float altura_segmento = (i * ALTURA_DEGRAU * NUM_DEGRAUS / num_segmentos_horizontal) + altura_corrimao;
        
        // Corrimão horizontal esquerdo inclinado
        desenha_bloco(espessura_corrimao, espessura_corrimao, comprimento_segmento,
                      -X_ESCADA/2 - 0.2f, altura_segmento, z_segmento - comprimento_segmento/2);
        
        // Corrimão horizontal direito inclinado
        desenha_bloco(espessura_corrimao, espessura_corrimao, comprimento_segmento,
                      X_ESCADA/2 + 0.2f, altura_segmento, z_segmento - comprimento_segmento/2);
    }
}

void desenha_escada() {
    // Escada central que vai do chão até a altura da plataforma
    float altura_degrau = ALTURA_DEGRAU;

    glColor3f(0.6f, 0.6f, 0.6f); // Cor de concreto para escada
    
    for (int i = 0; i < NUM_DEGRAUS; ++i) {
        // Posicionar cada degrau: termina na fachada (Z_INTERNO/2) e vai para trás
        desenha_bloco(X_ESCADA, altura_degrau, PROFUNDIDADE_DEGRAU, 
                      0.0f, i * altura_degrau, Z_INTERNO/2 + Z_ESCADA - (i * PROFUNDIDADE_DEGRAU) + .3f);
    }
    
    // Desenhar as rampas laterais partindo da base (braços do T)
    desenha_rampas_laterais();
    
    // Desenhar blocos de grama dos lados da escada
    desenha_blocos_grama();
    
    // Desenhar corrimãos da escada e rampas
    desenha_corrimao_escada();
}
