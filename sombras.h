#ifndef SOMBRAS_H
#define SOMBRAS_H

#include <GL/gl.h>
#include <GL/glext.h>
#include <cmath>
#include <string>

// Sistema de Shadow Mapping com FBO
class SistemaSombras {
private:
    // Shadow Map
    GLuint fbo_shadow;              // Frame Buffer Object para shadow map
    GLuint texture_shadow;          // Textura da shadow map
    GLuint rbo_depth;               // Render Buffer Object para depth
    int shadow_map_width;           // Largura da shadow map
    int shadow_map_height;          // Altura da shadow map
    
    // Shaders
    GLuint shader_shadow_program;   // Programa shader para gerar shadow map
    GLuint shader_scene_program;    // Programa shader para renderizar cena com sombras
    
    GLuint vertex_shader_shadow;
    GLuint fragment_shader_shadow;
    GLuint vertex_shader_scene;
    GLuint fragment_shader_scene;
    
    // Matrizes
    GLfloat light_projection_matrix[16];
    GLfloat light_view_matrix[16];
    GLfloat shadow_matrix[16];      // Matriz combinada para shader
    GLfloat bias_matrix[16];        // Matriz de bias para conversão de coordenadas
    
    // Parâmetros
    float shadow_bias;              // Bias para evitar shadow acne
    float shadow_intensity;         // Intensidade da sombra (0-1)
    bool shadow_mapping_enabled;
    
    // Posição e direção da luz
    GLfloat light_position[3];
    GLfloat light_target[3];
    
    // Funções auxiliares
    bool carregar_shader(const char* filename, std::string& source);
    GLuint compilar_shader(GLenum type, const char* source);
    GLuint criar_programa_shader(GLuint vertex_shader, GLuint fragment_shader);
    void calcular_matriz_luz();
    void multiplicar_matrizes(const GLfloat* a, const GLfloat* b, GLfloat* result);
    
public:
    SistemaSombras();
    ~SistemaSombras();
    
    // Inicializar sistema de shadow mapping
    bool inicializar(int width = 2048, int height = 2048);
    void finalizar();
    
    // Configurar luz para sombras
    void configurar_luz(float pos_x, float pos_y, float pos_z,
                       float target_x, float target_y, float target_z);
    
    // Primeira passada: renderizar shadow map
    void iniciar_render_shadow_map();
    void finalizar_render_shadow_map();
    
    // Segunda passada: renderizar cena com sombras
    void iniciar_render_cena();
    void finalizar_render_cena();
    
    // Desenhar objetos para shadow map (geometria simplificada)
    void desenhar_geometria_shadow_map();
    
    // Configurações
    void definir_bias(float bias) { shadow_bias = bias; }
    void definir_intensidade(float intensity) { shadow_intensity = intensity; }
    void habilitar(bool enable) { shadow_mapping_enabled = enable; }
    bool esta_habilitado() const { return shadow_mapping_enabled; }
    
    // Debug
    void desenhar_debug_shadow_map(float x, float y, float width, float height);
    GLuint obter_textura_shadow() const { return texture_shadow; }
};

// Instância global
extern SistemaSombras sistema_sombras;

#endif // SOMBRAS_H
