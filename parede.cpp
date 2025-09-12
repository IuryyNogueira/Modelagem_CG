#include "parede.h"
#include "constantes.h"
#include <cmath>

void desenha_plataforma() {
    desenha_bloco(X_PLATAFORMA_IGREJA, ALTURA_PLATAFORMA, Z_PLATAFORMA_IGREJA);
}

void desenha_parede() {
    glColor3f(0.95f, 0.95f, 0.9f);
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, Z_INTERNO - (ESPESSURA_PAREDE * 2), -X_INTERNO/2, ALTURA_PLATAFORMA, 0.0); // Parede esquerda
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, Z_INTERNO - (ESPESSURA_PAREDE * 2),  X_INTERNO/2, ALTURA_PLATAFORMA, 0.0); // Parede direita
    desenha_bloco(X_INTERNO, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, 0.0, ALTURA_PLATAFORMA, -Z_INTERNO/2); // Parede traseira
    desenha_bloco(12.0f, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, -X_INTERNO/2 + 12.0f/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - .075); // Parede frontal esquerda (colada na parede esquerda)
    desenha_bloco(12.0f, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, X_INTERNO/2 - 12.0f/2, ALTURA_PLATAFORMA, Z_INTERNO/2 - .075); // Parede frontal direita (colada na parede direita)

    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, 1.0f, 0.0f, ALTURA_PLATAFORMA, Z_INTERNO/2 - .075 - 4.0f); // Parede frontal central (com porta de 8m)

}
