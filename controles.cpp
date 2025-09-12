#include "controles.h"
#include "constantes.h"
#include "igreja.h"
#include <cmath>
#include <iostream>
#include <string>

// Função para desenhar texto na tela
void desenha_texto(float x, float y, const std::string& texto) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    
    for (char c : texto) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// Função para desenhar interface
void desenha_interface() {
    if (proximo_da_porta) {
        std::string estado = porta_aberta ? "ABERTAS" : "FECHADAS";
        std::string acao = porta_aberta ? "fechar" : "abrir";
        desenha_texto(10, glutGet(GLUT_WINDOW_HEIGHT) - 30, "Pressione E para " + acao + " as portas");
        desenha_texto(10, glutGet(GLUT_WINDOW_HEIGHT) - 50, "Portas laterais: " + estado);
    }
    
    // Controles sempre visíveis
    desenha_texto(10, 50, "Controles: WASD - Movimento | Mouse - Olhar | R/T - Rotar | ESC - Sair");
}

// Função para desenhar o chão
void desenha_chao() {
    float tamanho = 200.0f;
    
    // Chão principal - concreto urbano como na imagem
    glColor3f(0.6f, 0.6f, 0.62f); // Cinza concreto
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-tamanho, 0.0f, -tamanho);
        glVertex3f( tamanho, 0.0f, -tamanho);
        glVertex3f( tamanho, 0.0f,  tamanho);
        glVertex3f(-tamanho, 0.0f,  tamanho);
    glEnd();
    
    // Adicionar algumas linhas de divisão no concreto
    glColor3f(0.5f, 0.5f, 0.52f); // Linha mais escura
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        // Linhas horizontais
        for (int i = -5; i <= 5; i++) {
            glVertex3f(-tamanho, 0.01f, i * 20.0f);
            glVertex3f(tamanho, 0.01f, i * 20.0f);
        }
        // Linhas verticais
        for (int i = -5; i <= 5; i++) {
            glVertex3f(i * 20.0f, 0.01f, -tamanho);
            glVertex3f(i * 20.0f, 0.01f, tamanho);
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Cálculo da direção da câmera
    float dx = sin(dir) * cos(pitch);
    float dy = sin(pitch);
    float dz = -cos(dir) * cos(pitch);

    gluLookAt(
        pos_x, pos_y, pos_z, // posição da câmera
        pos_x + dx, pos_y + dy, pos_z + dz, // ponto para onde olha
        0.0f, 1.0f, 0.0f // vetor up
    );

    desenha_chao();
    desenha_igreja();
    desenha_interface();
    glutSwapBuffers();
}

