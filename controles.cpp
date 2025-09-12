#include "controles.h"
#include "constantes.h"
#include "igreja.h"
#include <cmath>
#include <iostream>

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
