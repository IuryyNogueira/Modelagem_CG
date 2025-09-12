#include "constantes.h"

// --- Medidas principais seguindo a planta baixa ---
const float X_TERRENO = 45.0f;           // Largura total da igreja
const float Z_TERRENO = 50.0f;       // Profundidade total 
const float H_MURO_TERRENO = 2.0f;      // Altura do muro ao redor do terreno
const float RECUO_ESQUERDO = 4.0f; // Recuo da parede esquerda

const float NIVEL_IGREJA = 1.0f; // Nível do chão da igreja (altura da plataforma)
const float NIVEL_TERRENO = 0.5f; // Nível do terreno (chão ao redor da igreja)

const float X_INTERNO = 32.0f;   // Largura interna
const float Z_INTERNO = 25.0f; // Comprimento interno
const float ESPESSURA_PAREDE = 0.15f; // Espessura das paredes
const float PE_DIREITO_IGREJA = 4.5f;// Altura até o topo da parede (pé direito)

const float X_PLATAFORMA_IGREJA = 36.0f;   // Largura da plataforma (um pouco maior que a igreja)
const float Z_PLATAFORMA_IGREJA = 27.0f; // Profundidade da plataforma (um pouco maior que a igreja)

const float INCLINACAO_TELHADO = 0.15f; // 30% de inclinação
const float ALTURA_TELHADO = X_INTERNO * INCLINACAO_TELHADO;    // Altura adicional do telhado

const float X_ESCADA = 11.0f;   // Largura da escada
const float Z_ESCADA = 8.0f; // Profundidade da escada
const float ALTURA_PLATAFORMA = 1.0f; // Altura da plataforma (mesmo nível do topo da escada)
const int NUM_DEGRAUS = 6; // Número de degraus na escada
const float PROFUNDIDADE_DEGRAU = Z_ESCADA / NUM_DEGRAUS; // Profundidade de cada degrau
const float ALTURA_DEGRAU = ALTURA_PLATAFORMA / NUM_DEGRAUS; // Altura de cada degrau

// --- Controle da câmera em primeira pessoa ---
float pos_x = 0.0f;
float pos_y = 1.7f; // altura dos olhos de uma pessoa (1.70m)
float pos_z = 15.0f; // posição mais próxima para escala humana
float dir = 0.0f; // direção em radianos (0 = olhando para -z)
float pitch = 0.0f; // sem inclinação inicial
const float VELOCIDADE = 0.3f;
const float SENSIBILIDADE = 0.05f; // Rotação mais suave

// --- Controle do mouse ---
int last_mouse_x = -1;
int last_mouse_y = -1;
bool mouse_initialized = false;
const float SENS_MOUSE = 0.003f; // Sensibilidade do mouse mais confortável

// --- Flags para teclas pressionadas ---
bool keyStates[256] = {false};

/**
 * @brief Desenha um bloco (paralelepípedo) em uma posição específica.
 * * @param largura A dimensão total no eixo X.
 * @param altura A dimensão total no eixo Y.
 * @param profundidade A dimensão total no eixo Z.
 * @param posX A coordenada X para a translação do bloco. Padrão é 0.
 * @param posY A coordenada Y para a translação do bloco. Padrão é 0.
 * @param posZ A coordenada Z para a translação do bloco. Padrão é 0.
 */
void desenha_bloco(float largura, float altura, float profundidade, 
                   float posX, float posY, float posZ) {
    
    // --- NOVO: Bloco de Transformação ---
    // Salva a matriz de transformação atual no topo da pilha.
    // Isso garante que nossas transformações (translação, etc.) 
    // sejam locais e não afetem outros objetos na cena.
    glPushMatrix();

    // Aplica a translação usando os novos parâmetros.
    // Move o "pincel" para a posição desejada antes de desenhar.
    glTranslatef(posX, posY, posZ);

    // --- O código de desenho a partir daqui é EXATAMENTE o mesmo de antes ---

    // Coordenadas dos 8 vértices únicos do bloco (definidos localmente)
    //      6--------7
    //     /|       /|
    //    / |      / |
    //   2--------3  |
    //   |  5-----|--4
    //   | /      | /
    //   |/       |/
    //   1--------0
    
    float x = largura / 2.0f;
    float y = altura; // Base em y=0
    float z = profundidade / 2.0f;

    GLfloat vertices[8][3] = {
        { x, 0,  z}, { -x, 0,  z}, { -x, y,  z}, {  x, y,  z}, // Frente: 0, 1, 2, 3
        { x, 0, -z}, { -x, 0, -z}, { -x, y, -z}, {  x, y, -z}  // Trás:   4, 5, 6, 7
    };

    GLint faces[6][4] = {
        {0, 1, 2, 3}, {4, 5, 6, 7}, {3, 2, 6, 7},
        {0, 1, 5, 4}, {1, 5, 6, 2}, {0, 4, 7, 3}
    };

    GLfloat normais[6][3] = {
        {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}, {0.0, 1.0, 0.0},
        {0.0, -1.0, 0.0}, {-1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}
    };

    // Desenha as 6 faces do bloco
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        glNormal3fv(normais[i]);
        for (int j = 0; j < 4; j++) {
            glVertex3fv(vertices[faces[i][j]]);
        }
    }
    glEnd();

    // --- NOVO: Finalização do Bloco de Transformação ---
    // Restaura a matriz de transformação que salvamos no início.
    // Isso descarta a nossa translação e garante que o próximo objeto
    // a ser desenhado comece do estado original.
    glPopMatrix();
}

