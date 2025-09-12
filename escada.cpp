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



void desenha_escada() {
    // Escada central que vai do chão até a altura da plataforma
    float altura_degrau = ALTURA_DEGRAU;

    glColor3f(0.6f, 0.6f, 0.6f); // Cor de concreto para escada
    
    for (int i = 0; i < NUM_DEGRAUS; ++i) {
        // Posicionar cada degrau: termina na fachada (Z_INTERNO/2) e vai para trás
        desenha_bloco(X_ESCADA, altura_degrau, PROFUNDIDADE_DEGRAU, 
                      0.0f, i * altura_degrau, Z_INTERNO/2 + Z_ESCADA - (i * PROFUNDIDADE_DEGRAU) + .3f);
    }
    
    // // Desenhar a base frontal no topo da escada (centro do T)
    // desenha_base_frontal();
    
    // Desenhar as rampas laterais partindo da base (braços do T)
    desenha_rampas_laterais();
}
