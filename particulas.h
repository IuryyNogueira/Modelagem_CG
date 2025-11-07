#ifndef PARTICULAS_H
#define PARTICULAS_H

#include <GL/gl.h>
#include <vector>
#include <cstdlib>
#include <cmath>

// Estrutura de uma partícula de fogo
struct Particula {
    float x, y, z;          // Posição
    float vx, vy, vz;       // Velocidade
    float vida;             // Tempo de vida (0 a 1)
    float tamanho;          // Tamanho da partícula
    float r, g, b, a;       // Cor RGBA
};

// Sistema de partículas para fogo
class SistemaParticulas {
private:
    std::vector<Particula> particulas;
    int max_particulas;
    float tempo_acumulado;
    
    void criar_particula(float x, float y, float z);
    void atualizar_particula(Particula& p, float dt);
    
public:
    SistemaParticulas(int max_part = 200);
    
    void atualizar(float dt);
    void desenhar_fogo_vela(float x, float y, float z);
    void limpar();
};

// Instância global
extern SistemaParticulas sistema_particulas;

#endif // PARTICULAS_H
