#ifndef CONSTANTES_H
#define CONSTANTES_H

// --- Medidas principais seguindo a planta baixa ---
extern const float LARGURA;
extern const float COMPRIMENTO;
extern const float ALTURA;
extern const float LARGURA_INTERNA;
extern const float COMPRIMENTO_INTERNO;
extern const float ALTURA_TELHADO;
extern const float INCLINACAO_TELHADO;
extern const float LARGURA_ESCADA;
extern const float PROFUNDIDADE_ESCADA;
extern const float ALTURA_PLATAFORMA;

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

#endif
