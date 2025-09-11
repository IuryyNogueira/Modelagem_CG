#include "arco.h"
#include <cmath>

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
