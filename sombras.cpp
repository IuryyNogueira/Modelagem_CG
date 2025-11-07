#include "sombras.h"
#include "constantes.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <GL/glut.h>

SistemaSombras sistema_sombras;

SistemaSombras::SistemaSombras() {
    fbo_shadow = 0;
    texture_shadow = 0;
    rbo_depth = 0;
    shadow_map_width = 2048;
    shadow_map_height = 2048;
    shader_shadow_program = 0;
    shader_scene_program = 0;
    vertex_shader_shadow = 0;
    fragment_shader_shadow = 0;
    vertex_shader_scene = 0;
    fragment_shader_scene = 0;
    shadow_bias = 0.005f;
    shadow_intensity = 0.5f;
    shadow_mapping_enabled = true; // Ativar sombras planares
    light_position[0] = 50.0f;
    light_position[1] = 80.0f;
    light_position[2] = 50.0f;
    light_target[0] = 0.0f;
    light_target[1] = 0.0f;
    light_target[2] = 0.0f;
    memset(light_projection_matrix, 0, sizeof(light_projection_matrix));
    memset(light_view_matrix, 0, sizeof(light_view_matrix));
    memset(shadow_matrix, 0, sizeof(shadow_matrix));
    memset(bias_matrix, 0, sizeof(bias_matrix));
    bias_matrix[0] = 0.5f; bias_matrix[5] = 0.5f; bias_matrix[10] = 0.5f;
    bias_matrix[12] = 0.5f; bias_matrix[13] = 0.5f; bias_matrix[14] = 0.5f;
    bias_matrix[15] = 1.0f;
}

SistemaSombras::~SistemaSombras() {
    finalizar();
}

bool SistemaSombras::carregar_shader(const char* filename, std::string& source) {
    return false;
}

GLuint SistemaSombras::compilar_shader(GLenum type, const char* source) {
    return 0;
}

GLuint SistemaSombras::criar_programa_shader(GLuint vertex_shader, GLuint fragment_shader) {
    return 0;
}

bool SistemaSombras::inicializar(int width, int height) {
    std::cout << "=== Sistema de Sombras Projetadas Ativo ===" << std::endl;
    shadow_mapping_enabled = true;
    return true;
}

void SistemaSombras::finalizar() {
}

void SistemaSombras::configurar_luz(float pos_x, float pos_y, float pos_z,
                                    float target_x, float target_y, float target_z) {
    light_position[0] = pos_x;
    light_position[1] = pos_y;
    light_position[2] = pos_z;
    light_target[0] = target_x;
    light_target[1] = target_y;
    light_target[2] = target_z;
}

void SistemaSombras::calcular_matriz_luz() {
}

void SistemaSombras::multiplicar_matrizes(const GLfloat* a, const GLfloat* b, GLfloat* result) {
}

// Função para calcular matriz de sombra projetada em um plano
void calcular_matriz_sombra_planar(GLfloat* mat, GLfloat* light, GLfloat* plane) {
    GLfloat dot = plane[0] * light[0] + 
                  plane[1] * light[1] + 
                  plane[2] * light[2] + 
                  plane[3] * light[3];
    
    mat[0]  = dot - light[0] * plane[0];
    mat[4]  = 0.0f - light[0] * plane[1];
    mat[8]  = 0.0f - light[0] * plane[2];
    mat[12] = 0.0f - light[0] * plane[3];
    
    mat[1]  = 0.0f - light[1] * plane[0];
    mat[5]  = dot - light[1] * plane[1];
    mat[9]  = 0.0f - light[1] * plane[2];
    mat[13] = 0.0f - light[1] * plane[3];
    
    mat[2]  = 0.0f - light[2] * plane[0];
    mat[6]  = 0.0f - light[2] * plane[1];
    mat[10] = dot - light[2] * plane[2];
    mat[14] = 0.0f - light[2] * plane[3];
    
    mat[3]  = 0.0f - light[3] * plane[0];
    mat[7]  = 0.0f - light[3] * plane[1];
    mat[11] = 0.0f - light[3] * plane[2];
    mat[15] = dot - light[3] * plane[3];
}

