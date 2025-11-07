#include "texturas.h"
#include <iostream>
#include <SOIL/SOIL.h>

GerenciadorTexturas gerenciador_texturas;

GerenciadorTexturas::GerenciadorTexturas() {
    // Inicializa IDs com 0
    parede_externa = parede_interna = piso_marmore = 0;
    madeira_escura = madeira_porta = concreto = 0;
    telha_colonial = vitral = grama = 0;
    pedra_caminho = metal_bronze = tecido_vermelho = 0;
    
    for(int i = 0; i < 6; i++) {
        skybox[i] = 0;
    }
}

GerenciadorTexturas::~GerenciadorTexturas() {
    limpar();
}

GLuint GerenciadorTexturas::carregar_textura(const std::string& caminho, bool mipmap) {
    if(texturas_carregadas.find(caminho) != texturas_carregadas.end()) {
        return texturas_carregadas[caminho];
    }
    
    GLuint textura_id;
    
    textura_id = SOIL_load_OGL_texture(
        caminho.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    if(textura_id == 0) {
        std::cerr << "ERRO ao carregar textura: " << caminho << std::endl;
        std::cerr << "Motivo: " << SOIL_last_result() << std::endl;
        return 0;
    }
    
    glBindTexture(GL_TEXTURE_2D, textura_id);
    
    if(mipmap) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    GLfloat maior_aniso = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maior_aniso);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maior_aniso);
    
    texturas_carregadas[caminho] = textura_id;
    
    std::cout << "Textura carregada: " << caminho << " (ID: " << textura_id << ")" << std::endl;
    
    return textura_id;
}

GLuint GerenciadorTexturas::obter_textura(const std::string& nome) {
    if(texturas_carregadas.find(nome) != texturas_carregadas.end()) {
        return texturas_carregadas[nome];
    }
    return 0;
}

void GerenciadorTexturas::carregar_todas_texturas() {
    std::cout << "=== Carregando Texturas ===" << std::endl;
    
    // Texturas principais (adaptadas para as extensões reais)
    parede_externa = carregar_textura("texturas/parede_externa.png");
    parede_interna = carregar_textura("texturas/parede_interna.png");
    piso_marmore = carregar_textura("texturas/piso_marmore.jpg");
    madeira_escura = carregar_textura("texturas/madeira_escura.jpg");
    madeira_porta = carregar_textura("texturas/madeira_porta.jpg");
    concreto = carregar_textura("texturas/concreto.jpg");
    telha_colonial = carregar_textura("texturas/telha_colonial.jpg");
    vitral = carregar_textura("texturas/vitral_colorido.jpg");
    grama = carregar_textura("texturas/grama.jpg");
    pedra_caminho = carregar_textura("texturas/pedra_caminho.png");
    metal_bronze = carregar_textura("texturas/metal_bronze.jpg");
    tecido_vermelho = carregar_textura("texturas/tecido_vermelho.jpg");

    std::cout << "=== Texturas Carregadas ===" << std::endl;
}

void GerenciadorTexturas::limpar() {
    for(auto& par : texturas_carregadas) {
        glDeleteTextures(1, &par.second);
    }
    texturas_carregadas.clear();
}
