#include "iluminacao.h"
#include "constantes.h"
#include <cmath>
#include <iostream>

SistemaIluminacao sistema_iluminacao;

SistemaIluminacao::SistemaIluminacao() {
    luz_sol_ativa = true;
    luz_altar_ativa = true;
    luzes_laterais_ativas = true;
    luz_entrada_ativa = true;
    hora_dia = 15.0f; // 15h (3h da tarde)
    intensidade_global = 1.0f;
}

void SistemaIluminacao::inicializar() {
    std::cout << "=== Inicializando Sistema de Iluminação ===" << std::endl;
    
    // Habilitar iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    // Habilitar normalização automática (importante para objetos escalados)
    glEnable(GL_NORMALIZE);
    
    // Modelo de iluminação
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
    // Luz ambiente global REDUZIDA para ambiente mais escuro e dramático
    GLfloat luz_ambiente_global[] = {0.15f, 0.15f, 0.18f, 1.0f}; // Reduzido de 0.35
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente_global);
    
    // Habilitar depth test para sombras
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    // Configurar todas as luzes
    aplicar_luz_sol();
    aplicar_luz_altar();
    aplicar_luzes_laterais();
    aplicar_luz_entrada();
    aplicar_luzes_velas();
    
    std::cout << "Sistema de iluminação inicializado!" << std::endl;
}

void SistemaIluminacao::aplicar_luz_sol() {
    if(!luz_sol_ativa) {
        glDisable(GL_LIGHT0);
        return;
    }
    
    glEnable(GL_LIGHT0);
    
    // Calcular posição do sol baseado na hora do dia
    float angulo = (hora_dia / 24.0f) * 2.0f * M_PI;
    float altura_sol = sin(angulo) * 100.0f;
    float pos_horizontal = cos(angulo) * 80.0f;
    
    // Intensidade varia com a hora - MUITO MAIS FORTE
    float intensidade = std::max(0.3f, (float)sin(angulo) * 1.2f);
    
    // Cor do sol (amarelo intenso ao meio-dia)
    float vermelho = 1.0f;
    float verde = 0.98f - (0.2f * (1.0f - intensidade));
    float azul = 0.85f - (0.4f * (1.0f - intensidade));
    
    GLfloat posicao_sol[] = {pos_horizontal, altura_sol, 50.0f, 1.0f};
    GLfloat cor_difusa[] = {vermelho * intensidade * 1.5f, verde * intensidade * 1.5f, azul * intensidade * 1.5f, 1.0f};
    GLfloat cor_ambiente[] = {0.4f * intensidade, 0.4f * intensidade, 0.45f * intensidade, 1.0f};
    GLfloat cor_especular[] = {1.0f * intensidade, 1.0f * intensidade, 0.98f * intensidade, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_sol);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_difusa);
    glLightfv(GL_LIGHT0, GL_AMBIENT, cor_ambiente);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_especular);
    
    // Sem atenuação (luz direcional forte)
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
}

void SistemaIluminacao::aplicar_luz_altar() {
    if(!luz_altar_ativa) {
        glDisable(GL_LIGHT1);
        return;
    }
    
    glEnable(GL_LIGHT1);
    
    // Spotlight focado no altar
    GLfloat posicao[] = {0.0f, ALTURA_PLATAFORMA + PE_DIREITO_IGREJA - 1.0f, -Z_INTERNO/2 + 3.0f, 1.0f};
    GLfloat direcao[] = {0.0f, -1.0f, -0.2f}; // Apontando para baixo e levemente para frente
    
    GLfloat cor_difusa[] = {1.0f, 0.98f, 0.9f, 1.0f}; // Branco quente
    GLfloat cor_ambiente[] = {0.2f, 0.19f, 0.18f, 1.0f};
    GLfloat cor_especular[] = {1.0f, 1.0f, 0.95f, 1.0f};
    
    glLightfv(GL_LIGHT1, GL_POSITION, posicao);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direcao);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, cor_difusa);
    glLightfv(GL_LIGHT1, GL_AMBIENT, cor_ambiente);
    glLightfv(GL_LIGHT1, GL_SPECULAR, cor_especular);
    
    // Parâmetros do spotlight
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);      // Ângulo do cone
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 15.0f);    // Concentração
    
    // Atenuação
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01f);
}

