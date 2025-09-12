#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <GL/glut.h>

// // --- Medidas principais seguindo a planta baixa ---
// extern const float LARGURA;
// extern const float COMPRIMENTO;
// extern const float ALTURA;
// extern const float LARGURA_INTERNA;
// extern const float COMPRIMENTO_INTERNO;
// extern const float ALTURA_TELHADO;
// extern const float INCLINACAO_TELHADO;
// extern const float LARGURA_ESCADA;
// extern const float PROFUNDIDADE_ESCADA;
// extern const float ALTURA_PLATAFORMA;

extern const float X_TERRENO;
extern const float Z_TERRENO;
extern const float H_MURO_TERRENO;
extern const float RECUO_ESQUERDO;

extern const float NIVEL_IGREJA;
extern const float NIVEL_TERRENO;

extern const float X_INTERNO;
extern const float Z_INTERNO;
extern const float ESPESSURA_PAREDE;
extern const float PE_DIREITO_IGREJA;

extern const float X_PLATAFORMA_IGREJA;
extern const float Z_PLATAFORMA_IGREJA;

extern const float INCLINACAO_TELHADO;
extern const float ALTURA_TELHADO;

extern const float X_ESCADA;
extern const float Z_ESCADA;
extern const float ALTURA_PLATAFORMA;
extern const int NUM_DEGRAUS;
extern const float PROFUNDIDADE_DEGRAU;
extern const float ALTURA_DEGRAU;


// --- Controle da câmera em primeira pessoa ---
extern float pos_x;
extern float pos_y;
extern float pos_z;
extern float dir;
extern float pitch;
extern const float VELOCIDADE;
extern const float SENSIBILIDADE;

// --- Controle do mouse ---
extern int last_mouse_x;
extern int last_mouse_y;
extern bool mouse_initialized;
extern const float SENS_MOUSE;

// --- Flags para teclas pressionadas ---
extern bool keyStates[256];

void desenha_bloco(float x, float y, float z, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f);

#endif
