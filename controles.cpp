#include "controles.h"
#include "constantes.h"
#include "igreja.h"
#include "iluminacao.h"
#include "texturas.h"
#include "skybox.h"
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
    
    // Aplicar textura de grama
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.grama);
    sistema_iluminacao.configurar_material_parede();
    
    // Cor BRANCA para não alterar a textura - problema estava aqui!
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-tamanho, 0.0f, -tamanho);
        glTexCoord2f(20.0f, 0.0f); glVertex3f( tamanho, 0.0f, -tamanho);
        glTexCoord2f(20.0f, 20.0f); glVertex3f( tamanho, 0.0f,  tamanho);
        glTexCoord2f(0.0f, 20.0f); glVertex3f(-tamanho, 0.0f,  tamanho);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    // Linhas de divisão no terreno (opcional, mais escuras)
    glColor3f(0.3f, 0.5f, 0.3f);
    glLineWidth(1.0f);
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

    // Atualizar sistema de iluminação
    sistema_iluminacao.atualizar(0.016f); // ~60 FPS

    // Desenhar skybox PRIMEIRO (fundo)
    desenha_skybox();
    
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
    
    // Movimento com WASD (minúsculas E maiúsculas)
    if (keyStates['w'] || keyStates['W']) {
        move_x += sin(dir);
        move_z += -cos(dir);
    }
    if (keyStates['s'] || keyStates['S']) {
        move_x -= sin(dir);
        move_z -= -cos(dir);
    }
    if (keyStates['a'] || keyStates['A']) {
        move_x -= cos(dir);
        move_z -= sin(dir);
    }
    if (keyStates['d'] || keyStates['D']) {
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
        float nova_pos_x = pos_x + move_x * VELOCIDADE * 0.5f;
        float nova_pos_z = pos_z + move_z * VELOCIDADE * 0.5f;
        
        // Detecção de colisão com as paredes
        // APENAS verifica colisão se você JÁ está na área da igreja ou perto dela
        bool colisao = false;
        float margem = 0.2f; // Margem de segurança do jogador (reduzida para mais liberdade)
        
        // Verificar se está na área relevante (dentro ou perto da igreja)
        bool na_area_igreja = (pos_x > -X_PLATAFORMA_IGREJA/2 - 5.0f && pos_x < X_PLATAFORMA_IGREJA/2 + 5.0f &&
                               pos_z > -Z_PLATAFORMA_IGREJA/2 - 5.0f && pos_z < Z_PLATAFORMA_IGREJA/2 + 5.0f);
        
        if (na_area_igreja) {
            // Área interna permitida (dentro das paredes)
            float area_permitida_x_min = -X_INTERNO/2 + margem;
            float area_permitida_x_max = X_INTERNO/2 - margem;
            float area_permitida_z_min = -Z_INTERNO/2 + margem;
            float area_permitida_z_max = Z_INTERNO/2 - margem;
        
        // Se está dentro da área X da igreja
        bool dentro_area_x = (nova_pos_x >= area_permitida_x_min && nova_pos_x <= area_permitida_x_max);
        
        // Colidiu com parede esquerda
        if (nova_pos_x < area_permitida_x_min && 
            nova_pos_z >= area_permitida_z_min && nova_pos_z <= area_permitida_z_max) {
            colisao = true;
        }
        
        // Colidiu com parede direita
        if (nova_pos_x > area_permitida_x_max && 
            nova_pos_z >= area_permitida_z_min && nova_pos_z <= area_permitida_z_max) {
            colisao = true;
        }
        
        // Colidiu com parede traseira
        if (nova_pos_z < area_permitida_z_min && 
            nova_pos_x >= area_permitida_x_min && nova_pos_x <= area_permitida_x_max) {
            colisao = true;
        }
        
        // Verificar se está na área da escada (sem colisão)
        bool na_escada = (nova_pos_x >= -X_ESCADA/2 && nova_pos_x <= X_ESCADA/2 &&
                          nova_pos_z >= Z_INTERNO/2 && nova_pos_z <= Z_INTERNO/2 + Z_ESCADA + 0.5f);
        
        // Colidiu com parede frontal (verificar se NÃO está nas portas E NÃO está na escada)
        if (nova_pos_z > area_permitida_z_max && dentro_area_x && !na_escada) {
            // Definir áreas das portas laterais (sem parede)
            // Porta esquerda: de -X_INTERNO/2 até ~-X_INTERNO/2 + 12.0f
            // Porta direita: de X_INTERNO/2 - 12.0f até X_INTERNO/2
            float porta_esq_x_max = -X_INTERNO/2 + 12.0f;
            float porta_dir_x_min = X_INTERNO/2 - 12.0f;
            
            // Há parede frontal em 3 segmentos:
            // 1. Esquerdo: -X_INTERNO/2 até -X_INTERNO/2 + 12.0f (porta esquerda)
            // 2. Central: entre as portas (pequeno segmento)
            // 3. Direito: X_INTERNO/2 - 12.0f até X_INTERNO/2 (porta direita)
            
            // Como simplificação: só há colisão se estiver no segmento central pequeno
            float parede_central_x_min = porta_esq_x_max - margem;
            float parede_central_x_max = porta_dir_x_min + margem;
            
            if (nova_pos_x >= parede_central_x_min && nova_pos_x <= parede_central_x_max) {
                colisao = true;
            }
        }
        
        // Verificar colisão com portas laterais (só se estiverem fechadas)
        if (angulo_porta < 45.0f) { // Portas consideradas fechadas se ângulo < 45°
            // Portas ficam em Z_INTERNO/2, ou seja, na parede frontal
            float porta_z_min = Z_INTERNO/2 - margem;
            float porta_z_max = Z_INTERNO/2 + 1.0f; // Portas se projetam para fora
            
            // Porta esquerda (centro do buraco na parede)
            float porta_esq_x = (-X_INTERNO/2 + 12.0f + 0.0f) / 2.0f;
            float porta_esq_x_min = porta_esq_x - 1.2f;
            float porta_esq_x_max = porta_esq_x + 1.2f;
            
            if (nova_pos_z >= porta_z_min && nova_pos_z <= porta_z_max &&
                nova_pos_x >= porta_esq_x_min && nova_pos_x <= porta_esq_x_max) {
                colisao = true;
            }
            
            // Porta direita (centro do buraco na parede)
            float porta_dir_x = (0.0f + X_INTERNO/2 - 12.0f) / 2.0f;
            float porta_dir_x_min = porta_dir_x - 1.2f;
            float porta_dir_x_max = porta_dir_x + 1.2f;
            
            if (nova_pos_z >= porta_z_min && nova_pos_z <= porta_z_max &&
                nova_pos_x >= porta_dir_x_min && nova_pos_x <= porta_dir_x_max) {
                colisao = true;
            }
        }

        
        // Escada: sem colisão física, apenas ajuste de altura (feito depois)
        
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
        
        } // Fim do if (na_area_igreja)
        
        // Aplicar movimento apenas se não houver colisão
        if (!colisao) {
            pos_x = nova_pos_x;
            pos_z = nova_pos_z;
        }
    }
    
    // Ajuste de altura baseado na posição - ordem CORRETA para evitar afundamento
    // SEMPRE executado, mesmo sem movimento
    // Altura dos olhos padrão
    float altura_olhos = 1.7f;
    
    // 1. PRIMEIRO: Verificar se está dentro da igreja (interior)
    if (pos_x > -X_INTERNO/2 + 0.3f && pos_x < X_INTERNO/2 - 0.3f &&
        pos_z > -Z_INTERNO/2 + 0.3f && pos_z < Z_INTERNO/2 - 0.3f) {
        // Dentro da igreja - altura da plataforma
        pos_y = altura_olhos + ALTURA_PLATAFORMA;
    }
    // 2. SEGUNDO: Verificar se está na escada (FORA da igreja, na frente)
    else if (pos_x >= -X_ESCADA/2 && pos_x <= X_ESCADA/2 &&
             pos_z >= Z_INTERNO/2 && pos_z <= Z_INTERNO/2 + Z_ESCADA + 0.5f) {
        // Na escada - interpolar altura suavemente
        float pos_rel_z = pos_z - Z_INTERNO/2; // Distância da base da escada
        
        // Se está antes da escada (entre igreja e escada)
        if (pos_rel_z < 0.3f) {
            // Transição suave entre plataforma e escada
            pos_y = altura_olhos + ALTURA_PLATAFORMA;
        } else {
            // Na escada propriamente dita
            float pos_na_escada = pos_rel_z - 0.3f; // Posição relativa dentro da escada
            
            if (pos_na_escada < 0.0f) pos_na_escada = 0.0f;
            if (pos_na_escada > Z_ESCADA) pos_na_escada = Z_ESCADA;
            
            // Calcular degrau atual e próximo para interpolação
            float degrau_float = pos_na_escada / PROFUNDIDADE_DEGRAU;
            int degrau_atual = (int)degrau_float;
            float fracao = degrau_float - degrau_atual; // Fração dentro do degrau
            
            // Limitar ao número de degraus
            if (degrau_atual >= NUM_DEGRAUS) degrau_atual = NUM_DEGRAUS - 1;
            
            // Altura base do degrau atual
            float altura_base = ALTURA_PLATAFORMA - (degrau_atual * ALTURA_DEGRAU);
            
            // Altura do próximo degrau (um degrau abaixo)
            float altura_proxima = altura_base;
            if (degrau_atual < NUM_DEGRAUS - 1) {
                altura_proxima = ALTURA_PLATAFORMA - ((degrau_atual + 1) * ALTURA_DEGRAU);
            }
            
            // Interpolar suavemente entre os dois degraus
            float altura_interpolada = altura_base + (altura_proxima - altura_base) * fracao;
            
            pos_y = altura_olhos + altura_interpolada;
        }
    }
    // 3. TERCEIRO: Verificar se está na plataforma externa
    else if (pos_x >= -X_PLATAFORMA_IGREJA/2 && pos_x <= X_PLATAFORMA_IGREJA/2 &&
             pos_z >= -Z_PLATAFORMA_IGREJA/2 && pos_z <= Z_PLATAFORMA_IGREJA/2) {
        // Na plataforma externa da igreja
        pos_y = altura_olhos + ALTURA_PLATAFORMA;
    } 
    // 4. ÚLTIMO: Chão normal
    else {
        // No chão normal
        pos_y = altura_olhos;
    }
    
    glutPostRedisplay();
}
