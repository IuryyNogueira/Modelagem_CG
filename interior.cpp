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
        glVertex3f(-1.2f, base_y + 0.02f, Z_INTERNO/2 - 1.0f); // Começa próximo à entrada
        glVertex3f(1.2f, base_y + 0.02f, Z_INTERNO/2 - 1.0f);
        glVertex3f(1.2f, base_y + 0.02f, -Z_INTERNO/2 + 5.0f); // Termina antes do altar
        glVertex3f(-1.2f, base_y + 0.02f, -Z_INTERNO/2 + 5.0f);
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

void desenha_bancos() {
    // Bancos inclinados no sentido anti-horário (posicionados corretamente)
    // Duas fileiras de cada lado do caminho verde
    
    float rotacao = -8.0f; // Inclinação anti-horária
    
    // Lado esquerdo - primeira fileira (mais próxima do caminho)
    for(int i = 0; i < 5; i++) {
        float z = Z_INTERNO/2 - 4.0f - i * 3.0f; // Espaçamento de 3m entre bancos
        desenha_banco_individual(-4.0f, z, rotacao);
    }
    
    // Lado esquerdo - segunda fileira (mais próxima da parede)
    for(int i = 0; i < 5; i++) {
        float z = Z_INTERNO/2 - 4.0f - i * 3.0f;
        desenha_banco_individual(-8.0f, z, rotacao);
    }
    
    // Lado direito - primeira fileira (mais próxima do caminho)
    for(int i = 0; i < 5; i++) {
        float z = Z_INTERNO/2 - 4.0f - i * 3.0f;
        desenha_banco_individual(4.0f, z, -rotacao); // Rotação oposta
    }
    
    // Lado direito - segunda fileira (mais próxima da parede)
    for(int i = 0; i < 5; i++) {
        float z = Z_INTERNO/2 - 4.0f - i * 3.0f;
        desenha_banco_individual(8.0f, z, -rotacao); // Rotação oposta
    }
}

void desenha_interior() {
    // Removido desenha_piso() - usando o piso original
    desenha_caminho_verde();
    desenha_altar();
    desenha_cruz_grande();
    desenha_bancos();
    desenha_arranjos_flores(); // Adicionar arranjos de flores brancas
}
//     // Altar no fundo da igreja (como na imagem real)
//     float largura_altar = 10.0f;
//     float altura_altar = 1.5f;
//     float profundidade_altar = 4.0f;
//     float base_y = ALTURA_PLATAFORMA;
    
//     // Parede de fundo do altar (cor laranja/terracota como na imagem)
//     glColor3f(0.8f, 0.4f, 0.2f); // Cor terracota
//     glPushMatrix();
//     glTranslatef(0.0f, base_y + 6.0f, -COMPRIMENTO + 2.0f);
//     glScalef(LARGURA - 4.0f, 12.0f, 1.0f);
//     glutSolidCube(1.0f);
//     glPopMatrix();
    
//     // Base elevada do altar
//     glColor3f(0.7f, 0.6f, 0.5f); // Cor de pedra/concreto
//     glPushMatrix();
//     glTranslatef(0.0f, base_y + altura_altar/2 + 0.5f, -COMPRIMENTO + 6.0f);
//     glScalef(largura_altar + 2.0f, altura_altar, profundidade_altar + 2.0f);
//     glutSolidCube(1.0f);
//     glPopMatrix();
    
//     // Mesa do altar (madeira)
//     glColor3f(0.6f, 0.4f, 0.2f); // Madeira escura como na imagem
//     glPushMatrix();
//     glTranslatef(0.0f, base_y + altura_altar + 0.9f, -COMPRIMENTO + 6.0f);
//     glScalef(largura_altar, 0.3f, profundidade_altar);
//     glutSolidCube(1.0f);
//     glPopMatrix();
    
//     // Cruz no altar
//     glColor3f(0.9f, 0.8f, 0.7f); // Cor clara para a cruz
//     glPushMatrix();
//     glTranslatef(0.0f, base_y + altura_altar + 2.0f, -COMPRIMENTO + 4.0f);
//     // Haste vertical
//     glPushMatrix();
//     glScalef(0.3f, 3.0f, 0.3f);
//     glutSolidCube(1.0f);
//     glPopMatrix();
//     // Haste horizontal
//     glPushMatrix();
//     glTranslatef(0.0f, 0.5f, 0.0f);
//     glScalef(1.8f, 0.3f, 0.3f);
//     glutSolidCube(1.0f);
//     glPopMatrix();
//     glPopMatrix();
// }

// void desenha_bancos() {
//     // Bancos removidos para melhorar a vista da igreja
// }

// void desenha_pulpito() {
//     // Púlpito moderno na lateral direita (como nas igrejas modernas)
//     float base_y = ALTURA_PLATAFORMA;
    
//     glColor3f(0.6f, 0.4f, 0.2f); // Madeira escura
    
