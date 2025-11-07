#include "interior.h"
#include "constantes.h"
#include "texturas.h"
#include "iluminacao.h"
#include "particulas.h"
#include <cmath>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void desenha_altar() {
    float base_y = ALTURA_PLATAFORMA;
    
    // Aplicar textura de mármore e material
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.piso_marmore);
    sistema_iluminacao.configurar_material_marmore();
    glColor3f(0.95f, 0.95f, 0.95f); // Branco do altar
    
    // Altar principal (topo)
    glPushMatrix();
    glTranslatef(0.0f, base_y + 0.4f, -Z_INTERNO/2 + 3.0f);
    desenha_bloco(6.0f, 0.8f, 2.0f, 0.0f, 0.0f, 0.0f);
    glPopMatrix();
    
    // Base do altar (mais larga e mais baixa)
    glColor3f(0.9f, 0.9f, 0.9f);
    glPushMatrix();
    glTranslatef(0.0f, base_y + 0.15f, -Z_INTERNO/2 + 3.0f);
    desenha_bloco(8.0f, 0.3f, 2.5f, 0.0f, 0.0f, 0.0f);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
    // NÃO desenhar bíblia aqui - será desenhada em pedestal separado
}

void desenha_pedestal_biblia() {
    float base_y = ALTURA_PLATAFORMA;
    
    // Pedestal de mármore ao lado direito do altar
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.piso_marmore);
    sistema_iluminacao.configurar_material_marmore();
    glColor3f(0.92f, 0.92f, 0.90f);
    
    // Posição: lado direito do altar
    float pos_x = 4.0f;
    float pos_z = -Z_INTERNO/2 + 3.5f;
    
    // Base do pedestal
    glPushMatrix();
    glTranslatef(pos_x, base_y + 0.2f, pos_z);
    glScalef(0.6f, 0.4f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Coluna do pedestal (cilindro MAIS BAIXO)
    glPushMatrix();
    glTranslatef(pos_x, base_y + 0.45f, pos_z);  // Abaixado de 0.6f para 0.45f
    GLUquadric* quad_ped = gluNewQuadric();
    gluQuadricTexture(quad_ped, GL_TRUE);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad_ped, 0.15, 0.15, 0.45, 16, 4);  // Altura reduzida de 0.6 para 0.45
    gluDeleteQuadric(quad_ped);
    glPopMatrix();
    
    // Topo do pedestal (plataforma para a bíblia) - ajustado
    glPushMatrix();
    glTranslatef(pos_x, base_y + 0.85f, pos_z);  // Abaixado de 0.95f para 0.85f
    glScalef(0.7f, 0.1f, 0.7f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
    // Desenhar a Bíblia no topo do pedestal (MELHORADA)
    glPushMatrix();
    glTranslatef(pos_x, base_y + 0.95f, pos_z);  // Ajustado para nova altura
    
    // Aplicar material brilhante
    sistema_iluminacao.configurar_material_madeira();
    
    // Livro da bíblia MELHORADO - mais realista
    // Capa inferior (base do livro)
    glColor3f(0.45f, 0.25f, 0.12f); // Marrom escuro da capa
    glPushMatrix();
    glRotatef(-25.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.75f, 0.12f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Páginas do livro (bloco branco)
    glColor3f(0.98f, 0.96f, 0.88f); // Páginas amareladas
    glPushMatrix();
    glRotatef(-25.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.03f, 0.08f, 0.0f);
    glScalef(0.68f, 0.08f, 0.44f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Lombada do livro (lateral)
    glColor3f(0.4f, 0.22f, 0.1f); // Marrom mais escuro
    glPushMatrix();
    glRotatef(-25.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.36f, 0.06f, 0.0f);
    glScalef(0.04f, 0.1f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Cruz DOURADA GRANDE e BRILHANTE na capa
    glColor3f(1.0f, 0.85f, 0.15f); // Dourado mais vibrante
    glPushMatrix();
    glRotatef(-25.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.05f, 0.13f, -0.08f);
    
    // Haste vertical da cruz (MAIOR)
    glPushMatrix();
    glScalef(0.03f, 0.03f, 0.12f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Haste horizontal da cruz (MAIOR)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.03f);
    glScalef(0.03f, 0.03f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPopMatrix();
    
    // Detalhes dourados nas bordas (decoração)
    glColor3f(1.0f, 0.8f, 0.2f);
    glPushMatrix();
    glRotatef(-25.0f, 0.0f, 1.0f, 0.0f);
    // Borda superior
    glPushMatrix();
    glTranslatef(0.0f, 0.12f, -0.24f);
    glScalef(0.7f, 0.015f, 0.02f);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Borda inferior
    glPushMatrix();
    glTranslatef(0.0f, 0.12f, 0.24f);
    glScalef(0.7f, 0.015f, 0.02f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();
    
    glPopMatrix();
}

void desenha_cruz_grande() {
    float base_y = ALTURA_PLATAFORMA;
    
    // Cruz grande na parede do fundo (posicionada corretamente)
    glColor3f(0.4f, 0.3f, 0.2f); // Madeira escura da cruz
    glPushMatrix();
    glTranslatef(0.0f, base_y + 4.0f, -Z_INTERNO/2 + 0.5f); // Bem próxima à parede traseira
    
    // Haste vertical da cruz
    glPushMatrix();
    glScalef(0.3f, 4.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Haste horizontal da cruz
    glPushMatrix();
    glTranslatef(0.0f, 0.8f, 0.0f);
    glScalef(2.2f, 0.3f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPopMatrix();
}

void desenha_caminho_verde() {
    float base_y = ALTURA_PLATAFORMA;
    
    // Aplicar textura de tecido vermelho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.tecido_vermelho);
    sistema_iluminacao.configurar_material_tecido();
    
    // Caminho vermelho central (da entrada até próximo ao altar)
    glColor3f(0.9f, 0.9f, 0.9f); // Branco para não alterar cor da textura
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.2f, base_y + 0.02f, Z_INTERNO/2 - 3.0f); // Começa mais dentro da igreja
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.2f, base_y + 0.02f, Z_INTERNO/2 - 3.0f);
        glTexCoord2f(1.0f, 5.0f); glVertex3f(1.2f, base_y + 0.02f, -Z_INTERNO/2 + 6.0f); // Termina um pouco antes do altar
        glTexCoord2f(0.0f, 5.0f); glVertex3f(-1.2f, base_y + 0.02f, -Z_INTERNO/2 + 6.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void desenha_piso_marmore() {
    float base_y = ALTURA_PLATAFORMA;
    
    // Aplicar textura de mármore
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.piso_marmore);
    sistema_iluminacao.configurar_material_marmore();
    glColor3f(0.95f, 0.95f, 0.95f); // Branco levemente cinza
    
    // Piso principal da igreja
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-X_INTERNO/2, base_y + 0.01f, -Z_INTERNO/2);
        glTexCoord2f(5.0f, 0.0f); glVertex3f(X_INTERNO/2, base_y + 0.01f, -Z_INTERNO/2);
        glTexCoord2f(5.0f, 8.0f); glVertex3f(X_INTERNO/2, base_y + 0.01f, Z_INTERNO/2);
        glTexCoord2f(0.0f, 8.0f); glVertex3f(-X_INTERNO/2, base_y + 0.01f, Z_INTERNO/2);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void desenha_banco_individual(float x, float z, float rotacao) {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(x, base_y, z);
    glRotatef(rotacao, 0.0f, 1.0f, 0.0f);
    
    // Aplicar textura de madeira escura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.madeira_escura);
    sistema_iluminacao.configurar_material_madeira();
    glColor3f(0.7f, 0.5f, 0.3f);
    
    // ===== ASSENTO DO BANCO (simples e limpo) =====
    desenha_bloco(2.5f, 0.1f, 0.8f, 0.0f, 0.25f, 0.0f);
    
    // ===== ENCOSTO DO BANCO (NA FRENTE - posição corrigida e mais baixo) =====
    // Encosto vertical na FRENTE onde a pessoa se apoia (altura reduzida)
    desenha_bloco(2.5f, 0.45f, 0.1f, 0.0f, 0.475f, 0.45f);
    
    // ===== PÉS DO BANCO (4 pés simples) =====
    for(int i = 0; i < 4; i++) {
        float px = (i % 2 == 0) ? -1.1f : 1.1f;
        float pz = (i < 2) ? 0.3f : -0.3f;
        
        desenha_bloco(0.1f, 0.25f, 0.1f, px, 0.125f, pz);
    }
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void desenha_arranjo_flores(float x, float z) {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(x, base_y, z);
    
    // Vaso/base do arranjo (cor bege/terracota)
    glColor3f(0.8f, 0.7f, 0.6f);
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);
    glScalef(0.6f, 0.6f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Flores brancas (várias esferas pequenas)
    glColor3f(0.95f, 0.95f, 0.95f); // Branco das flores
    
    // Arranjo de flores em formato arredondado
    for(int i = 0; i < 8; i++) {
        float angulo = i * 45.0f * M_PI / 180.0f;
        float raio = 0.3f;
        
        glPushMatrix();
        glTranslatef(raio * cos(angulo), 0.7f + (i % 2) * 0.1f, raio * sin(angulo));
        glScalef(0.15f, 0.15f, 0.15f);
        glutSolidSphere(1.0f, 8, 8);
        glPopMatrix();
    }
    
    // Flores centrais
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef((i-1) * 0.15f, 0.8f + i * 0.05f, (i-1) * 0.1f);
        glScalef(0.12f, 0.12f, 0.12f);
        glutSolidSphere(1.0f, 8, 8);
        glPopMatrix();
    }
    
    // Algumas folhas verdes (opcionais)
    glColor3f(0.2f, 0.5f, 0.2f);
    for(int i = 0; i < 4; i++) {
        float angulo = i * 90.0f * M_PI / 180.0f;
        glPushMatrix();
        glTranslatef(0.4f * cos(angulo), 0.5f, 0.4f * sin(angulo));
        glScalef(0.08f, 0.08f, 0.08f);
        glutSolidSphere(1.0f, 6, 6);
        glPopMatrix();
    }
    
    glPopMatrix();
}

void desenha_arranjos_flores() {
    // Arranjos ao lado do altar
    desenha_arranjo_flores(-3.0f, -Z_INTERNO/2 + 4.0f); // Lado esquerdo do altar
    desenha_arranjo_flores(3.0f, -Z_INTERNO/2 + 4.0f);  // Lado direito do altar
    
    // Arranjos nas laterais do caminho verde (próximo à entrada)
    desenha_arranjo_flores(-2.5f, Z_INTERNO/2 - 2.0f);  // Lado esquerdo da entrada
    desenha_arranjo_flores(2.5f, Z_INTERNO/2 - 2.0f);   // Lado direito da entrada
    
    // Arranjos do meio REMOVIDOS - conflitavam com bancos
    // desenha_arranjo_flores(-2.5f, 0.0f);  
    // desenha_arranjo_flores(2.5f, 0.0f);   
    
    // Arranjos nas laterais próximo ao altar
    desenha_arranjo_flores(-5.0f, -Z_INTERNO/2 + 8.0f);
    desenha_arranjo_flores(5.0f, -Z_INTERNO/2 + 8.0f);
}

void desenha_biblia() {
    float base_y = ALTURA_PLATAFORMA;
    
    // Desabilitar textura para usar cores sólidas
    glDisable(GL_TEXTURE_2D);
    
    glPushMatrix();
    glTranslatef(0.0f, base_y + 0.9f, -Z_INTERNO/2 + 3.0f); // Bem visível no topo do altar
    
    // Aplicar material brilhante
    sistema_iluminacao.configurar_material_madeira();
    
    // Livro da bíblia MAIOR e mais visível (capa de couro marrom)
    glColor3f(0.45f, 0.25f, 0.12f); // Marrom mais claro e visível
    glPushMatrix();
    glRotatef(12.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.8f, 0.12f, 0.5f); // Livro MAIOR
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Páginas brancas (bem visíveis)
    glColor3f(1.0f, 0.98f, 0.92f); // Quase branco
    glPushMatrix();
    glRotatef(12.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.06f, 0.08f, 0.0f);
    glScalef(0.72f, 0.08f, 0.44f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Cruz DOURADA GRANDE na capa
    glColor3f(1.0f, 0.85f, 0.3f); // Dourado BRILHANTE
    glPushMatrix();
    glRotatef(12.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.13f, -0.08f);
    
    // Haste vertical da cruz (MAIOR)
    glPushMatrix();
    glScalef(0.03f, 0.03f, 0.12f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Haste horizontal da cruz (MAIOR)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.03f);
    glScalef(0.03f, 0.03f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}
void desenha_castical_longo(float x, float z) {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(x, base_y, z);
    
    // Desabilitar textura - usar cor de bronze direto
    glDisable(GL_TEXTURE_2D);
    sistema_iluminacao.configurar_material_metal();
    
    // ===== BASE DO CASTIÇAL (PERFEITAMENTE NO CHÃO) =====
    // Base inferior MUITO larga e achatada (no chão - y=0)
    glColor3f(0.75f, 0.6f, 0.25f);
    glPushMatrix();
    glTranslatef(0.0f, 0.03f, 0.0f);  // Quase no chão (apenas 3cm)
    glScalef(0.7f, 0.06f, 0.7f);  // MUITO larga e achatada
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Base média (disco)
    glColor3f(0.78f, 0.63f, 0.28f);
    glPushMatrix();
    glTranslatef(0.0f, 0.08f, 0.0f);
    glScalef(0.55f, 0.04f, 0.55f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Base superior (menor)
    glColor3f(0.8f, 0.65f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, 0.13f, 0.0f);
    glScalef(0.4f, 0.06f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Conexão base-haste (torus decorativo)
    glColor3f(0.82f, 0.67f, 0.32f);
    glPushMatrix();
    glTranslatef(0.0f, 0.18f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidTorus(0.06, 0.1, 12, 16);
    glPopMatrix();
    
    // CILINDRO DE CONEXÃO (liga base à haste principal)
    glColor3f(0.78f, 0.63f, 0.28f);
    glPushMatrix();
    glTranslatef(0.0f, 0.24f, 0.0f);
    GLUquadric* quad_conector = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad_conector, 0.12, 0.08, 0.6, 16, 4);  // Cônico da base para haste
    gluDeleteQuadric(quad_conector);
    glPopMatrix();
    
    // ===== HASTE LONGA DO CASTIÇAL =====
    glColor3f(0.78f, 0.63f, 0.28f);
    glPushMatrix();
    glTranslatef(0.0f, 0.85f, 0.0f);  // Ajustado para conectar com a nova base
    GLUquadric* quad = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.08, 0.08, 1.4, 16, 4);
    gluDeleteQuadric(quad);
    glPopMatrix();
    
    // Detalhe no meio da haste
    glColor3f(0.82f, 0.67f, 0.32f);
    glPushMatrix();
    glTranslatef(0.0f, 0.85f, 0.0f);
    glutSolidSphere(0.12, 12, 12);
    glPopMatrix();
    
    // ===== PRATO DO CASTIÇAL (onde fica a vela) =====
    glColor3f(0.8f, 0.65f, 0.3f);
    // Prato principal (ajustado para nova altura da haste)
    glPushMatrix();
    glTranslatef(0.0f, 1.65f, 0.0f);  // Ajustado para nova base
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidTorus(0.05, 0.25, 12, 24);
    glPopMatrix();
    
    // Borda elevada do prato
    glPushMatrix();
    glTranslatef(0.0f, 1.67f, 0.0f);
    glScalef(0.3f, 0.04f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // ===== VELA (mais realista) =====
    glColor3f(0.95f, 0.92f, 0.85f); // Cor de cera branca/bege
    
    // Corpo principal da vela (cilindro)
    glPushMatrix();
    glTranslatef(0.0f, 1.95f, 0.0f);  // Ajustado para nova altura
    GLUquadric* quad_vela = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad_vela, 0.1, 0.095, 0.55, 16, 4);
    gluDeleteQuadric(quad_vela);
    glPopMatrix();
    
    // Topo da vela com cera derretida
    glColor3f(0.93f, 0.90f, 0.83f);
    glPushMatrix();
    glTranslatef(0.0f, 2.50f, 0.0f);  // Ajustado
    glScalef(0.11f, 0.06f, 0.11f);
    glutSolidSphere(1.0f, 12, 12);
    glPopMatrix();
    
    // Pavio da vela
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, 2.55f, 0.0f);  // Ajustado
    glScalef(0.015f, 0.08f, 0.015f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // ===== CHAMA E HALO LUMINOSO (MELHORADO) =====
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    float altura_chama = 2.63f;  // Ajustado para nova posição da vela
    
    // Halo externo (maior e mais fraco) - laranja difuso
    glPushMatrix();
    glTranslatef(0.0f, altura_chama, 0.0f);
    glColor4f(1.0f, 0.4f, 0.05f, 0.08f);  // Mais suave
    glutSolidSphere(0.5f, 16, 16);
    glPopMatrix();
    
    // Halo médio-externo - laranja-amarelo
    glPushMatrix();
    glTranslatef(0.0f, altura_chama, 0.0f);
    glColor4f(1.0f, 0.6f, 0.15f, 0.18f);
    glutSolidSphere(0.35f, 14, 14);
    glPopMatrix();
    
    // Halo médio - amarelo quente
    glPushMatrix();
    glTranslatef(0.0f, altura_chama, 0.0f);
    glColor4f(1.0f, 0.75f, 0.25f, 0.3f);
    glutSolidSphere(0.22f, 14, 14);
    glPopMatrix();
    
    // Halo interno - amarelo brilhante
    glPushMatrix();
    glTranslatef(0.0f, altura_chama, 0.0f);
    glColor4f(1.0f, 0.9f, 0.45f, 0.55f);
    glutSolidSphere(0.13f, 12, 12);
    glPopMatrix();
    
    // ===== CHAMA CENTRAL BRILHANTE E TREMULANTE (NÚCLEO) =====
    // Calcular variação para efeito de tremulação
    static float tempo_chama = 0.0f;
    tempo_chama += 0.1f;
    float variacao = 0.92f + 0.08f * sin(tempo_chama * 5.0f + x * 2.0f);  // Oscila entre 0.92 e 1.0
    float variacao2 = 0.95f + 0.05f * cos(tempo_chama * 7.0f + z * 3.0f); // Oscila entre 0.95 e 1.0
    
    glColor4f(1.0f, 0.95f, 0.6f, 0.85f + 0.1f * variacao);  // Amarelo muito brilhante com alpha variável
    glPushMatrix();
    glTranslatef(0.0f, altura_chama, 0.0f);
    // Forma alongada de chama com escala variável (tremulação)
    glScalef(0.08f * variacao2, 0.15f * variacao, 0.08f * variacao2);
    glutSolidSphere(1.0f, 10, 10);
    glPopMatrix();
    
    // ===== PARTÍCULAS DE FOGO ANIMADAS (INICIO MAIS ALTO) =====
    // Partículas começam 0.15 acima do centro da chama
    sistema_particulas.desenhar_fogo_vela(x, base_y + altura_chama + 0.15f, z);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHTING);
    
    glPopMatrix();
}

void desenha_bloco_com_vela(float x, float z) {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(x, base_y, z);
    
    // Bloco retangular (pedra/mármore)
    glColor3f(0.85f, 0.82f, 0.8f); // Cor de mármore
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);
    glScalef(1.2f, 0.6f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Vela em cima do bloco
    glColor3f(0.95f, 0.9f, 0.8f); // Cor de cera
    glPushMatrix();
    glTranslatef(0.0f, 0.8f, 0.0f);
    glScalef(0.15f, 0.4f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // HALO LUMINOSO DA CHAMA (visível e brilhante)
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    // Halo externo (mais fraco e maior)
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);
    glColor4f(1.0f, 0.6f, 0.1f, 0.15f); // Laranja transparente
    glutSolidSphere(0.35f, 12, 12);
    glPopMatrix();
    
    // Halo médio
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);
    glColor4f(1.0f, 0.7f, 0.2f, 0.3f); // Amarelo-laranja
    glutSolidSphere(0.22f, 12, 12);
    glPopMatrix();
    
    // Halo interno (mais brilhante)
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);
    glColor4f(1.0f, 0.9f, 0.3f, 0.6f); // Amarelo brilhante
    glutSolidSphere(0.12f, 12, 12);
    glPopMatrix();
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHTING);
    
    // Chama da vela (núcleo)
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.8f, 0.2f); // Amarelo brilhante
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);
    glScalef(0.08f, 0.12f, 0.08f);
    glutSolidSphere(1.0f, 8, 8);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    
    glPopMatrix();
}

void desenha_casticais_e_velas() {
    // Castiçais longos próximos ao altar
    desenha_castical_longo(-4.5f, -Z_INTERNO/2 + 2.5f); // Lado esquerdo do altar
    desenha_castical_longo(4.5f, -Z_INTERNO/2 + 2.5f);  // Lado direito do altar
    
    // Castiçais nas laterais do altar
    desenha_castical_longo(-6.0f, -Z_INTERNO/2 + 5.0f);
    desenha_castical_longo(6.0f, -Z_INTERNO/2 + 5.0f);
    
    // Blocos com velas próximos à entrada
    desenha_bloco_com_vela(-7.0f, Z_INTERNO/2 - 3.0f);
    desenha_bloco_com_vela(7.0f, Z_INTERNO/2 - 3.0f);
    
    // Blocos com velas no meio da igreja
    desenha_bloco_com_vela(-8.0f, -5.0f);
    desenha_bloco_com_vela(8.0f, -5.0f);
}

void desenha_bancos() {
    // Bancos inclinados no sentido anti-horário (posicionados corretamente)
    // A linha de bancos também segue a rotação individual
    
    float rotacao = -8.0f; // Inclinação anti-horária
    
    // Lado esquerdo - primeira fileira (mais próxima do caminho)
    for(int i = 0; i < 5; i++) {
        float z_base = Z_INTERNO/2 - 4.0f - i * 3.0f;
        // Aplicar offset lateral baseado na rotação para formar linha diagonal
        float x_offset = i * 0.3f; // Pequeno deslocamento em X para seguir a rotação
        desenha_banco_individual(-4.0f + x_offset, z_base, rotacao);
    }
    
    // Lado esquerdo - segunda fileira (mais próxima da parede)
    for(int i = 0; i < 5; i++) {
        float z_base = Z_INTERNO/2 - 4.0f - i * 3.0f;
        float x_offset = i * 0.3f; // Mesmo offset para manter paralelismo
        desenha_banco_individual(-8.0f + x_offset, z_base, rotacao);
    }
    
    // Lado direito - primeira fileira (mais próxima do caminho)
    for(int i = 0; i < 5; i++) {
        float z_base = Z_INTERNO/2 - 4.0f - i * 3.0f;
        // Offset negativo no lado direito para rotação oposta
        float x_offset = -i * 0.3f; 
        desenha_banco_individual(4.0f + x_offset, z_base, -rotacao); // Rotação oposta
    }
    
    // Lado direito - segunda fileira (mais próxima da parede)
    for(int i = 0; i < 5; i++) {
        float z_base = Z_INTERNO/2 - 4.0f - i * 3.0f;
        float x_offset = -i * 0.3f; // Mesmo offset negativo
        desenha_banco_individual(8.0f + x_offset, z_base, -rotacao); // Rotação oposta
    }
}

void desenha_lampadas_pendentes() {
    // Lâmpadas pendentes nas laterais da igreja (onde antes eram luzes externas)
    float posicoes_z[] = {10.0f, -5.0f, -20.0f}; // 3 lâmpadas de cada lado
    
    for (int i = 0; i < 3; i++) {
        // Lado esquerdo
        glPushMatrix();
        glTranslatef(-10.0f, 8.5f, posicoes_z[i]); // Abaixadas de 13.0 para 8.5
        
        // Fio/corrente da lâmpada
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.2f, 0.2f, 0.2f); // Preto
        glPushMatrix();
        glScalef(0.05f, 2.0f, 0.05f);
        glutSolidCube(1.0f);
        glPopMatrix();
        
        // Cúpula da lâmpada (metal)
        sistema_iluminacao.configurar_material_metal();
        glColor3f(0.7f, 0.65f, 0.5f); // Bronze
        glPushMatrix();
        glTranslatef(0.0f, -1.5f, 0.0f);
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(0.4f, 0.6f, 16, 8);
        glPopMatrix();
        
        // Lâmpada acesa (esfera brilhante)
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        // Halo externo
        glPushMatrix();
        glTranslatef(0.0f, -1.6f, 0.0f);
        glColor4f(1.0f, 0.95f, 0.8f, 0.2f);
        glutSolidSphere(0.35f, 12, 12);
        glPopMatrix();
        
        // Lâmpada central
        glPushMatrix();
        glTranslatef(0.0f, -1.6f, 0.0f);
        glColor4f(1.0f, 0.95f, 0.7f, 0.9f);
        glutSolidSphere(0.2f, 12, 12);
        glPopMatrix();
        
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
        
        glPopMatrix();
        
        // Lado direito
        glPushMatrix();
        glTranslatef(10.0f, 8.5f, posicoes_z[i]); // Abaixadas de 13.0 para 8.5
        
        // Fio/corrente
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.2f, 0.2f, 0.2f);
        glPushMatrix();
        glScalef(0.05f, 2.0f, 0.05f);
        glutSolidCube(1.0f);
        glPopMatrix();
        
        // Cúpula
        sistema_iluminacao.configurar_material_metal();
        glColor3f(0.7f, 0.65f, 0.5f);
        glPushMatrix();
        glTranslatef(0.0f, -1.5f, 0.0f);
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(0.4f, 0.6f, 16, 8);
        glPopMatrix();
        
        // Lâmpada acesa
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        glPushMatrix();
        glTranslatef(0.0f, -1.6f, 0.0f);
        glColor4f(1.0f, 0.95f, 0.8f, 0.2f);
        glutSolidSphere(0.35f, 12, 12);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(0.0f, -1.6f, 0.0f);
        glColor4f(1.0f, 0.95f, 0.7f, 0.9f);
        glutSolidSphere(0.2f, 12, 12);
        glPopMatrix();
        
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
        
        glPopMatrix();
    }
}

// ===== NOVOS OBJETOS RELIGIOSOS =====

void desenha_pia_agua_benta(float x, float z, float rotacao_y) {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(x, base_y, z);
    glRotatef(rotacao_y, 0.0f, 1.0f, 0.0f);
    
    // Pedestal da pia (mármore sem textura)
    glDisable(GL_TEXTURE_2D);
    sistema_iluminacao.configurar_material_marmore();
    glColor3f(0.88f, 0.88f, 0.86f);  // Cinza claro (mármore)
    
    // Base quadrada estável
    glPushMatrix();
    glTranslatef(0.0f, 0.12f, 0.0f);
    glScalef(0.3f, 0.24f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Coluna cilíndrica
    glPushMatrix();
    glTranslatef(0.0f, 0.45f, 0.0f);
    GLUquadric* quad_coluna = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad_coluna, 0.08, 0.08, 0.4, 12, 4);
    gluDeleteQuadric(quad_coluna);
    glPopMatrix();
    
    // Bacia (tigela) - formato de meia esfera
    glColor3f(0.9f, 0.9f, 0.88f);
    glPushMatrix();
    glTranslatef(0.0f, 0.7f, 0.0f);
    glScalef(0.22f, 0.08f, 0.22f);
    glutSolidSphere(1.0f, 16, 16);
    glPopMatrix();
    
    // ÁGUA dentro da pia (MUITO VISÍVEL)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.2f, 0.5f, 0.7f, 0.7f);  // Azul mais escuro e opaco
    glPushMatrix();
    glTranslatef(0.0f, 0.71f, 0.0f);
    glScalef(0.18f, 0.01f, 0.18f);
    glutSolidSphere(1.0f, 16, 16);
    glPopMatrix();
    glDisable(GL_BLEND);
    
    glPopMatrix();
}

void desenha_crucifixo_parede(float x, float y, float z, float rotacao_y, float tamanho) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotacao_y, 0.0f, 1.0f, 0.0f);
    
    // Aplicar textura de madeira escura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gerenciador_texturas.madeira_escura);
    sistema_iluminacao.configurar_material_madeira();
    glColor3f(0.35f, 0.25f, 0.15f);  // Madeira escura
    
    // Barra vertical da cruz
    glPushMatrix();
    glScalef(tamanho * 0.08f, tamanho * 0.5f, tamanho * 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Barra horizontal da cruz
    glPushMatrix();
    glTranslatef(0.0f, tamanho * 0.15f, 0.0f);
    glScalef(tamanho * 0.35f, tamanho * 0.08f, tamanho * 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
    // Cristo (forma simplificada)
    glColor3f(0.85f, 0.75f, 0.65f);  // Cor de pele/bronze
    
    // Cabeça
    glPushMatrix();
    glTranslatef(0.0f, tamanho * 0.25f, tamanho * 0.05f);
    glutSolidSphere(tamanho * 0.06f, 12, 12);
    glPopMatrix();
    
    // Corpo
    glPushMatrix();
    glTranslatef(0.0f, tamanho * 0.05f, tamanho * 0.05f);
    glScalef(tamanho * 0.08f, tamanho * 0.25f, tamanho * 0.06f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Braços
    glPushMatrix();
    glTranslatef(0.0f, tamanho * 0.15f, tamanho * 0.05f);
    glScalef(tamanho * 0.3f, tamanho * 0.06f, tamanho * 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPopMatrix();
}

void desenha_confessionario(float x, float z, float rotacao_y) {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(x, base_y, z);
    glRotatef(rotacao_y, 0.0f, 1.0f, 0.0f);
    
    // SEM textura - usar cor direta de madeira escura
    glDisable(GL_TEXTURE_2D);
    sistema_iluminacao.configurar_material_madeira();
    glColor3f(0.35f, 0.25f, 0.15f);  // Madeira escura diretamente
    
    // Base/piso
    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.0f);
    glScalef(1.2f, 0.1f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Parede esquerda
    glPushMatrix();
    glTranslatef(-0.55f, 1.1f, 0.0f);
    glScalef(0.1f, 2.4f, 1.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Parede direita
    glPushMatrix();
    glTranslatef(0.55f, 1.1f, 0.0f);
    glScalef(0.1f, 2.2f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Parede de trás
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, -0.45f);
    glScalef(1.2f, 2.2f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Teto
    glPushMatrix();
    glTranslatef(0.0f, 2.15f, 0.0f);
    glScalef(1.2f, 0.1f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Divisória central (separa padre e penitente)
    glColor3f(0.3f, 0.22f, 0.14f);
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);
    glScalef(0.05f, 1.8f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Pequena grade na divisória (treliça)
    glColor3f(0.15f, 0.15f, 0.15f);
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(0.02f, 1.2f + i * 0.08f, 0.0f);
        glScalef(0.02f, 0.02f, 0.6f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    
    // Cortina na entrada (tecido vermelho sem textura)
    glColor3f(0.6f, 0.1f, 0.1f);  // Vermelho escuro
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.45f);
    glScalef(1.0f, 1.8f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPopMatrix();
}

void desenha_pulpito(float x, float z, float rotacao_y) {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(x, base_y, z);
    glRotatef(rotacao_y, 0.0f, 1.0f, 0.0f);
    
    // SEM textura - usar cor direta
    glDisable(GL_TEXTURE_2D);
    sistema_iluminacao.configurar_material_madeira();
    glColor3f(0.4f, 0.28f, 0.18f);  // Madeira marrom
    
    // Base sólida (plataforma)
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);
    glScalef(0.8f, 0.6f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Coluna de suporte (cilindro MAIS BAIXO)
    glPushMatrix();
    glTranslatef(0.0f, 0.65f, 0.0f);  // Abaixado de 0.75f para 0.65f
    GLUquadric* quad_coluna = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad_coluna, 0.15, 0.15, 0.5, 12, 4);  // Altura reduzida de 0.6 para 0.5
    gluDeleteQuadric(quad_coluna);
    glPopMatrix();
    
    // Mesa do púlpito (onde apoia os papéis) - ajustada
    glColor3f(0.45f, 0.32f, 0.20f);
    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f);  // Abaixado de 1.0f para 0.9f
    glScalef(0.7f, 0.08f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Painel frontal inclinado - ajustado
    glPushMatrix();
    glTranslatef(0.0f, 1.05f, 0.25f);  // Abaixado de 1.15f para 1.05f
    glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.65f, 0.4f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Cruz dourada pequena no painel - ajustada
    glColor3f(0.85f, 0.7f, 0.3f);  // Dourado
    glPushMatrix();
    glTranslatef(0.0f, 1.05f, 0.28f);  // Abaixado de 1.15f para 1.05f
    // Vertical
    glPushMatrix();
    glScalef(0.02f, 0.08f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Horizontal
    glPushMatrix();
    glTranslatef(0.0f, 0.02f, 0.0f);
    glScalef(0.05f, 0.02f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();
    
    glPopMatrix();
}

void desenha_objetos_religiosos() {
    // Pias de água benta BEM nos cantos da entrada
    desenha_pia_agua_benta(-11.0f, Z_INTERNO/2 - 1.2f, 45.0f);   // Canto esquerdo
    desenha_pia_agua_benta(11.0f, Z_INTERNO/2 - 1.2f, -45.0f);   // Canto direito
    
    // Crucifixos nas paredes laterais (meio da igreja)
    desenha_crucifixo_parede(-X_INTERNO/2 + 0.15f, ALTURA_PLATAFORMA + 3.5f, -5.0f, 90.0f, 1.2f);
    desenha_crucifixo_parede(X_INTERNO/2 - 0.15f, ALTURA_PLATAFORMA + 3.5f, -5.0f, -90.0f, 1.2f);
    
    // APENAS 1 Confessionário no canto traseiro esquerdo
    desenha_confessionario(-11.5f, Z_INTERNO/2 - 4.5f, 45.0f);
    
    // Púlpito ao lado esquerdo do altar (não invade bancos)
    desenha_pulpito(-8.5f, -Z_INTERNO/2 + 5.5f, 45.0f);
}

void desenha_interior() {
    desenha_piso_marmore(); // Piso de mármore
    desenha_caminho_verde(); // Tapete vermelho sobre o piso
    desenha_altar(); // Altar principal
    desenha_pedestal_biblia(); // Pedestal com Bíblia ao lado do altar
    desenha_cruz_grande();
    desenha_bancos();
    desenha_arranjos_flores(); // Adicionar arranjos de flores brancas
    desenha_casticais_e_velas(); // Adicionar castiçais e velas
    desenha_lampadas_pendentes(); // Lâmpadas pendentes no teto
    desenha_objetos_religiosos(); // Novos objetos: pias, crucifixos, confessionários, púlpito
}
