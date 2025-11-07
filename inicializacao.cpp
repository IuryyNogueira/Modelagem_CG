#include "inicializacao.h"
#include "texturas.h"
#include "iluminacao.h"
#include "skybox.h"
#include "sombras.h"
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
    
    // SMOOTH SHADING para melhor qualidade visual com shaders
    glShadeModel(GL_SMOOTH);
    
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
    
    // Inicializar sistema de iluminação avançado
    std::cout << "Configurando iluminação..." << std::endl;
    sistema_iluminacao.inicializar();
    
    // Inicializar sistema de shadow mapping
    std::cout << "Configurando shadow mapping..." << std::endl;
    if (!sistema_sombras.inicializar(2048, 2048)) {
        std::cerr << "AVISO: Shadow mapping não pode ser inicializado. Continuando sem sombras." << std::endl;
    }
    
    // Configurar luz para shadow mapping (sincronizar com luz do sol)
    sistema_sombras.configurar_luz(50.0f, 80.0f, 50.0f, 0.0f, 0.0f, 0.0f);
    
    // Inicializar skybox
    std::cout << "Carregando skybox..." << std::endl;
    inicializar_skybox();
    
    std::cout << "=== INICIALIZAÇÃO CONCLUÍDA ===" << std::endl;
}
