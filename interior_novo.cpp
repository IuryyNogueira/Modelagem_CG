#include "interior.h"
#include "constantes.h"
#include <cmath>

void desenha_altar() {
    // Altar no fundo da igreja (como na imagem real)
    float largura_altar = 10.0f;
    float altura_altar = 1.5f;
    float profundidade_altar = 4.0f;
    float base_y = ALTURA_PLATAFORMA;
    
    // Parede de fundo do altar (cor laranja/terracota como na imagem)
    glColor3f(0.8f, 0.4f, 0.2f); // Cor terracota
    glPushMatrix();
    glTranslatef(0.0f, base_y + 6.0f, -COMPRIMENTO + 2.0f);
    glScalef(LARGURA - 4.0f, 12.0f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Base elevada do altar
    glColor3f(0.7f, 0.6f, 0.5f); // Cor de pedra/concreto
    glPushMatrix();
    glTranslatef(0.0f, base_y + altura_altar/2 + 0.5f, -COMPRIMENTO + 6.0f);
    glScalef(largura_altar + 2.0f, altura_altar, profundidade_altar + 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Mesa do altar (madeira)
    glColor3f(0.6f, 0.4f, 0.2f); // Madeira escura como na imagem
    glPushMatrix();
    glTranslatef(0.0f, base_y + altura_altar + 0.9f, -COMPRIMENTO + 6.0f);
    glScalef(largura_altar, 0.3f, profundidade_altar);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Cruz no altar
    glColor3f(0.9f, 0.8f, 0.7f); // Cor clara para a cruz
    glPushMatrix();
    glTranslatef(0.0f, base_y + altura_altar + 2.0f, -COMPRIMENTO + 4.0f);
    // Haste vertical
    glPushMatrix();
    glScalef(0.3f, 3.0f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Haste horizontal
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(1.8f, 0.3f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();
}

void desenha_bancos() {
    // Bancos como na imagem real - madeira marrom, organizados em fileiras
    int fileiras = 10;
    float largura_banco = 8.0f;
    float altura_banco = 0.8f;
    float profundidade_banco = 1.8f;
    float espacamento_fileiras = 2.5f;
    float espacamento_lateral = 1.0f;
    float largura_corredor = 3.0f;
    float base_y = ALTURA_PLATAFORMA;
    
    glColor3f(0.55f, 0.35f, 0.15f); // Madeira marrom como na imagem
    
    for (int i = 0; i < fileiras; ++i) {
        float z_pos = -8.0f - i * espacamento_fileiras;
        
        // Bancos da seção esquerda
        for (int j = 0; j < 2; ++j) {
            float x_pos = -largura_corredor/2 - espacamento_lateral - largura_banco/2 - j * (largura_banco + espacamento_lateral);
            
            // Assento do banco
            glPushMatrix();
            glTranslatef(x_pos, base_y + altura_banco/2, z_pos);
            glScalef(largura_banco, altura_banco, profundidade_banco);
            glutSolidCube(1.0f);
            glPopMatrix();
            
            // Encosto do banco (virado para o altar)
            glColor3f(0.5f, 0.3f, 0.1f); // Madeira um pouco mais escura
            glPushMatrix();
            glTranslatef(x_pos, base_y + altura_banco + 0.6f, z_pos - profundidade_banco/2 + 0.15f);
            glScalef(largura_banco, 1.2f, 0.3f);
            glutSolidCube(1.0f);
            glPopMatrix();
            glColor3f(0.55f, 0.35f, 0.15f); // Restaurar cor
        }
        
        // Bancos da seção direita
        for (int j = 0; j < 2; ++j) {
            float x_pos = largura_corredor/2 + espacamento_lateral + largura_banco/2 + j * (largura_banco + espacamento_lateral);
            
            // Assento do banco
            glPushMatrix();
            glTranslatef(x_pos, base_y + altura_banco/2, z_pos);
            glScalef(largura_banco, altura_banco, profundidade_banco);
            glutSolidCube(1.0f);
            glPopMatrix();
            
            // Encosto do banco (virado para o altar)
            glColor3f(0.5f, 0.3f, 0.1f);
            glPushMatrix();
            glTranslatef(x_pos, base_y + altura_banco + 0.6f, z_pos - profundidade_banco/2 + 0.15f);
            glScalef(largura_banco, 1.2f, 0.3f);
            glutSolidCube(1.0f);
            glPopMatrix();
            glColor3f(0.55f, 0.35f, 0.15f); // Restaurar cor
        }
    }
}

void desenha_pulpito() {
    // Púlpito moderno na lateral direita (como nas igrejas modernas)
    float base_y = ALTURA_PLATAFORMA;
    
    glColor3f(0.6f, 0.4f, 0.2f); // Madeira escura
    
    glPushMatrix();
    glTranslatef(15.0f, base_y + 1.8f, -COMPRIMENTO + 15.0f); // Lateral direita, próximo ao altar
    
    // Base do púlpito (mais moderna e elegante)
    glPushMatrix();
    glScalef(3.0f, 3.6f, 2.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Superfície do púlpito
    glColor3f(0.55f, 0.35f, 0.15f);
    glPushMatrix();
    glTranslatef(0.0f, 1.8f, 0.5f);
    glScalef(3.2f, 0.2f, 1.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Pequenos degraus de acesso
    glColor3f(0.5f, 0.3f, 0.1f);
    for (int i = 0; i < 2; ++i) {
        glPushMatrix();
        glTranslatef(-2.0f, -1.8f + i * 0.4f, 0.0f);
        glScalef(1.2f, 0.3f, 2.0f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    
    glPopMatrix();
}

void desenha_colunas() {
    // Remover colunas - a igreja da imagem não tem colunas internas visíveis
    // A estrutura metálica do teto é suficiente
}

void desenha_pia_batismal() {
    // Simplificar - não é muito visível na imagem real
}

void desenha_confessionarios() {
    // Remover confessionários - não aparecem na igreja moderna da imagem
}

void desenha_decoracoes() {
    // Elementos decorativos simples como na igreja real
    float base_y = ALTURA_PLATAFORMA;
    
    // Símbolos ou objetos simples no altar
    glColor3f(0.8f, 0.7f, 0.2f); // Dourado
    
    // Objetos simples no altar
    glPushMatrix();
    glTranslatef(-1.5f, base_y + 2.5f, -COMPRIMENTO + 6.0f);
    glScalef(0.4f, 0.8f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.5f, base_y + 2.5f, -COMPRIMENTO + 6.0f);
    glScalef(0.4f, 0.8f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void desenha_piso() {
    // Piso de concreto/pedra como na imagem real
    float base_y = ALTURA_PLATAFORMA;
    
    glColor3f(0.75f, 0.75f, 0.78f); // Cor de concreto/pedra clara
    
    // Piso principal da igreja
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-LARGURA/2 + 1.0f, base_y + 0.01f, -1.0f);
        glVertex3f(LARGURA/2 - 1.0f, base_y + 0.01f, -1.0f);
        glVertex3f(LARGURA/2 - 1.0f, base_y + 0.01f, -COMPRIMENTO + 1.0f);
        glVertex3f(-LARGURA/2 + 1.0f, base_y + 0.01f, -COMPRIMENTO + 1.0f);
    glEnd();
    
    // Corredor central (cor ligeiramente diferente)
    glColor3f(0.7f, 0.7f, 0.73f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.5f, base_y + 0.02f, -1.0f);
        glVertex3f(1.5f, base_y + 0.02f, -1.0f);
        glVertex3f(1.5f, base_y + 0.02f, -COMPRIMENTO + 8.0f);
        glVertex3f(-1.5f, base_y + 0.02f, -COMPRIMENTO + 8.0f);
    glEnd();
    
    // Área elevada do altar
    glColor3f(0.8f, 0.8f, 0.82f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-LARGURA/2 + 2.0f, base_y + 0.5f, -COMPRIMENTO + 8.0f);
        glVertex3f(LARGURA/2 - 2.0f, base_y + 0.5f, -COMPRIMENTO + 8.0f);
        glVertex3f(LARGURA/2 - 2.0f, base_y + 0.5f, -COMPRIMENTO + 1.0f);
        glVertex3f(-LARGURA/2 + 2.0f, base_y + 0.5f, -COMPRIMENTO + 1.0f);
    glEnd();
}

void desenha_interior() {
    desenha_piso();
    desenha_altar();
    desenha_bancos();
    desenha_pulpito();
    desenha_colunas();
    desenha_pia_batismal();
    desenha_confessionarios();
    desenha_decoracoes();
}
