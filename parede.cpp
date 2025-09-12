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

    glColor3f(0.59f, 0.29f, 0.0);
    desenha_bloco(0.05f, 2.1f, 1.2f, -X_INTERNO/2 + 12.0f - 0.025f, ALTURA_PLATAFORMA, Z_INTERNO/2 - .75); // Porta esquerda (encostada na parede esquerda)
    desenha_bloco(0.05f, 2.1f, 1.2f, X_INTERNO/2 - 12.0f + 0.025f, ALTURA_PLATAFORMA, Z_INTERNO/2 - .75); // Porta direita (encostada na parede direita)

    glColor3f(0.95f, 0.95f, 0.9f);
    desenha_bloco(8.3f, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, 0.0f, ALTURA_PLATAFORMA, Z_INTERNO/2 - 1.4f); // Parede frontal central (com porta)
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - 2.1f, 1.2f, -X_INTERNO/2 + 12.0f - .075f, ALTURA_PLATAFORMA + 2.1, Z_INTERNO/2 - .75f); // Parede frontal entre porta e parede esquerda
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA - 2.1f, 1.2f, X_INTERNO/2 - 12.0f + .075f, ALTURA_PLATAFORMA + 2.1, Z_INTERNO/2 - .75f); // Parede frontal entre porta e parede direita
    desenha_bloco(8.3f, ESPESSURA_PAREDE, 1.2f, 0.0f, ALTURA_PLATAFORMA + PE_DIREITO_IGREJA, Z_INTERNO/2 - .75f); // Parte superior da parede frontal (acima da porta)

}
