#ifndef FEIXES_LUZ_H
#define FEIXES_LUZ_H

#include <GL/gl.h>

// Sistema de feixes volumétricos de luz (God Rays)
class SistemaFeixesLuz {
private:
    float intensidade_base;
    float comprimento_feixe;
    
    void desenhar_feixe_individual(float origem_x, float origem_y, float origem_z,
                                   float direcao_x, float direcao_y, float direcao_z,
                                   float largura_base, float largura_fim,
                                   float r, float g, float b, float alpha);
    
public:
    SistemaFeixesLuz();
    void inicializar();
    void desenhar_feixes_janelas();
    void desenhar_feixes_velas();
    void desenhar_todos_feixes();
};

extern SistemaFeixesLuz sistema_feixes_luz;

#endif