void SistemaIluminacao::aplicar_luzes_laterais() {
    // LUZ LATERAL ESQUERDA FRONTAL (GL_LIGHT2) - Lâmpada pendente
    if(luzes_laterais_ativas) {
        glEnable(GL_LIGHT2);
        
        GLfloat pos_esq[] = {-10.0f, 8.5f, 10.0f, 1.0f}; // Posição da lâmpada pendente (abaixada)
        GLfloat cor_difusa[] = {1.0f, 0.95f, 0.85f, 1.0f}; // Luz quente amarelada
        GLfloat cor_ambiente[] = {0.2f, 0.19f, 0.17f, 1.0f};
        
        glLightfv(GL_LIGHT2, GL_POSITION, pos_esq);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, cor_difusa);
        glLightfv(GL_LIGHT2, GL_AMBIENT, cor_ambiente);
        
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.08f);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.02f);
    } else {
        glDisable(GL_LIGHT2);
    }
    
    // LUZ LATERAL DIREITA FRONTAL (GL_LIGHT3) - Lâmpada pendente
    if(luzes_laterais_ativas) {
        glEnable(GL_LIGHT3);
        
        GLfloat pos_dir[] = {10.0f, 8.5f, 10.0f, 1.0f}; // Posição da lâmpada pendente (abaixada)
        GLfloat cor_difusa[] = {1.0f, 0.95f, 0.85f, 1.0f};
        GLfloat cor_ambiente[] = {0.2f, 0.19f, 0.17f, 1.0f};
        
        glLightfv(GL_LIGHT3, GL_POSITION, pos_dir);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, cor_difusa);
        glLightfv(GL_LIGHT3, GL_AMBIENT, cor_ambiente);
        
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.08f);
        glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.02f);
    } else {
        glDisable(GL_LIGHT3);
    }
}

void SistemaIluminacao::aplicar_luz_entrada() {
    if(!luz_entrada_ativa) {
        glDisable(GL_LIGHT4);
        return;
    }
    
    glEnable(GL_LIGHT4);
    
    // Luz acima do arco de entrada
    GLfloat posicao[] = {0.0f, ALTURA_PLATAFORMA + PE_DIREITO_IGREJA + 8.0f, Z_INTERNO/2 + 2.0f, 1.0f};
    GLfloat direcao[] = {0.0f, -0.7f, -0.3f};
    
    GLfloat cor_difusa[] = {1.0f, 0.95f, 0.85f, 1.0f}; // Amarelo suave
    GLfloat cor_ambiente[] = {0.15f, 0.14f, 0.13f, 1.0f};
    
    glLightfv(GL_LIGHT4, GL_POSITION, posicao);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direcao);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, cor_difusa);
    glLightfv(GL_LIGHT4, GL_AMBIENT, cor_ambiente);
    
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 60.0f);
    glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0f);
    
    glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.03f);
    glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.005f);
}

void SistemaIluminacao::aplicar_luzes_velas() {
    // Luzes das velas (GL_LIGHT5 e GL_LIGHT6)
    // Velas próximas ao altar
    
    // LUZ VELA ESQUERDA (GL_LIGHT5)
    glEnable(GL_LIGHT5);
    GLfloat pos_vela_esq[] = {-4.5f, ALTURA_PLATAFORMA + 2.5f, -Z_INTERNO/2 + 2.5f, 1.0f};
    GLfloat cor_vela[] = {1.0f, 0.7f, 0.3f, 1.0f}; // Laranja amarelado (chama de vela)
    GLfloat cor_vela_ambiente[] = {0.3f, 0.2f, 0.1f, 1.0f};
    
    glLightfv(GL_LIGHT5, GL_POSITION, pos_vela_esq);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, cor_vela);
    glLightfv(GL_LIGHT5, GL_AMBIENT, cor_vela_ambiente);
    glLightfv(GL_LIGHT5, GL_SPECULAR, cor_vela);
    
    // Atenuação forte (vela é luz fraca)
    glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.2f);
    glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.1f);
    
    // LUZ VELA DIREITA (GL_LIGHT6)
    glEnable(GL_LIGHT6);
    GLfloat pos_vela_dir[] = {4.5f, ALTURA_PLATAFORMA + 2.5f, -Z_INTERNO/2 + 2.5f, 1.0f};
    
    glLightfv(GL_LIGHT6, GL_POSITION, pos_vela_dir);
    glLightfv(GL_LIGHT6, GL_DIFFUSE, cor_vela);
    glLightfv(GL_LIGHT6, GL_AMBIENT, cor_vela_ambiente);
    glLightfv(GL_LIGHT6, GL_SPECULAR, cor_vela);
    
    glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.2f);
    glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.1f);
    
    // LUZ VELA LATERAL ESQUERDA (GL_LIGHT7)
    glEnable(GL_LIGHT7);
    GLfloat pos_vela_lat_esq[] = {-7.0f, ALTURA_PLATAFORMA + 1.1f, Z_INTERNO/2 - 3.0f, 1.0f};
    
    glLightfv(GL_LIGHT7, GL_POSITION, pos_vela_lat_esq);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, cor_vela);
    glLightfv(GL_LIGHT7, GL_AMBIENT, cor_vela_ambiente);
    
    glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.25f);
    glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.15f);
}