// Lembrete da preferência do usuário: incluir a implementação completa do método.

/**
 * @brief Desenha um prisma triangular (como a empena de um telhado) em uma posição específica.
 * @param largura A largura da base do triângulo (eixo X).
 * @param altura A altura do triângulo, do centro da base ao topo (eixo Y).
 * @param profundidade A profundidade/espessura do prisma (eixo Z).
 * @param posX A coordenada X para a translação do prisma. Padrão é 0.
 * @param posY A coordenada Y para a translação do prisma. Padrão é 0.
 * @param posZ A coordenada Z para a translação do prisma. Padrão é 0.
 */
void desenha_prisma_triangular(float largura, float altura, float profundidade,
                               float posX, float posY, float posZ) {

    glPushMatrix();
    glTranslatef(posX, posY, posZ);

    // Definimos os 6 vértices únicos do prisma.
    // A base fica em Y=0.
    //      2
    //     / \
    //    /   \
    //   0-----1  (Face da frente, com Z positivo)
    //
    //      5
    //     / \
    //    /   \
    //   3-----4  (Face de trás, com Z negativo)

    float x = largura / 2.0f;
    float y = altura;
    float z = profundidade / 2.0f;

    GLfloat vertices[6][3] = {
        {-x, 0,  z}, // 0: inferior-esquerda-frente
        { x, 0,  z}, // 1: inferior-direita-frente
        { 0, y,  z}, // 2: superior-centro-frente
        {-x, 0, -z}, // 3: inferior-esquerda-trás
        { x, 0, -z}, // 4: inferior-direita-trás
        { 0, y, -z}  // 5: superior-centro-trás
    };
    
    // Normais para as 5 faces. As normais das rampas são calculadas
    // para serem perpendiculares às faces inclinadas.
    GLfloat normais[5][3] = {
        {0.0, 0.0, 1.0},        // 0: Frente
        {0.0, 0.0, -1.0},       // 1: Trás
        {0.0, -1.0, 0.0},       // 2: Base
        {-altura, x, 0.0},      // 3: Rampa esquerda (vetor (-y, x))
        { altura, x, 0.0}       // 4: Rampa direita (vetor (y, x))
    };


    // --- Desenha as faces triangulares ---
    glBegin(GL_TRIANGLES);
        // Face da Frente
        glNormal3fv(normais[0]);
        glVertex3fv(vertices[0]);
        glVertex3fv(vertices[1]);
        glVertex3fv(vertices[2]);

        // Face de Trás
        glNormal3fv(normais[1]);
        glVertex3fv(vertices[4]); // Ordem anti-horária vista de trás
        glVertex3fv(vertices[3]);
        glVertex3fv(vertices[5]);
    glEnd();

    // --- Desenha as faces retangulares (Quads) ---
    glBegin(GL_QUADS);
        // Base
        glNormal3fv(normais[2]);
        glVertex3fv(vertices[1]); // Ordem anti-horária vista de baixo
        glVertex3fv(vertices[0]);
        glVertex3fv(vertices[3]);
        glVertex3fv(vertices[4]);

        // Rampa Esquerda
        glNormal3fv(normais[3]);
        glVertex3fv(vertices[0]);
        glVertex3fv(vertices[2]);
        glVertex3fv(vertices[5]);
        glVertex3fv(vertices[3]);

        // Rampa Direita
        glNormal3fv(normais[4]);
        glVertex3fv(vertices[2]);
        glVertex3fv(vertices[1]);
        glVertex3fv(vertices[4]);
        glVertex3fv(vertices[5]);
    glEnd();

    glPopMatrix();
}