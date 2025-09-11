#include <GL/glut.h>
#include <cmath> // Para sin() e cos()
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

// --- Prototipos das funções de desenho ---
void desenha_chao();
void desenha_parede();
void desenha_telhas();
void desenha_escada();
void desenha_arco();
void desenha_igreja();

// ...existing code...

// Função para desenhar o chão (deve ficar junto das outras funções de desenho)
void desenha_chao() {
    float tamanho = 200.0f;
    glColor3f(0.3f, 0.7f, 0.3f); // Verde grama
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-tamanho, 0.0f, -tamanho);
        glVertex3f( tamanho, 0.0f, -tamanho);
        glVertex3f( tamanho, 0.0f,  tamanho);
        glVertex3f(-tamanho, 0.0f,  tamanho);
    glEnd();
}
#include <GL/glut.h>
#include <cmath> // Para sin() e cos()
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
// --- Controle do mouse ---
int last_mouse_x = -1;
int last_mouse_y = -1;
bool mouse_initialized = false;
const float SENS_MOUSE = 0.003f;

void atualiza_camera_mouse(int x, int y) {
    // Usa as variáveis globais dir e pitch corretamente
    extern float dir;
    extern float pitch;
    if (!mouse_initialized) {
        last_mouse_x = x;
        last_mouse_y = y;
        mouse_initialized = true;
        return;
    }
    int dx = x - last_mouse_x;
    int dy = y - last_mouse_y;
    last_mouse_x = x;
    last_mouse_y = y;

    dir += dx * SENS_MOUSE;
    pitch += -dy * SENS_MOUSE;
    if (pitch > 1.2f) pitch = 1.2f;
    if (pitch < -1.2f) pitch = -1.2f;

    glutPostRedisplay();
}
#include <GL/glut.h>
#include <cmath> // Para sin() e cos()
#include <iostream>

// --- Medidas principais ---
const float LARGURA = 45.0f;
const float COMPRIMENTO = 50.0f;
const float ALTURA = 4.5f;
const float INCLINACAO_TELHADO = 0.3f; // 30%


// --- Controle da câmera em primeira pessoa ---
float pos_x = 0.0f;
float pos_y = 2.0f; // altura dos olhos
float pos_z = 10.0f;
float dir = 0.0f; // direção em radianos (0 = olhando para -z)
float pitch = 0.0f; // inclinação vertical
const float VELOCIDADE = 1.0f;
const float SENSIBILIDADE = 0.07f;

void inicializa() {
    glClearColor(0.7f, 0.85f, 1.0f, 1.0f); // Céu azul claro
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Posição da luz
    GLfloat luz_pos[] = {50.0f, 100.0f, 80.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, luz_pos);
}

void desenha_parede() {
    // Frente
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, 0, 0);
        glVertex3f( LARGURA/2, 0, 0);
        glVertex3f( LARGURA/2, ALTURA, 0);
        glVertex3f(-LARGURA/2, ALTURA, 0);
    glEnd();

    // Fundo
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, 0, -COMPRIMENTO);
        glVertex3f( LARGURA/2, 0, -COMPRIMENTO);
        glVertex3f( LARGURA/2, ALTURA, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, ALTURA, -COMPRIMENTO);
    glEnd();

    // Lateral Esquerda
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, 0, 0);
        glVertex3f(-LARGURA/2, 0, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, ALTURA, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, ALTURA, 0);
    glEnd();

    // Lateral Direita
    glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(LARGURA/2, 0, 0);
        glVertex3f(LARGURA/2, 0, -COMPRIMENTO);
        glVertex3f(LARGURA/2, ALTURA, -COMPRIMENTO);
        glVertex3f(LARGURA/2, ALTURA, 0);
    glEnd();
}

