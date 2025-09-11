#include "igreja.h"
#include "parede.h"
#include "telhado.h"
#include "escada.h"
#include "arco.h"
#include "interior.h"
#include "constantes.h"

void desenha_igreja() {
    glPushMatrix();
    
    // Desenhar a plataforma com rampas primeiro
    desenha_plataforma();
    
    // Desenhar as paredes (já ajustadas para ficarem na altura da plataforma)
    desenha_parede();
    
    // Desenhar o interior da igreja
    desenha_interior();
    
    // Desenhar o telhado
    desenha_telhas();

    // Desenhar escada na frente da igreja (direcionada à porta)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, PROFUNDIDADE_ESCADA);
    desenha_escada();
    glPopMatrix();

    // Desenhar cruz no topo
    desenha_arco();

    glPopMatrix();
}
