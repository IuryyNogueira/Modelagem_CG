#include "constantes.h"

// --- Medidas principais seguindo a planta baixa ---
const float LARGURA = 45.0f;           // Largura total da igreja
const float COMPRIMENTO = 50.0f;       // Profundidade total  
const float ALTURA = 16.84f;           // Altura até o topo da parede (pé direito)
const float LARGURA_INTERNA = 32.0f;   // Largura interna
const float COMPRIMENTO_INTERNO = 36.0f; // Comprimento interno
const float ALTURA_TELHADO = 8.96f;    // Altura adicional do telhado
const float INCLINACAO_TELHADO = 0.3f; // 30% de inclinação
const float LARGURA_ESCADA = 12.04f;   // Largura da escada
const float PROFUNDIDADE_ESCADA = 8.0f; // Profundidade da escada
const float ALTURA_PLATAFORMA = 1.16f; // Altura da plataforma (mesmo nível do topo da escada)

// --- Controle da câmera em primeira pessoa ---
float pos_x = 0.0f;
float pos_y = 1.7f; // altura dos olhos de uma pessoa (1.70m)
float pos_z = 15.0f; // posição mais próxima para escala humana
float dir = 0.0f; // direção em radianos (0 = olhando para -z)
float pitch = 0.0f; // sem inclinação inicial
const float VELOCIDADE = 0.3f;
const float SENSIBILIDADE = 0.05f; // Rotação mais suave

// --- Controle do mouse ---
int last_mouse_x = -1;
int last_mouse_y = -1;
bool mouse_initialized = false;
const float SENS_MOUSE = 0.003f; // Sensibilidade do mouse mais confortável

// --- Flags para teclas pressionadas ---
bool keyStates[256] = {false};