// Desenhar sombra de um objeto no chão
void desenhar_sombra_objeto_chao(GLfloat* luz_pos, void (*desenhar_objeto)()) {
    if (!sistema_sombras.esta_habilitado()) return;
    
    // Plano do chão: y = ALTURA_PLATAFORMA
    GLfloat plano_chao[4] = {0.0f, 1.0f, 0.0f, -ALTURA_PLATAFORMA - 0.01f};
    GLfloat matriz_sombra[16];
    
    calcular_matriz_sombra_planar(matriz_sombra, luz_pos, plano_chao);
    
    // Configurar estado para desenhar sombra
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);
    glDepthMask(GL_FALSE);
    
    // Cor da sombra (preta semi-transparente) - MAIS ESCURA
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f); // Aumentado de 0.4f para 0.6f
    
    // Aplicar matriz de projeção de sombra
    glPushMatrix();
    glMultMatrixf(matriz_sombra);
    
    // Desenhar geometria
    desenhar_objeto();
    
    glPopMatrix();
    glDepthMask(GL_TRUE);
    glPopAttrib();
}

// Geometria simplificada dos bancos para sombra
void geometria_banco() {
    glutSolidCube(1.0);
}

// Geometria simplificada do altar para sombra
void geometria_altar() {
    glPushMatrix();
    glScalef(8.0f, 2.0f, 3.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Geometria simplificada de vela para sombra
void geometria_vela() {
    glPushMatrix();
    glScalef(0.3f, 1.5f, 0.3f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void SistemaSombras::iniciar_render_shadow_map() {
}

void SistemaSombras::finalizar_render_shadow_map() {
}

void SistemaSombras::iniciar_render_cena() {
}

void SistemaSombras::finalizar_render_cena() {
}

void SistemaSombras::desenhar_geometria_shadow_map() {
}

// Função para desenhar todas as sombras dos objetos internos
void SistemaSombras::desenhar_sombras_interiores() {
    if (!shadow_mapping_enabled) return;
    
    // Obter posição da luz principal (GL_LIGHT0 - sol/luz global)
    GLfloat luz_sol[4];
    glGetLightfv(GL_LIGHT0, GL_POSITION, luz_sol);
    
    // Se for luz direcional (w=0), converter para posicional
    if (luz_sol[3] == 0.0f) {
        luz_sol[0] *= 100.0f;
        luz_sol[1] *= 100.0f;
        luz_sol[2] *= 100.0f;
        luz_sol[3] = 1.0f;
    }
    
    // Desenhar sombras dos bancos
    for(int i = 0; i < 8; i++) {
        // Banco esquerdo
        glPushMatrix();
        glTranslatef(-8.0f, ALTURA_PLATAFORMA + 0.9f, 15.0f - i * 4.0f);
        glScalef(3.8f, 1.8f, 2.3f);
        desenhar_sombra_objeto_chao(luz_sol, geometria_banco);
        glPopMatrix();
        
        // Banco direito
        glPushMatrix();
        glTranslatef(8.0f, ALTURA_PLATAFORMA + 0.9f, 15.0f - i * 4.0f);
        glScalef(3.8f, 1.8f, 2.3f);
        desenhar_sombra_objeto_chao(luz_sol, geometria_banco);
        glPopMatrix();
    }
    
    // Desenhar sombra do altar
    glPushMatrix();
    glTranslatef(0.0f, ALTURA_PLATAFORMA + 1.0f, -Z_INTERNO/2 + 3.0f);
    desenhar_sombra_objeto_chao(luz_sol, geometria_altar);
    glPopMatrix();
    
    // Desenhar sombras das velas (3 no altar)
    float posicoes_velas[][2] = {
        {-4.0f, -Z_INTERNO/2 + 2.5f},
        {0.0f, -Z_INTERNO/2 + 2.5f},
        {4.0f, -Z_INTERNO/2 + 2.5f}
    };
    
    for(int i = 0; i < 3; i++) {
        // Sombra das velas - também projetada pela luz das próprias velas
        GLfloat luz_vela[4] = {
            posicoes_velas[i][0], 
            ALTURA_PLATAFORMA + 3.5f, 
            posicoes_velas[i][1], 
            1.0f
        };
        
        glPushMatrix();
        glTranslatef(posicoes_velas[i][0], ALTURA_PLATAFORMA + 2.5f, posicoes_velas[i][1]);
        desenhar_sombra_objeto_chao(luz_sol, geometria_vela);
        glPopMatrix();
    }
}

void SistemaSombras::desenhar_debug_shadow_map(float x, float y, float width, float height) {
}
