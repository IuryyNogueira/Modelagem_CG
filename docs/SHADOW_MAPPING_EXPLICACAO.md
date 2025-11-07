# Shadow Mapping Implementado na Igreja 3D

## O que é Shadow Mapping?

Shadow Mapping é uma técnica avançada de renderização de sombras em tempo real que funciona em dois passos:

1. **Primeira Passada (Shadow Map)**: Renderiza a cena do ponto de vista da luz, salvando apenas a profundidade em uma textura
2. **Segunda Passada (Cena Final)**: Renderiza a cena normalmente, comparando a profundidade de cada pixel com a shadow map para determinar se está na sombra

## Implementação Neste Projeto

### Arquivos Modificados:

1. **`sombras.h`** - Nova interface do sistema de sombras
2. **`sombras.cpp`** - Implementação do shadow mapping com FBO e shaders
3. **`shaders/shadow_vertex.glsl`** - Vertex shader para gerar shadow map
4. **`shaders/shadow_fragment.glsl`** - Fragment shader para gerar shadow map  
5. **`shaders/scene_vertex.glsl`** - Vertex shader para renderizar cena com sombras
6. **`shaders/scene_fragment.glsl`** - Fragment shader com cálculo de sombras e PCF
7. **`inicializacao.cpp`** - Inicialização do sistema de sombras
8. **`igreja_componente.cpp`** - Loop de renderização em duas passadas

### Características Implementadas:

- **Frame Buffer Object (FBO)** para renderização off-screen
- **Shadow Map de alta resolução** (2048x2048)
- **PCF (Percentage Closer Filtering)** para sombras suaves (kernel 5x5)
- **Bias automático** para evitar shadow acne
- **Projeção ortográfica** para luz direcional (sol)
- **Shaders GLSL 1.20** compatíveis com OpenGL 2.1+

### Como Funciona:

#### Primeira Passada (Shadow Map):
```cpp
sistema_sombras.iniciar_render_shadow_map();
sistema_sombras.desenhar_geometria_shadow_map(); // Geometria simplificada
sistema_sombras.finalizar_render_shadow_map();
```

#### Segunda Passada (Cena com Sombras):
```cpp
sistema_sombras.iniciar_render_cena(); // Ativa shaders com sombras
desenha_igreja(); // Renderização normal
sistema_sombras.finalizar_render_cena();
```

### Parâmetros Configuráveis:

- **Shadow Bias**: Ajusta o offset para evitar shadow acne (padrão: 0.005)
- **Shadow Intensity**: Controla a escuridão das sombras (padrão: 0.7)
- **Shadow Map Resolution**: Resolução da textura de profundidade (padrão: 2048x2048)

### Vantagens desta Implementação:

1. **Sombras dinâmicas** que seguem o movimento do sol
2. **Sombras suaves** graças ao PCF
3. **Performance otimizada** com geometria simplificada na shadow map
4. **Fácil debug** com função para visualizar a shadow map

### Debug:

Para visualizar a shadow map no canto da tela, descomente esta linha em `igreja_componente.cpp`:
```cpp
sistema_sombras.desenhar_debug_shadow_map(10, 10, 256, 256);
```

### Requisitos:

- OpenGL 2.1+ com suporte a:
  - Frame Buffer Objects (GL_EXT_framebuffer_object)
  - GLSL 1.20+
  - Depth textures
  - Texture compare mode

### Troubleshooting:

Se o shadow mapping não funcionar:
1. O sistema detectará automaticamente e desabilitará as sombras
2. A aplicação continuará funcionando normalmente sem sombras
3. Verifique os logs de console para mensagens de erro dos shaders

## Melhorias Futuras Possíveis:

- **Cascaded Shadow Maps** para sombras de longa distância
- **Variance Shadow Maps** para sombras ainda mais suaves
- **Dynamic shadow map resolution** baseada na distância
- **Multiple light sources** com múltiplas shadow maps
