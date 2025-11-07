#include "particulas.h"
#include <GL/glut.h>
#include <ctime>
#include <algorithm>

SistemaParticulas sistema_particulas;

SistemaParticulas::SistemaParticulas(int max_part) 
    : max_particulas(max_part), tempo_acumulado(0.0f) {
    particulas.reserve(max_particulas);
}

void SistemaParticulas::criar_particula(float x, float y, float z) {
    if (particulas.size() >= static_cast<size_t>(max_particulas)) return;
    
    Particula p;
    p.x = x + ((rand() % 100 - 50) / 500.0f); // Pequena variação horizontal
    p.y = y;
    p.z = z + ((rand() % 100 - 50) / 500.0f);
    
    // Velocidade principalmente para cima com leve oscilação
    p.vx = ((rand() % 100 - 50) / 1000.0f);
    p.vy = 0.3f + ((rand() % 100) / 500.0f); // Movimento ascendente
    p.vz = ((rand() % 100 - 50) / 1000.0f);
    
    p.vida = 1.0f;
    p.tamanho = 0.04f + ((rand() % 50) / 1000.0f);
    
    // Cores do fogo: amarelo-laranja-vermelho
    p.r = 1.0f;
    p.g = 0.7f + ((rand() % 30) / 100.0f);
    p.b = 0.1f + ((rand() % 20) / 100.0f);
    p.a = 1.0f;
    
    particulas.push_back(p);
}

void SistemaParticulas::atualizar_particula(Particula& p, float dt) {
    // Atualizar posição
    p.x += p.vx * dt;
    p.y += p.vy * dt;
    p.z += p.vz * dt;
    
    // Diminuir vida
    p.vida -= dt * 2.0f; // Partículas duram ~0.5 segundos
    
    // Atualizar cor (amarelo -> laranja -> vermelho -> transparente)
    if (p.vida > 0.7f) {
        // Fase inicial: amarelo brilhante
        p.r = 1.0f;
        p.g = 0.9f;
        p.b = 0.3f;
    } else if (p.vida > 0.4f) {
        // Fase média: laranja
        p.r = 1.0f;
        p.g = 0.6f;
        p.b = 0.1f;
    } else {
        // Fase final: vermelho escuro
        p.r = 0.8f;
        p.g = 0.3f;
        p.b = 0.05f;
    }
    
    // Alpha diminui com a vida
    p.a = p.vida * 0.8f;
    
    // Tamanho aumenta levemente
    p.tamanho += dt * 0.02f;
}

void SistemaParticulas::atualizar(float dt) {
    tempo_acumulado += dt;
    
    // Atualizar partículas existentes
    for (auto it = particulas.begin(); it != particulas.end(); ) {
        atualizar_particula(*it, dt);
        
        if (it->vida <= 0.0f) {
            it = particulas.erase(it);
        } else {
            ++it;
        }
    }
}

void SistemaParticulas::desenhar_fogo_vela(float x, float y, float z) {
    // Criar novas partículas continuamente
    static float tempo_criacao = 0.0f;
    tempo_criacao += 0.016f; // ~60 FPS
    
    if (tempo_criacao > 0.02f) { // Criar partículas a cada 20ms
        for (int i = 0; i < 2; i++) { // 2 partículas por vez
            criar_particula(x, y, z);
        }
        tempo_criacao = 0.0f;
    }
    
    // Atualizar sistema
    atualizar(0.016f);
    
    // Desenhar partículas
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDepthMask(GL_FALSE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Blending aditivo para efeito de brilho
    
    for (const auto& p : particulas) {
        // Desenhar apenas partículas próximas a esta vela
        float dist = sqrt(pow(p.x - x, 2) + pow(p.z - z, 2));
        if (dist > 0.3f) continue;
        
        glPushMatrix();
        glTranslatef(p.x, p.y, p.z);
        
        // Billboard: sempre de frente para a câmera
        GLfloat modelview[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
        
        // Zerar rotação mantendo translação
        modelview[0] = modelview[5] = modelview[10] = 1.0f;
        modelview[1] = modelview[2] = modelview[4] = 
        modelview[6] = modelview[8] = modelview[9] = 0.0f;
        
        glLoadMatrixf(modelview);
        
        glColor4f(p.r, p.g, p.b, p.a);
        
        // Desenhar partícula como quad
        float s = p.tamanho;
        glBegin(GL_QUADS);
            glVertex3f(-s, -s, 0.0f);
            glVertex3f( s, -s, 0.0f);
            glVertex3f( s,  s, 0.0f);
            glVertex3f(-s,  s, 0.0f);
        glEnd();
        
        glPopMatrix();
    }
    
    glPopAttrib();
}

void SistemaParticulas::limpar() {
    particulas.clear();
}
