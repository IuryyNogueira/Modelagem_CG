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
    // ===== PRIMEIRA PASSADA: RENDERIZAR SHADOW MAP =====
    if (sistema_sombras.esta_habilitado()) {
        // Atualizar posição da luz baseada no sol
        GLfloat light_pos[4];
        glGetLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        
        // Configurar luz para shadow mapping
        sistema_sombras.configurar_luz(light_pos[0], light_pos[1], light_pos[2], 
                                       0.0f, 0.0f, 0.0f);
        
        // Iniciar renderização da shadow map
        sistema_sombras.iniciar_render_shadow_map();
        
        // Desenhar geometria simplificada para shadow map
        sistema_sombras.desenhar_geometria_shadow_map();
        
        // Finalizar renderização da shadow map
        sistema_sombras.finalizar_render_shadow_map();
    }
    
    // ===== SEGUNDA PASSADA: RENDERIZAR CENA COM SOMBRAS =====
    glPushMatrix();
    
    // Iniciar renderização com shaders de sombra (se disponível)
    sistema_sombras.iniciar_render_cena();
    
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
    
    // Finalizar renderização com sombras
    sistema_sombras.finalizar_render_cena();
    
    glPopMatrix();
    
    // ===== FEIXES DE LUZ VOLUMÉTRICOS (sem sombras) =====
    sistema_feixes_luz.desenhar_todos_feixes();
    
    // ===== DEBUG: Desenhar shadow map no canto da tela (descomente para debug) =====
    // sistema_sombras.desenhar_debug_shadow_map(10, 10, 256, 256);
}
