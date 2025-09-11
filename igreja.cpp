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
    glutCreateWindow("Igreja 3D - C++ / OpenGL | Comandos: W/S/A/D (Rotacao) Q/E (Zoom)");

    inicializa();

    glutDisplayFunc(display);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}