//     glPushMatrix();
//     glTranslatef(15.0f, base_y + 1.8f, -COMPRIMENTO + 15.0f); // Lateral direita, próximo ao altar
    
//     // Base do púlpito (mais moderna e elegante)
//     glPushMatrix();
//     glScalef(3.0f, 3.6f, 2.5f);
//     glutSolidCube(1.0f);
//     glPopMatrix();
    
//     // Superfície do púlpito
//     glColor3f(0.55f, 0.35f, 0.15f);
//     glPushMatrix();
//     glTranslatef(0.0f, 1.8f, 0.5f);
//     glScalef(3.2f, 0.2f, 1.8f);
//     glutSolidCube(1.0f);
//     glPopMatrix();
    
//     // Pequenos degraus de acesso
//     glColor3f(0.5f, 0.3f, 0.1f);
//     for (int i = 0; i < 2; ++i) {
//         glPushMatrix();
//         glTranslatef(-2.0f, -1.8f + i * 0.4f, 0.0f);
//         glScalef(1.2f, 0.3f, 2.0f);
//         glutSolidCube(1.0f);
//         glPopMatrix();
//     }
    
//     glPopMatrix();
// }

// void desenha_colunas() {
//     // Remover colunas - a igreja da imagem não tem colunas internas visíveis
//     // A estrutura metálica do teto é suficiente
// }

// void desenha_pia_batismal() {
//     // Simplificar - não é muito visível na imagem real
// }

// void desenha_confessionarios() {
//     // Remover confessionários - não aparecem na igreja moderna da imagem
// }

// void desenha_decoracoes() {
//     // Elementos decorativos simples como na igreja real
//     float base_y = ALTURA_PLATAFORMA;
    
//     // Símbolos ou objetos simples no altar
//     glColor3f(0.8f, 0.7f, 0.2f); // Dourado
    
//     // Objetos simples no altar
//     glPushMatrix();
//     glTranslatef(-1.5f, base_y + 2.5f, -COMPRIMENTO + 6.0f);
//     glScalef(0.4f, 0.8f, 0.4f);
//     glutSolidCube(1.0f);
//     glPopMatrix();
    
//     glPushMatrix();
//     glTranslatef(1.5f, base_y + 2.5f, -COMPRIMENTO + 6.0f);
//     glScalef(0.4f, 0.8f, 0.4f);
//     glutSolidCube(1.0f);
//     glPopMatrix();
// }

// void desenha_piso() {
//     // Piso de concreto/pedra como na imagem real
//     float base_y = ALTURA_PLATAFORMA;
    
//     glColor3f(0.75f, 0.75f, 0.78f); // Cor de concreto/pedra clara
    
//     // Piso principal da igreja
//     glBegin(GL_QUADS);
//         glNormal3f(0.0f, 1.0f, 0.0f);
//         glVertex3f(-LARGURA/2 + 1.0f, base_y + 0.01f, -1.0f);
//         glVertex3f(LARGURA/2 - 1.0f, base_y + 0.01f, -1.0f);
//         glVertex3f(LARGURA/2 - 1.0f, base_y + 0.01f, -COMPRIMENTO + 1.0f);
//         glVertex3f(-LARGURA/2 + 1.0f, base_y + 0.01f, -COMPRIMENTO + 1.0f);
//     glEnd();
    
//     // Corredor central (cor ligeiramente diferente)
//     glColor3f(0.7f, 0.7f, 0.73f);
//     glBegin(GL_QUADS);
//         glNormal3f(0.0f, 1.0f, 0.0f);
//         glVertex3f(-1.5f, base_y + 0.02f, -1.0f);
//         glVertex3f(1.5f, base_y + 0.02f, -1.0f);
//         glVertex3f(1.5f, base_y + 0.02f, -COMPRIMENTO + 8.0f);
//         glVertex3f(-1.5f, base_y + 0.02f, -COMPRIMENTO + 8.0f);
//     glEnd();
    
//     // Área elevada do altar
//     glColor3f(0.8f, 0.8f, 0.82f);
//     glBegin(GL_QUADS);
//         glNormal3f(0.0f, 1.0f, 0.0f);
//         glVertex3f(-LARGURA/2 + 2.0f, base_y + 0.5f, -COMPRIMENTO + 8.0f);
//         glVertex3f(LARGURA/2 - 2.0f, base_y + 0.5f, -COMPRIMENTO + 8.0f);
//         glVertex3f(LARGURA/2 - 2.0f, base_y + 0.5f, -COMPRIMENTO + 1.0f);
//         glVertex3f(-LARGURA/2 + 2.0f, base_y + 0.5f, -COMPRIMENTO + 1.0f);
//     glEnd();
// }

// void desenha_interior() {
//     desenha_piso();
//     desenha_altar();
//     desenha_bancos();
//     desenha_pulpito();
//     desenha_colunas();
//     desenha_pia_batismal();
//     desenha_confessionarios();
//     desenha_decoracoes();
// }
