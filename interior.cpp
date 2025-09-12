#include "interior.h"
#include "constantes.h"
#include <cmath>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void desenha_altar() {
    float base_y = ALTURA_PLATAFORMA;
    
    // Altar retangular branco no final da igreja (posicionado corretamente)
    glColor3f(0.95f, 0.95f, 0.95f); // Branco do altar
    glPushMatrix();
    glTranslatef(0.0f, base_y + 0.4f, -Z_INTERNO/2 + 3.0f); // Próximo à parede traseira
    glScalef(6.0f, 0.8f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Base do altar um pouco mais baixa
    glColor3f(0.9f, 0.9f, 0.9f);
    glPushMatrix();
    glTranslatef(0.0f, base_y + 0.15f, -Z_INTERNO/2 + 3.0f);
    glScalef(8.0f, 0.3f, 2.5f);
    glutSolidCube(1.0f);
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
    
    // Caminho verde central (da entrada até próximo ao altar)
    glColor3f(0.2f, 0.6f, 0.2f); // Verde do caminho
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.2f, base_y + 0.02f, Z_INTERNO/2 - 3.0f); // Começa mais dentro da igreja
        glVertex3f(1.2f, base_y + 0.02f, Z_INTERNO/2 - 3.0f);
        glVertex3f(1.2f, base_y + 0.02f, -Z_INTERNO/2 + 6.0f); // Termina um pouco antes do altar
        glVertex3f(-1.2f, base_y + 0.02f, -Z_INTERNO/2 + 6.0f);
    glEnd();
}

void desenha_banco_individual(float x, float z, float rotacao) {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(x, base_y, z);
    glRotatef(rotacao, 0.0f, 1.0f, 0.0f); // Rotação anti-horária
    
    // Cor madeira dos bancos
    glColor3f(0.6f, 0.4f, 0.2f);
    
    // Assento do banco - menor
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);
    glScalef(2.5f, 0.1f, 0.8f); // Reduzido significativamente
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Encosto do banco - menor
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.3f); // Corrigido: encosto atrás do assento
    glScalef(2.5f, 0.7f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Pés do banco (4 pés) - menores
    for(int i = 0; i < 4; i++) {
        float px = (i % 2 == 0) ? -1.1f : 1.1f;
        float pz = (i < 2) ? 0.3f : -0.3f;
        
        glPushMatrix();
        glTranslatef(px, 0.125f, pz);
        glScalef(0.1f, 0.25f, 0.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    
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
    
    // Arranjos decorativos ao longo do caminho
    desenha_arranjo_flores(-2.5f, 0.0f);  // Meio do caminho, lado esquerdo
    desenha_arranjo_flores(2.5f, 0.0f);   // Meio do caminho, lado direito
    
    // Arranjos nas laterais próximo ao altar
    desenha_arranjo_flores(-5.0f, -Z_INTERNO/2 + 8.0f);
    desenha_arranjo_flores(5.0f, -Z_INTERNO/2 + 8.0f);
}

void desenha_biblia() {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(0.0f, base_y + 0.8f + 0.04f, -Z_INTERNO/2 + 3.0f); // Apoiada no topo do altar
    
    // Livro da bíblia (formato retangular achatado)
    glColor3f(0.2f, 0.1f, 0.05f); // Marrom escuro (couro)
    glPushMatrix();
    glRotatef(15.0f, 0.0f, 1.0f, 0.0f); // Ligeiramente rotacionada para parecer natural
    glScalef(0.6f, 0.08f, 0.4f); // Livro achatado
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Páginas (cor mais clara)
    glColor3f(0.95f, 0.92f, 0.85f); // Cor de papel envelhecido
    glPushMatrix();
    glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.05f, 0.05f, 0.0f); // Ligeiramente deslocado para simular páginas
    glScalef(0.55f, 0.05f, 0.35f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Cruz dourada na capa (pequena)
    glColor3f(0.8f, 0.6f, 0.1f); // Dourado
    glPushMatrix();
    glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.08f, -0.1f);
    
    // Haste vertical da cruz
    glPushMatrix();
    glScalef(0.02f, 0.02f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Haste horizontal da cruz
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.02f);
    glScalef(0.02f, 0.02f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}

void desenha_castical_longo(float x, float z) {
    float base_y = ALTURA_PLATAFORMA;
    
    glPushMatrix();
    glTranslatef(x, base_y, z);
    
    // Base do castiçal (dourado/bronze)
    glColor3f(0.8f, 0.6f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f);
    glScalef(0.4f, 0.4f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Haste longa do castiçal
    glColor3f(0.7f, 0.5f, 0.1f); // Bronze mais escuro
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glScalef(0.08f, 1.6f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Prato do castiçal (onde fica a vela)
    glColor3f(0.8f, 0.6f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, 1.8f, 0.0f);
    glScalef(0.25f, 0.05f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Vela
    glColor3f(0.95f, 0.9f, 0.8f); // Cor de cera
    glPushMatrix();
    glTranslatef(0.0f, 2.1f, 0.0f);
    glScalef(0.12f, 0.6f, 0.12f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Chama da vela (pequena esfera laranja)
    glColor3f(1.0f, 0.5f, 0.0f); // Laranja da chama
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(0.06f, 0.1f, 0.06f);
    glutSolidSphere(1.0f, 8, 8);
    glPopMatrix();
    
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
    
    // Chama da vela
    glColor3f(1.0f, 0.5f, 0.0f); // Laranja da chama
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);
    glScalef(0.08f, 0.12f, 0.08f);
    glutSolidSphere(1.0f, 8, 8);
    glPopMatrix();
    
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

void desenha_interior() {
    // Removido desenha_piso() - usando o piso original
    desenha_caminho_verde();
    desenha_altar();
    desenha_cruz_grande();
    desenha_biblia(); // Bíblia em cima do altar
    desenha_bancos();
    desenha_arranjos_flores(); // Adicionar arranjos de flores brancas
    desenha_casticais_e_velas(); // Adicionar castiçais e velas
}
