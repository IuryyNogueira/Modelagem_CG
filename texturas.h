#ifndef TEXTURAS_H
#define TEXTURAS_H

#include <GL/gl.h>
#include <string>
#include <map>

class GerenciadorTexturas {
private:
    std::map<std::string, GLuint> texturas_carregadas;
    
public:
    GerenciadorTexturas();
    ~GerenciadorTexturas();
    
    // Carregar textura de arquivo
    GLuint carregar_textura(const std::string& caminho, bool mipmap = true);
    
    // Obter ID de textura já carregada
    GLuint obter_textura(const std::string& nome);
    
    // Carregar todas as texturas do projeto
    void carregar_todas_texturas();
    
    // Liberar memória
    void limpar();
    
    // IDs das texturas principais
    GLuint parede_externa;
    GLuint parede_interna;
    GLuint piso_marmore;
    GLuint madeira_escura;
    GLuint madeira_porta;
    GLuint concreto;
    GLuint telha_colonial;
    GLuint vitral;
    GLuint grama;
    GLuint pedra_caminho;
    GLuint metal_bronze;
    GLuint tecido_vermelho;
    
    // Skybox
    GLuint skybox[6]; // Frente, Trás, Esq, Dir, Cima, Baixo
};

// Instância global
extern GerenciadorTexturas gerenciador_texturas;

#endif