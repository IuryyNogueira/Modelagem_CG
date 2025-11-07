#ifndef SOMBRAS_H
#define SOMBRAS_H

#include <GL/gl.h>
#include <cmath>

// Sistema de shadow mapping e sombras projetadas
class SistemaSombras {
private:
    // Matriz de projeção de sombra no plano
    GLfloat matriz_sombra_chao[16];
    GLfloat matriz_sombra_plataforma[16];
    
    // Cor da sombra (semi-transparente)
    GLfloat cor_sombra[4] = {0.0f, 0.0f, 0.0f, 0.5f};
    
    // Calcular matriz de projeção de sombra planar
    void calcular_matriz_sombra_planar(GLfloat matriz[16], 
                                       GLfloat luz_pos[4],
                                       GLfloat plano[4]);
    
public:
    SistemaSombras();
    
    // Inicializar sistema de sombras
    void inicializar();
    
    // Começar renderização de sombras no chão
    void iniciar_sombra_chao(GLfloat luz_pos[4]);
    
    // Começar renderização de sombras na plataforma
    void iniciar_sombra_plataforma(GLfloat luz_pos[4]);
    
    // Finalizar renderização de sombras
    void finalizar_sombra();
    
    // Renderizar sombras de todos os objetos internos
    void desenhar_sombras_interiores();
    
    // Renderizar sombras dos objetos externos
    void desenhar_sombras_exteriores();
};

// Instância global
extern SistemaSombras sistema_sombras;

#endif // SOMBRAS_H
