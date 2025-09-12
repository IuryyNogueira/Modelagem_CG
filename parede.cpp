#include "parede.h"
#include "constantes.h"
#include <cmath>

void desenha_plataforma() {
    desenha_bloco(X_PLATAFORMA_IGREJA, ALTURA_PLATAFORMA, Z_PLATAFORMA_IGREJA);
}

void desenha_parede() {
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, Z_INTERNO, -X_INTERNO/2, ALTURA_PLATAFORMA, 0.0); // Parede esquerda
    desenha_bloco(ESPESSURA_PAREDE, PE_DIREITO_IGREJA, Z_INTERNO,  X_INTERNO/2, ALTURA_PLATAFORMA, 0.0); // Parede direita
    desenha_bloco(X_INTERNO, PE_DIREITO_IGREJA, ESPESSURA_PAREDE, 0.0, ALTURA_PLATAFORMA, -Z_INTERNO/2); // Parede traseira
}
