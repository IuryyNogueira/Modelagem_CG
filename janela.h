#ifndef JANELA_H
#define JANELA_H

#include <GL/gl.h>

// Função para desenhar uma janela com vitral
void desenha_janela(float largura, float altura, bool com_vitral = true);

// Função para desenhar janelas laterais da igreja
void desenha_janelas_laterais();

#endif // JANELA_H
