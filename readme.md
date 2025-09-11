# Igreja 3D - Projeto OpenGL C++

Este projeto implementa uma igreja em 3D usando OpenGL e C++. O código foi modularizado para facilitar a colaboração e manutenção.

## Estrutura do Projeto

O projeto foi organizado nos seguintes módulos:

- **constantes.h/cpp** - Constantes globais e variáveis de controle da câmera
- **inicializacao.h/cpp** - Configuração inicial do OpenGL
- **parede.h/cpp** - Renderização das paredes da igreja
- **telhado.h/cpp** - Renderização do telhado e telhas
- **escada.h/cpp** - Renderização da escada de entrada
- **arco.h/cpp** - Renderização do arco frontal
- **igreja_componente.cpp** - Função principal que combina todos os componentes
- **controles.h/cpp** - Controles de câmera e interface
- **igreja.cpp** - Arquivo principal com função main

## Compilação

### Opção 1: Usando Makefile (Recomendado)
```bash
make
```

Para limpar arquivos compilados:
```bash
make clean
```

Para recompilar tudo:
```bash
make rebuild
```

### Opção 2: Compilação manual
```bash
g++ -Wall -std=c++11 igreja.cpp constantes.cpp inicializacao.cpp parede.cpp telhado.cpp escada.cpp arco.cpp igreja_componente.cpp controles.cpp -o igreja -lglut -lGLU -lGL
```

## Execução
```bash
./igreja
```

## Controles
- **W/S** - Rotação vertical da câmera
- **A/D** - Rotação horizontal da câmera
- **Q/E** - Zoom in/out
- **ESC** - Sair do programa

## Contribuição

Cada desenvolvedor pode trabalhar nos diferentes módulos independentemente:
- **Paredes**: Modificar `parede.cpp` para adicionar janelas, portas, detalhes
- **Telhado**: Modificar `telhado.cpp` para diferentes estilos de telhado
- **Escada**: Modificar `escada.cpp` para diferentes tipos de escada
- **Arco**: Modificar `arco.cpp` para diferentes estilos de entrada
- **Controles**: Modificar `controles.cpp` para adicionar novos controles
- **Iluminação**: Modificar `inicializacao.cpp` para diferentes configurações de luz
