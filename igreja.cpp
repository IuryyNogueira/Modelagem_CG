#include <GL/glut.h>
#include <iostream>

// Inclusão de todos os módulos
#include "constantes.h"
#include "inicializacao.h"
#include "igreja.h"
#include "controles.h"

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