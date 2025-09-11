#include "igreja.h"
#include "parede.h"
#include "telhado.h"
#include "escada.h"
#include "arco.h"

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
