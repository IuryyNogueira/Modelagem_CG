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

    // Desenhar escada na frente da igreja (direcionada à porta)
    // glPushMatrix();
    // glTranslatef(0.0f, 0.0f, Z_ESCADA); // Posicionar a escada na frente da igreja
    desenha_escada();
    // glPopMatrix();

    // // Desenhar cruz no topo
    desenha_arco();
    
    glPopMatrix();
    
    // ===== FEIXES DE LUZ VOLUMÉTRICOS =====
    sistema_feixes_luz.desenhar_todos_feixes();
    
    // Sombras desabilitadas (causando artefatos visuais)
    // ===== RENDERIZAR SOMBRAS SUTIS =====
    // GLfloat pos_luz_sol[4];
    // glGetLightfv(GL_LIGHT0, GL_POSITION, pos_luz_sol);
    // if (pos_luz_sol[3] == 0.0f) {
    //     float distancia = 500.0f;
    //     pos_luz_sol[0] *= distancia;
    //     pos_luz_sol[1] *= distancia;
    //     pos_luz_sol[2] *= distancia;
    //     pos_luz_sol[3] = 1.0f;
    // }
    // sistema_sombras.iniciar_sombra_chao(pos_luz_sol);
    // sistema_sombras.desenhar_sombras_interiores();
    // sistema_sombras.finalizar_sombra();
}