void desenha_telhas() {
    float altura_telhas = ALTURA + (LARGURA/2) * INCLINACAO_TELHADO;
    glColor3f(0.8f, 0.2f, 0.2f); // Vermelho telha

    float normal_x = INCLINACAO_TELHADO;
    float normal_y = 1.0f - INCLINACAO_TELHADO;

    // Lado esquerdo
    glNormal3f(-normal_x, normal_y, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-LARGURA/2, ALTURA, 0);
        glVertex3f( 0, altura_telhas, 0);
        glVertex3f( 0, altura_telhas, -COMPRIMENTO);
        glVertex3f(-LARGURA/2, ALTURA, -COMPRIMENTO);
    glEnd();

    // Lado direito
    glNormal3f(normal_x, normal_y, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(LARGURA/2, ALTURA, 0);
        glVertex3f(0, altura_telhas, 0);
        glVertex3f(0, altura_telhas, -COMPRIMENTO);
        glVertex3f(LARGURA/2, ALTURA, -COMPRIMENTO);
    glEnd();
}

void desenha_escada() {
    float largura = 12.0f;
    float profundidade_total = 8.0f;
    float altura_total = 1.5f;
    int degraus = 8;

    float altura_degrau = altura_total / degraus;
    float profundidade_degrau = profundidade_total / degraus;

    glColor3f(0.5f, 0.5f, 0.5f);
    for (int i = 0; i < degraus; ++i) {
        float y_baixo = i * altura_degrau;
        float y_cima = (i + 1) * altura_degrau;
        float z_frente = (i + 1) * profundidade_degrau;
        float z_tras = i * profundidade_degrau;

        // Topo do degrau
        glNormal3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(-largura/2, y_cima, z_tras);
            glVertex3f(largura/2, y_cima, z_tras);
            glVertex3f(largura/2, y_cima, z_frente);
            glVertex3f(-largura/2, y_cima, z_frente);
        glEnd();

        // Frente do degrau
        glNormal3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
            glVertex3f(-largura/2, y_baixo, z_frente);
            glVertex3f(largura/2, y_baixo, z_frente);
            glVertex3f(largura/2, y_cima, z_frente);
            glVertex3f(-largura/2, y_cima, z_frente);
        glEnd();
    }
}

void desenha_arco() {
    float raio_externo = 25.0f;
    float raio_interno = 22.0f;
    int segmentos = 64;
    glColor3f(0.9f, 0.9f, 0.9f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segmentos; ++i) {
        float ang = 3.14159265f * i / segmentos;
        float x_ext = raio_externo * cos(ang);
        float y_ext = raio_externo * sin(ang);
        float x_int = raio_interno * cos(ang);
        float y_int = raio_interno * sin(ang);
        
        if (y_ext < 0) y_ext = 0;
        if (y_int < 0) y_int = 0;

        glVertex3f(x_ext, y_ext, 0.0f);
        glVertex3f(x_int, y_int, 0.0f);
    }
    glEnd();
    glPopMatrix();
}

void desenha_igreja() {
    glPushMatrix();
    glColor3f(0.9f, 0.9f, 0.85f);
    desenha_parede();
    desenha_telhas();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.1f);
    desenha_escada();
    glPopMatrix();

    desenha_arco();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Cálculo da direção da câmera
    float dx = sin(dir) * cos(pitch);
    float dy = sin(pitch);
    float dz = -cos(dir) * cos(pitch);

    gluLookAt(
        pos_x, pos_y, pos_z, // posição da câmera
        pos_x + dx, pos_y + dy, pos_z + dz, // ponto para onde olha
        0.0f, 1.0f, 0.0f // vetor up
    );

    desenha_chao();
    desenha_igreja();
    glutSwapBuffers();
}

void redimensiona(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}


// Flags para teclas pressionadas
bool keyStates[256] = {false};

void teclado(unsigned char key, int x, int y) {
    keyStates[key] = true;
    if (key == 27) // ESC
        exit(0);
}

void teclado_up(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void atualiza_movimento() {
    float move_x = 0.0f, move_z = 0.0f;
    if (keyStates['w']) {
        move_x += sin(dir);
        move_z += -cos(dir);
    }
    if (keyStates['s']) {
        move_x -= sin(dir);
        move_z -= -cos(dir);
    }
    if (keyStates['a']) {
        move_x -= cos(dir);
        move_z -= sin(dir);
    }
    if (keyStates['d']) {
        move_x += cos(dir);
        move_z += sin(dir);
    }
    // Normaliza para não andar mais rápido na diagonal
    float len = sqrt(move_x * move_x + move_z * move_z);
    if (len > 0.01f) {
        move_x /= len;
        move_z /= len;
        pos_x += move_x * VELOCIDADE * 0.2f;
        pos_z += move_z * VELOCIDADE * 0.2f;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Igreja 3D - C++ / OpenGL | W/S/A/D = andar, Mouse = olhar, ESC = sair");

    inicializa();

    glutDisplayFunc(display);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(teclado_up);
    glutPassiveMotionFunc(atualiza_camera_mouse);
    glutIdleFunc(atualiza_movimento);

    glutMainLoop();
    return 0;
}