void redimensiona(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void teclado(unsigned char key, int x, int y) {
    keyStates[key] = true;
    
    // Controle da porta com tecla E
    if ((key == 'e' || key == 'E') && proximo_da_porta) {
        porta_aberta = !porta_aberta;
    }
    
    if (key == 27) // ESC
        exit(0);
}

void teclado_up(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void atualiza_camera_mouse(int x, int y) {
    if (!mouse_initialized) {
        last_mouse_x = x;
        last_mouse_y = y;
        mouse_initialized = true;
        return;
    }
    int dx = x - last_mouse_x;
    int dy = y - last_mouse_y;
    last_mouse_x = x;
    last_mouse_y = y;

    dir += dx * SENS_MOUSE;
    pitch += -dy * SENS_MOUSE;
    if (pitch > 1.2f) pitch = 1.2f;
    if (pitch < -1.2f) pitch = -1.2f;

    glutPostRedisplay();
}

void atualiza_movimento() {
    // Animação da porta
    if (porta_aberta && angulo_porta < 90.0f) {
        angulo_porta += 2.0f; // Velocidade de abertura
        if (angulo_porta > 90.0f) angulo_porta = 90.0f;
    } else if (!porta_aberta && angulo_porta > 0.0f) {
        angulo_porta -= 2.0f; // Velocidade de fechamento
        if (angulo_porta < 0.0f) angulo_porta = 0.0f;
    }
    
    // Verificar proximidade das portas laterais (centro dos buracos reais)
    float pos_porta_esq_x = (-X_INTERNO/2 + 12.0f + 0.0f) / 2.0f;  // Centro do buraco esquerdo
    float pos_porta_dir_x = (0.0f + X_INTERNO/2 - 12.0f) / 2.0f;   // Centro do buraco direito
    float pos_porta_z = Z_INTERNO/2 + 0.1f;                        // Posição Z correta das portas (mais à frente)
    
    float dist_porta_esq = sqrt(pow(pos_x - pos_porta_esq_x, 2) + pow(pos_z - pos_porta_z, 2));
    float dist_porta_dir = sqrt(pow(pos_x - pos_porta_dir_x, 2) + pow(pos_z - pos_porta_z, 2));
    
    proximo_da_porta = (dist_porta_esq < 3.0f || dist_porta_dir < 3.0f);
    
    float move_x = 0.0f, move_z = 0.0f;
    
    // Movimento com WASD
    if (keyStates['w']) {
        move_x += sin(dir);
        move_z += -cos(dir);
    }
    if (keyStates['s']) {
        move_x -= sin(dir);
        move_z -= -cos(dir);
    }
    if (keyStates['a']) {
        move_x -= cos(dir);
        move_z -= sin(dir);
    }
    if (keyStates['d']) {
        move_x += cos(dir);
        move_z += sin(dir);
    }
    
    // Rotação com R e T
    if (keyStates['r'] || keyStates['R']) {
        dir += SENSIBILIDADE; // Rotaciona para a direita
    }
    if (keyStates['t'] || keyStates['T']) {
        dir -= SENSIBILIDADE; // Rotaciona para a esquerda
    }
    
    // Normaliza e aplica movimento com detecção de colisão
    float len = sqrt(move_x * move_x + move_z * move_z);
    if (len > 0.01f) {
        move_x /= len;
        move_z /= len;
        
        // Calcular nova posição
        float nova_pos_x = pos_x + move_x * VELOCIDADE * 0.3f;
        float nova_pos_z = pos_z + move_z * VELOCIDADE * 0.3f;
        
        // Detecção de colisão com as paredes baseada nos blocos reais
        bool colisao = false;
        float margem = 0.5f; // Margem para não encostar diretamente na parede
        
        // Baseado nas paredes definidas em parede.cpp:
        
        // Parede esquerda: posX = -X_INTERNO/2, largura = ESPESSURA_PAREDE
        // Limites: X de (-X_INTERNO/2 - ESPESSURA_PAREDE/2) até (-X_INTERNO/2 + ESPESSURA_PAREDE/2)
        float parede_esq_min = -X_INTERNO/2 - ESPESSURA_PAREDE/2 - margem;
        float parede_esq_max = -X_INTERNO/2 + ESPESSURA_PAREDE/2 + margem;
        
        // Parede direita: posX = X_INTERNO/2, largura = ESPESSURA_PAREDE  
        float parede_dir_min = X_INTERNO/2 - ESPESSURA_PAREDE/2 - margem;
        float parede_dir_max = X_INTERNO/2 + ESPESSURA_PAREDE/2 + margem;
        
        // Parede traseira: posZ = -Z_INTERNO/2, profundidade = ESPESSURA_PAREDE
        float parede_tras_min = -Z_INTERNO/2 - ESPESSURA_PAREDE/2 - margem;
        float parede_tras_max = -Z_INTERNO/2 + ESPESSURA_PAREDE/2 + margem;
        
        // Paredes frontais (duas laterais + central pequena)
        // Parede frontal esquerda: posX = -X_INTERNO/2 + 12.0f/2, largura = 12.0f
        float parede_front_esq_min = (-X_INTERNO/2 + 12.0f/2) - 12.0f/2 - margem;
        float parede_front_esq_max = (-X_INTERNO/2 + 12.0f/2) + 12.0f/2 + margem;
        
        // Parede frontal direita: posX = X_INTERNO/2 - 12.0f/2, largura = 12.0f
        float parede_front_dir_min = (X_INTERNO/2 - 12.0f/2) - 12.0f/2 - margem;
        float parede_front_dir_max = (X_INTERNO/2 - 12.0f/2) + 12.0f/2 + margem;
        
        // Parede frontal central: posX = 0.0f, largura = ESPESSURA_PAREDE
        float parede_front_cent_min = 0.0f - ESPESSURA_PAREDE/2 - margem;
        float parede_front_cent_max = 0.0f + ESPESSURA_PAREDE/2 + margem;
        
        // Posição Z das paredes frontais
        float parede_front_z = Z_INTERNO/2 - 0.075f;
        float parede_front_z_min = parede_front_z - ESPESSURA_PAREDE/2 - margem;
        float parede_front_z_max = parede_front_z + ESPESSURA_PAREDE/2 + margem;
        
        // Verificar colisão com parede esquerda
        if (nova_pos_x >= parede_esq_min && nova_pos_x <= parede_esq_max &&
            nova_pos_z >= -Z_INTERNO/2 && nova_pos_z <= Z_INTERNO/2) {
            colisao = true;
        }
        
        // Verificar colisão com parede direita
        if (nova_pos_x >= parede_dir_min && nova_pos_x <= parede_dir_max &&
            nova_pos_z >= -Z_INTERNO/2 && nova_pos_z <= Z_INTERNO/2) {
            colisao = true;
        }
        
        // Verificar colisão com parede traseira
        if (nova_pos_z >= parede_tras_min && nova_pos_z <= parede_tras_max &&
            nova_pos_x >= -X_INTERNO/2 && nova_pos_x <= X_INTERNO/2) {
            colisao = true;
        }
        
        // Verificar colisão com paredes frontais
        if (nova_pos_z >= parede_front_z_min && nova_pos_z <= parede_front_z_max) {
            // Parede frontal esquerda
            if (nova_pos_x >= parede_front_esq_min && nova_pos_x <= parede_front_esq_max) {
                colisao = true;
            }
            // Parede frontal direita
            if (nova_pos_x >= parede_front_dir_min && nova_pos_x <= parede_front_dir_max) {
                colisao = true;
            }
            // Parede frontal central (pequena)
            if (nova_pos_x >= parede_front_cent_min && nova_pos_x <= parede_front_cent_max) {
                colisao = true;
            }
        }
        
        // Verificar colisão com portas laterais (só se estiverem fechadas)
        if (angulo_porta < 45.0f) { // Portas consideradas fechadas se ângulo < 45°
            float porta_z = Z_INTERNO/2 + 0.1f; // Posição Z correta das portas (mais à frente)
            float porta_z_min = porta_z - 0.6f - margem;
            float porta_z_max = porta_z + 0.6f + margem;
            
            // Porta esquerda (centro do buraco real)
            float porta_esq_x = (-X_INTERNO/2 + 12.0f + 0.0f) / 2.0f;
            float porta_esq_x_min = porta_esq_x - 0.6f - margem;
            float porta_esq_x_max = porta_esq_x + 0.6f + margem;
            
            if (nova_pos_z >= porta_z_min && nova_pos_z <= porta_z_max &&
                nova_pos_x >= porta_esq_x_min && nova_pos_x <= porta_esq_x_max) {
                colisao = true;
            }
            
            // Porta direita (centro do buraco real)
            float porta_dir_x = (0.0f + X_INTERNO/2 - 12.0f) / 2.0f;
            float porta_dir_x_min = porta_dir_x - 0.6f - margem;
            float porta_dir_x_max = porta_dir_x + 0.6f + margem;
            
            if (nova_pos_z >= porta_z_min && nova_pos_z <= porta_z_max &&
                nova_pos_x >= porta_dir_x_min && nova_pos_x <= porta_dir_x_max) {
                colisao = true;
            }
        }
        
        // Verificar colisão com a escada
        // A escada está posicionada no centro (X=0) e vai de Z_INTERNO/2+0.3f para trás por Z_ESCADA
        float escada_x_min = -X_ESCADA/2 - margem;
        float escada_x_max = X_ESCADA/2 + margem;
        float escada_z_frente = Z_INTERNO/2 + 0.3f + margem;  // Frente da escada (mais à frente)
        float escada_z_tras = Z_INTERNO/2 + 0.3f - Z_ESCADA - margem; // Trás da escada
        
        // Verificar se o jogador está na área horizontal da escada
        if (nova_pos_x >= escada_x_min && nova_pos_x <= escada_x_max &&
            nova_pos_z >= escada_z_tras && nova_pos_z <= escada_z_frente) {
            
            // Calcular a altura esperada do degrau na posição Z do jogador
            float pos_relativa_z = escada_z_frente - nova_pos_z; // Distância da frente da escada
            int degrau_atual = (int)(pos_relativa_z / PROFUNDIDADE_DEGRAU);
            
            // Limitar o degrau aos limites válidos
            if (degrau_atual >= 0 && degrau_atual < NUM_DEGRAUS) {
                float altura_degrau_atual = degrau_atual * ALTURA_DEGRAU;
                
                // Se o jogador está no nível do chão (pos_y ~= 0) e deveria estar num degrau elevado,
                // impedir o movimento (simula que não pode atravessar o degrau)
                if (pos_y < altura_degrau_atual + 0.5f) {
                    colisao = true;
                }
            }
        }
        
        // Verificar colisão com o altar (posicionado em x=0, z=-Z_INTERNO/2 + 3.0f)
        float altar_x_min = -4.0f - margem; // Altar tem largura ~8.0f
        float altar_x_max = 4.0f + margem;
        float altar_z_min = -Z_INTERNO/2 + 3.0f - 1.25f - margem; // Altar tem profundidade ~2.5f
        float altar_z_max = -Z_INTERNO/2 + 3.0f + 1.25f + margem;
        
        if (nova_pos_x >= altar_x_min && nova_pos_x <= altar_x_max &&
            nova_pos_z >= altar_z_min && nova_pos_z <= altar_z_max) {
            colisao = true;
        }
        
        // Verificar colisão com bancos (simplificada - área geral dos bancos)
        // Bancos estão nas laterais, de Z_INTERNO/2 - 4.0f até Z_INTERNO/2 - 19.0f (5 fileiras * 3.0f)
        float bancos_z_min = Z_INTERNO/2 - 19.0f - margem;
        float bancos_z_max = Z_INTERNO/2 - 4.0f + margem;
        
        // Lado esquerdo dos bancos (-8.0f a -2.0f aproximadamente)
        if (nova_pos_x >= -9.0f - margem && nova_pos_x <= -2.0f + margem &&
            nova_pos_z >= bancos_z_min && nova_pos_z <= bancos_z_max) {
            colisao = true;
        }
        
        // Lado direito dos bancos (2.0f a 9.0f aproximadamente)
        if (nova_pos_x >= 2.0f - margem && nova_pos_x <= 9.0f + margem &&
            nova_pos_z >= bancos_z_min && nova_pos_z <= bancos_z_max) {
            colisao = true;
        }
        
        // Aplicar movimento apenas se não houver colisão
        if (!colisao) {
            pos_x = nova_pos_x;
            pos_z = nova_pos_z;
        }
        
        // Ajuste de altura baseado na posição - ordem corrigida
        // Primeiro verifica se está na escada
        if (pos_z > 0 && pos_z <= Z_ESCADA && 
            pos_x >= -X_ESCADA/2 && pos_x <= X_ESCADA/2) {
            // Na escada - altura varia com a posição Z
            float altura_escada = (pos_z / Z_ESCADA) * ALTURA_PLATAFORMA;
            pos_y = 1.7f + altura_escada + 0.1f; // Offset para ficar sobre os degraus
        }
        // Depois verifica se está dentro do interior da igreja
        else if (pos_x > -X_INTERNO/2 + 0.5f && pos_x < X_INTERNO/2 - 0.5f &&
                 pos_z > -Z_INTERNO/2 + 0.5f && pos_z < Z_INTERNO/2 - 0.5f) {
            // Dentro da igreja - altura da plataforma + offset
            pos_y = 1.7f + ALTURA_PLATAFORMA + 0.15f;
        }
        // Depois verifica se está na plataforma externa
        else if (pos_x >= -X_PLATAFORMA_IGREJA/2 && pos_x <= X_PLATAFORMA_IGREJA/2 &&
                 pos_z >= -Z_PLATAFORMA_IGREJA/2 && pos_z <= Z_PLATAFORMA_IGREJA/2) {
            // Na plataforma externa da igreja
            pos_y = 1.7f + ALTURA_PLATAFORMA + 0.1f;
        } 
        // Por último, chão normal
        else {
            // No chão normal
            pos_y = 1.7f;
        }
    }
    
    glutPostRedisplay();
}