void SistemaIluminacao::atualizar(float delta_time) {
    // Atualizar posição das luzes dinâmicas
    aplicar_luz_sol();
    aplicar_luz_altar();
    aplicar_luzes_laterais();
    aplicar_luz_entrada();
    aplicar_luzes_velas();
}

void SistemaIluminacao::avancar_tempo(float velocidade) {
    hora_dia += velocidade * 0.01f; // Ajuste conforme necessário
    if(hora_dia >= 24.0f) hora_dia -= 24.0f;
    if(hora_dia < 0.0f) hora_dia += 24.0f;
}

void SistemaIluminacao::definir_hora(float hora) {
    hora_dia = hora;
    if(hora_dia >= 24.0f) hora_dia = 24.0f;
    if(hora_dia < 0.0f) hora_dia = 0.0f;
}

void SistemaIluminacao::alternar_luz(TipoLuz tipo) {
    switch(tipo) {
        case LUZ_SOL:
            luz_sol_ativa = !luz_sol_ativa;
            break;
        case LUZ_ALTAR:
            luz_altar_ativa = !luz_altar_ativa;
            break;
        case LUZ_LATERAL_ESQ:
        case LUZ_LATERAL_DIR:
            luzes_laterais_ativas = !luzes_laterais_ativas;
            break;
        case LUZ_ENTRADA:
            luz_entrada_ativa = !luz_entrada_ativa;
            break;
    }
}

void SistemaIluminacao::ligar_todas_luzes() {
    luz_sol_ativa = true;
    luz_altar_ativa = true;
    luzes_laterais_ativas = true;
    luz_entrada_ativa = true;
}

void SistemaIluminacao::desligar_todas_luzes() {
    luz_sol_ativa = false;
    luz_altar_ativa = false;
    luzes_laterais_ativas = false;
    luz_entrada_ativa = false;
}

// Configurações de materiais
void SistemaIluminacao::configurar_material_madeira() {
    GLfloat mat_ambiente[] = {0.3f, 0.2f, 0.1f, 1.0f};
    GLfloat mat_difusa[] = {0.6f, 0.4f, 0.2f, 1.0f};
    GLfloat mat_especular[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat brilho[] = {20.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brilho);
}

void SistemaIluminacao::configurar_material_marmore() {
    GLfloat mat_ambiente[] = {0.4f, 0.4f, 0.42f, 1.0f};
    GLfloat mat_difusa[] = {0.8f, 0.8f, 0.82f, 1.0f};
    GLfloat mat_especular[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat brilho[] = {80.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brilho);
}

void SistemaIluminacao::configurar_material_metal() {
    GLfloat mat_ambiente[] = {0.3f, 0.25f, 0.2f, 1.0f};
    GLfloat mat_difusa[] = {0.7f, 0.6f, 0.4f, 1.0f};
    GLfloat mat_especular[] = {1.0f, 0.95f, 0.8f, 1.0f};
    GLfloat brilho[] = {100.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brilho);
}

void SistemaIluminacao::configurar_material_tecido() {
    GLfloat mat_ambiente[] = {0.2f, 0.05f, 0.05f, 1.0f};
    GLfloat mat_difusa[] = {0.7f, 0.1f, 0.1f, 1.0f};
    GLfloat mat_especular[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat brilho[] = {5.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brilho);
}

void SistemaIluminacao::configurar_material_parede() {
    GLfloat mat_ambiente[] = {0.35f, 0.35f, 0.37f, 1.0f};
    GLfloat mat_difusa[] = {0.9f, 0.9f, 0.92f, 1.0f};
    GLfloat mat_especular[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat brilho[] = {10.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brilho);
}

void SistemaIluminacao::aplicar_luz_indireta() {
    // Implementação de iluminação global (radiosity fake)
    // Simular luz refletida das superfícies
    
    // Aumentar luz ambiente em áreas próximas a superfícies brilhantes
    // O altar de mármore reflete luz para cima
    GLfloat luz_reflexo_altar[] = {0.15f, 0.15f, 0.17f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_reflexo_altar);
}

void SistemaIluminacao::aplicar_ambient_occlusion(float x, float y, float z, float raio) {
    // Ambient Occlusion: escurecer cantos e interseções
    // Calcular fator de oclusão baseado na proximidade de geometria
    
    // Esta função pode ser chamada durante o desenho de objetos em cantos
    // Por ora, simulamos com uma redução no brilho do material
    GLfloat mat_ambiente_escuro[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat mat_difusa_escuro[] = {0.3f, 0.3f, 0.3f, 1.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente_escuro);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_difusa_escuro);
}