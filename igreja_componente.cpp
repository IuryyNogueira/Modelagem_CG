#include "igreja.h"
#include "parede.h"
#include "telhado.h"
#include "escada.h"
#include "arco.h"
#include "interior.h"
#include "constantes.h"
#include "sombras.h"
#include "iluminacao.h"
#include "feixes_luz.h"
#include "particulas.h"
#include "janela.h"

void desenha_igreja() {
    glPushMatrix();
    
    // Desenhar a plataforma com rampas primeiro
    desenha_plataforma();
    
    // Desenhar as paredes (já ajustadas para ficarem na altura da plataforma)
    desenha_parede();
    
    // Desenhar janelas laterais
    desenha_janelas_laterais();
    
    // Desenhar o interior da igreja
    desenha_interior();
    
    // Desenhar o telhado
    desenha_telhas();

    // Desenhar escada na frente da igreja
    desenha_escada();

    // Desenhar arco
    desenha_arco();
    
    glPopMatrix();
    
    // ===== SOMBRAS PROJETADAS NO CHÃO =====
    sistema_sombras.desenhar_sombras_interiores();
    
    // ===== FEIXES DE LUZ VOLUMÉTRICOS =====
    sistema_feixes_luz.desenhar_todos_feixes();
}
