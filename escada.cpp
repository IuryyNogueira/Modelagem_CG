#include "escada.h"
#include "constantes.h"

// void desenha_base_frontal() {
//     // Base horizontal na frente da escada (não invade a igreja)
//     glColor3f(0.7f, 0.7f, 0.75f);
    
//     float largura_base = X_ESCADA + 6.0f; 
//     float profundidade_base = 2.0f; 
//     float altura_base = 0.2f; 
//     float y_base = ALTURA_PLATAFORMA - altura_base; 
//     float z_base = 3.0f; // NA FRENTE da escada, não invade a igreja
    
//     glBegin(GL_QUADS);
//         // Topo da base
//         glNormal3f(0.0f, 1.0f, 0.0f);
//         glVertex3f(-largura_base/2, ALTURA_PLATAFORMA, z_base);
//         glVertex3f(largura_base/2, ALTURA_PLATAFORMA, z_base);
//         glVertex3f(largura_base/2, ALTURA_PLATAFORMA, z_base + profundidade_base);
//         glVertex3f(-largura_base/2, ALTURA_PLATAFORMA, z_base + profundidade_base);
        
//         // Frente da base
//         glNormal3f(0.0f, 0.0f, 1.0f);
//         glVertex3f(-largura_base/2, y_base, z_base);
//         glVertex3f(largura_base/2, y_base, z_base);
//         glVertex3f(largura_base/2, ALTURA_PLATAFORMA, z_base);
//         glVertex3f(-largura_base/2, ALTURA_PLATAFORMA, z_base);
        
//         // Traseira da base
//         glNormal3f(0.0f, 0.0f, -1.0f);
//         glVertex3f(-largura_base/2, y_base, z_base + profundidade_base);
//         glVertex3f(largura_base/2, y_base, z_base + profundidade_base);
//         glVertex3f(largura_base/2, ALTURA_PLATAFORMA, z_base + profundidade_base);
//         glVertex3f(-largura_base/2, ALTURA_PLATAFORMA, z_base + profundidade_base);
        
//         // Laterais da base
//         glNormal3f(-1.0f, 0.0f, 0.0f);
//         glVertex3f(-largura_base/2, y_base, z_base);
//         glVertex3f(-largura_base/2, y_base, z_base + profundidade_base);
//         glVertex3f(-largura_base/2, ALTURA_PLATAFORMA, z_base + profundidade_base);
//         glVertex3f(-largura_base/2, ALTURA_PLATAFORMA, z_base);
        
//         glNormal3f(1.0f, 0.0f, 0.0f);
//         glVertex3f(largura_base/2, y_base, z_base);
//         glVertex3f(largura_base/2, y_base, z_base + profundidade_base);
//         glVertex3f(largura_base/2, ALTURA_PLATAFORMA, z_base + profundidade_base);
//         glVertex3f(largura_base/2, ALTURA_PLATAFORMA, z_base);
//     glEnd();
// }

// void desenha_rampas_laterais() {
//     // Rampas que se conectam diretamente à base
//     glColor3f(0.58f, 0.58f, 0.6f);
    
//     float largura_base = X_ESCADA + 6.0f; 
//     float largura_rampa = 2.0f; 
//     float comprimento_rampa = 8.0f; 
//     float altura_inicial = ALTURA_PLATAFORMA; 
//     int degraus_rampa = 4; 
//     float altura_degrau_rampa = altura_inicial / degraus_rampa;
//     float profundidade_degrau_rampa = comprimento_rampa / degraus_rampa;
//     float z_base = 3.0f; // Mesma posição Z da base
    
//     // Rampa esquerda - conecta diretamente à lateral esquerda da base
//     for (int i = 0; i < degraus_rampa; ++i) {
//         float y_cima = altura_inicial - i * altura_degrau_rampa;
//         float y_baixo = altura_inicial - (i + 1) * altura_degrau_rampa;
//         float x_inicio = -largura_base/2; // Exatamente na borda da base
//         float x_fim = x_inicio - profundidade_degrau_rampa; // Vai para a esquerda
        
//         // Topo do degrau
//         glNormal3f(0.0f, 1.0f, 0.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(x_inicio - i * profundidade_degrau_rampa, y_cima, z_base);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_cima, z_base);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//             glVertex3f(x_inicio - i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//         glEnd();
        
//         // Frente do degrau
//         glNormal3f(-1.0f, 0.0f, 0.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_baixo, z_base);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_baixo, z_base + largura_rampa);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_cima, z_base);
//         glEnd();
        
//         // Laterais
//         glNormal3f(0.0f, 0.0f, 1.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(x_inicio - i * profundidade_degrau_rampa, y_baixo, z_base + largura_rampa);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_baixo, z_base + largura_rampa);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//             glVertex3f(x_inicio - i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//         glEnd();
        
