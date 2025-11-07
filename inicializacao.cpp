#include "inicializacao.h"
#include "texturas.h"
#include "iluminacao.h"
#include "skybox.h"
#include <iostream>

void inicializa() {
    std::cout << "=== INICIALIZANDO IGREJA 3D ===" << std::endl;
    
    // Cor de fundo (azul claro para combinar com skybox)
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f); // Azul céu mais saturado
    
    // Habilitar teste de profundidade
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    // Habilitar texturas 2D
    glEnable(GL_TEXTURE_2D);
    
    // Habilitar blending para transparências
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // FLAT SHADING para iluminação global visível
    glShadeModel(GL_FLAT);
    
    // Habilitar polygon offset para sombras
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    
    // Antialiasing
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    // Carregar todas as texturas
    std::cout << "Carregando texturas..." << std::endl;
    gerenciador_texturas.carregar_todas_texturas();
    
    // Inicializar sistema de iluminação avançado com sombras
    std::cout << "Configurando iluminação e sombras..." << std::endl;
    sistema_iluminacao.inicializar();
    
    // Inicializar skybox
    std::cout << "Carregando skybox..." << std::endl;
    inicializar_skybox();
    
    std::cout << "=== INICIALIZAÇÃO CONCLUÍDA ===" << std::endl;
}
