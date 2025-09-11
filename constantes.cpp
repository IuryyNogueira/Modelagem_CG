#include "constantes.h"

// --- Medidas principais ---
const float LARGURA = 45.0f;
const float COMPRIMENTO = 50.0f;
const float ALTURA = 4.5f;
const float INCLINACAO_TELHADO = 0.3f; // 30%

// --- Controle da câmera em primeira pessoa ---
float pos_x = 0.0f;
float pos_y = 2.0f; // altura dos olhos
float pos_z = 10.0f;
float dir = 0.0f; // direção em radianos (0 = olhando para -z)
float pitch = 0.0f; // inclinação vertical
const float VELOCIDADE = 1.0f;
const float SENSIBILIDADE = 0.07f;

// --- Controle do mouse ---
int last_mouse_x = -1;
int last_mouse_y = -1;
bool mouse_initialized = false;
const float SENS_MOUSE = 0.003f;

// --- Flags para teclas pressionadas ---
bool keyStates[256] = {false};