//         glNormal3f(0.0f, 0.0f, -1.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(x_inicio - i * profundidade_degrau_rampa, y_baixo, z_base);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_baixo, z_base);
//             glVertex3f(x_fim - i * profundidade_degrau_rampa, y_cima, z_base);
//             glVertex3f(x_inicio - i * profundidade_degrau_rampa, y_cima, z_base);
//         glEnd();
//     }
    
//     // Rampa direita - conecta diretamente à lateral direita da base
//     for (int i = 0; i < degraus_rampa; ++i) {
//         float y_cima = altura_inicial - i * altura_degrau_rampa;
//         float y_baixo = altura_inicial - (i + 1) * altura_degrau_rampa;
//         float x_inicio = largura_base/2; // Exatamente na borda da base
//         float x_fim = x_inicio + profundidade_degrau_rampa; // Vai para a direita
        
//         // Topo do degrau
//         glNormal3f(0.0f, 1.0f, 0.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(x_inicio + i * profundidade_degrau_rampa, y_cima, z_base);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_cima, z_base);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//             glVertex3f(x_inicio + i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//         glEnd();
        
//         // Frente do degrau
//         glNormal3f(1.0f, 0.0f, 0.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_baixo, z_base);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_baixo, z_base + largura_rampa);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_cima, z_base);
//         glEnd();
        
//         // Laterais
//         glNormal3f(0.0f, 0.0f, 1.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(x_inicio + i * profundidade_degrau_rampa, y_baixo, z_base + largura_rampa);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_baixo, z_base + largura_rampa);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//             glVertex3f(x_inicio + i * profundidade_degrau_rampa, y_cima, z_base + largura_rampa);
//         glEnd();
        
//         glNormal3f(0.0f, 0.0f, -1.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(x_inicio + i * profundidade_degrau_rampa, y_baixo, z_base);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_baixo, z_base);
//             glVertex3f(x_fim + i * profundidade_degrau_rampa, y_cima, z_base);
//             glVertex3f(x_inicio + i * profundidade_degrau_rampa, y_cima, z_base);
//         glEnd();
//     }
// }

// void desenha_escada() {
//     // Escada central (linha vertical do T) - vai do chão até a altura máxima
//     float altura_total = ALTURA_PLATAFORMA;
//     int degraus = 6;
//     float altura_degrau = altura_total / degraus;
//     float profundidade_degrau = PROFUNDIDADE_ESCADA / degraus;

//     glColor3f(0.6f, 0.6f, 0.6f); // Cor de concreto para escada
    
//     for (int i = 0; i < degraus; ++i) {
//         float y_baixo = i * altura_degrau;
//         float y_cima = (i + 1) * altura_degrau;
//         float z_frente = -(i + 1) * profundidade_degrau; // Negativo para ir em direção à porta
//         float z_tras = -i * profundidade_degrau;

//         // Topo do degrau
//         glNormal3f(0.0f, 1.0f, 0.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(-X_ESCADA/2, y_cima, z_tras);
//             glVertex3f(X_ESCADA/2, y_cima, z_tras);
//             glVertex3f(X_ESCADA/2, y_cima, z_frente);
//             glVertex3f(-X_ESCADA/2, y_cima, z_frente);
//         glEnd();

//         // Frente do degrau (espelho)
//         glNormal3f(0.0f, 0.0f, -1.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(-X_ESCADA/2, y_baixo, z_frente);
//             glVertex3f(X_ESCADA/2, y_baixo, z_frente);
//             glVertex3f(X_ESCADA/2, y_cima, z_frente);
//             glVertex3f(-X_ESCADA/2, y_cima, z_frente);
//         glEnd();
        
//         // Laterais do degrau
//         glNormal3f(-1.0f, 0.0f, 0.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(-X_ESCADA/2, y_baixo, z_tras);
//             glVertex3f(-X_ESCADA/2, y_baixo, z_frente);
//             glVertex3f(-X_ESCADA/2, y_cima, z_frente);
//             glVertex3f(-X_ESCADA/2, y_cima, z_tras);
//         glEnd();
        
//         glNormal3f(1.0f, 0.0f, 0.0f);
//         glBegin(GL_QUADS);
//             glVertex3f(X_ESCADA/2, y_baixo, z_tras);
//             glVertex3f(X_ESCADA/2, y_baixo, z_frente);
//             glVertex3f(X_ESCADA/2, y_cima, z_frente);
//             glVertex3f(X_ESCADA/2, y_cima, z_tras);
//         glEnd();
//     }
    
//     // Desenhar a base frontal no topo da escada (centro do T)
//     desenha_base_frontal();
    
//     // Desenhar as rampas laterais partindo da base (braços do T)
//     desenha_rampas_laterais();
// }
