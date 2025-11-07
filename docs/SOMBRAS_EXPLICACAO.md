# Sobre Sombras no Projeto

## Situação Atual

Atualmente o projeto usa **OpenGL 2.1 (Legacy OpenGL)** com **GLUT**, que tem suporte limitado para sombras realistas.

## O que são Shadow Maps?

Shadow Mapping é uma técnica para criar sombras realistas em 3D. Funciona assim:

1. **Primeiro Passo (Shadow Pass)**: Renderiza a cena do ponto de vista da luz, salvando apenas as profundidades (depth buffer) em uma textura especial chamada "shadow map"

2. **Segundo Passo (Render Pass)**: Renderiza a cena normalmente da câmera, mas para cada pixel:
   - Converte a posição do pixel para o espaço da luz
   - Compara a profundidade atual com o valor no shadow map
   - Se a profundidade for maior = pixel está na sombra
   - Se for menor ou igual = pixel está iluminado

## Implementação em OpenGL 2.1

Para implementar shadow mapping em OpenGL 2.1, você precisaria:

### 1. Framebuffer Objects (FBO)
```cpp
GLuint shadowMapFBO;
GLuint shadowMapTexture;

// Criar FBO para shadow map
glGenFramebuffers(1, &shadowMapFBO);
glGenTextures(1, &shadowMapTexture);

// Configurar textura de profundidade
glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
             SHADOW_WIDTH, SHADOW_HEIGHT, 0, 
             GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
```

### 2. Render Pass da Luz
```cpp
// Renderizar do ponto de vista da luz
glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

// Configurar matriz de projeção da luz
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(90.0, 1.0, 1.0, 100.0);

// Posicionar câmera na posição da luz
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(luz_x, luz_y, luz_z, ...);

// Desenhar apenas geometria (sem cores/texturas)
desenhar_cena_geometria();
```

### 3. Render Pass Normal com Comparação
```cpp
// Renderizar normalmente
glBindFramebuffer(GL_FRAMEBUFFER, 0);

// Ativar comparação de shadow map
glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

// Usar coordenadas de textura geradas automaticamente
glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
// ... configurar matriz de projeção de textura

// Desenhar cena
desenhar_cena_completa();
```

## Alternativas Mais Simples

### 1. Projeção de Sombras no Chão (Planar Shadows)
Técnica mais simples que projeta sombras apenas no plano do chão:

```cpp
void desenhar_sombra_planar(float luz_y) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Matriz de projeção para o chão (y=0)
    GLfloat shadow_matrix[16] = {
        1, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 1, 0,
        0, 1/luz_y, 0, 1
    };
    
    glPushMatrix();
    glMultMatrixf(shadow_matrix);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f); // Sombra semi-transparente
    desenhar_objetos();
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}
```

**Vantagens**: Simples, rápido
**Desvantagens**: Sombras apenas em uma superfície plana

### 2. Stencil Shadow Volumes
Usa o stencil buffer para criar sombras precisas:

```cpp
// Muito complexo - requer cálculo de volumes de sombra
// para cada objeto e cada luz
```

**Vantagens**: Sombras precisas e hard-edged
**Desvantagens**: Muito complexo, pesado

### 3. Ambient Occlusion (Fake AO)
Escurece cantos e áreas onde objetos se encontram:

```cpp
// Ao desenhar objetos próximos ao chão
glColor3f(0.7f, 0.7f, 0.7f); // Mais escuro na base
```

**Vantagens**: Simples, dá profundidade
**Desvantagens**: Não são sombras reais

## Recomendação para Este Projeto

**Opção 1 (Mais Simples)**: 
- Manter como está
- Usar iluminação bem configurada para dar impressão de profundidade
- Adicionar ambient occlusion fake (objetos mais escuros perto do chão)

**Opção 2 (Moderada)**:
- Implementar sombras planares apenas no chão da igreja
- Simples de implementar
- Funciona bem para este tipo de cena

**Opção 3 (Avançada)**:
- Migrar para OpenGL 3.3+ com shaders modernos
- Implementar shadow mapping completo
- Requer reescrever grande parte do código

## Exemplo de Sombra Planar Simples

Se quiser tentar sombras planares simples no chão:

```cpp
void desenhar_sombras_no_chao() {
    // Posição da luz principal (sol)
    float luz_x = 0.0f;
    float luz_y = 20.0f;  // Altura da luz
    float luz_z = 10.0f;
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);  // Não escrever no depth buffer
    
    // Criar matriz de projeção da sombra
    GLfloat shadow_matrix[16];
    float ground_y = ALTURA_PLATAFORMA;
    
    // Calcular matriz de sombra
    shadow_matrix[0] = luz_y;
    shadow_matrix[4] = -luz_x;
    shadow_matrix[8] = -luz_z;
    shadow_matrix[12] = 0;
    
    shadow_matrix[1] = 0;
    shadow_matrix[5] = 0;
    shadow_matrix[9] = 0;
    shadow_matrix[13] = ground_y;
    
    shadow_matrix[2] = 0;
    shadow_matrix[6] = 0;
    shadow_matrix[10] = luz_y;
    shadow_matrix[14] = 0;
    
    shadow_matrix[3] = 0;
    shadow_matrix[7] = -1;
    shadow_matrix[11] = 0;
    shadow_matrix[15] = luz_y;
    
    glPushMatrix();
    glMultMatrixf(shadow_matrix);
    glColor4f(0.0f, 0.0f, 0.0f, 0.4f);  // Sombra semi-transparente
    
    // Redesenhar objetos (só geometria)
    desenhar_bancos();
    desenhar_altar();
    // ... outros objetos
    
    glPopMatrix();
    
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}
```

## Conclusão

Para sombras **realmente corretas** com múltiplas luzes, você precisaria de:
- Shadow mapping (complexo em OpenGL 2.1)
- OU migração para OpenGL moderno (3.3+) com shaders

Para este projeto educacional, **não é essencial** ter sombras perfeitas. A iluminação bem configurada já cria uma cena convincente!
