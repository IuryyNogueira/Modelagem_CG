# Guia para Colaboradores - Igreja 3D

## Como Contribuir

Este projeto foi modularizado para facilitar a colaboração entre múltiplos desenvolvedores. Cada componente da igreja está em um arquivo separado.

## Estrutura Modular

### 1. Constantes (`constantes.h/cpp`)
- Contém todas as medidas principais da igreja
- Variáveis de controle da câmera
- **Colaboradores podem**: Ajustar dimensões, adicionar novas constantes

### 2. Paredes (`parede.h/cpp`)
- Renderiza as 4 paredes da igreja
- **Colaboradores podem**: 
  - Adicionar janelas
  - Adicionar portas
  - Criar texturas nas paredes
  - Adicionar detalhes arquitetônicos

### 3. Telhado (`telhado.h/cpp`)
- Renderiza o telhado em formato triangular
- **Colaboradores podem**:
  - Mudar o estilo do telhado
  - Adicionar chaminé
  - Criar diferentes materiais de telha
  - Adicionar calhas

### 4. Escada (`escada.h/cpp`)
- Renderiza a escada de entrada
- **Colaboradores podem**:
  - Mudar o número de degraus
  - Adicionar corrimão
  - Mudar o material
  - Criar escadas curvas

### 5. Arco (`arco.h/cpp`)
- Renderiza o arco de entrada
- **Colaboradores podem**:
  - Mudar o estilo do arco (gótico, românico, etc.)
  - Adicionar ornamentações
  - Criar arcos múltiplos
  - Adicionar colunas

### 6. Controles (`controles.h/cpp`)
- Gerencia entrada do usuário e visualização
- **Colaboradores podem**:
  - Adicionar novos controles
  - Implementar animações
  - Adicionar modos de visualização
  - Implementar câmera automática

### 7. Inicialização (`inicializacao.h/cpp`)
- Configura OpenGL e iluminação
- **Colaboradores podem**:
  - Ajustar iluminação
  - Adicionar múltiplas luzes
  - Configurar materiais
  - Adicionar sombras

## Fluxo de Trabalho Recomendado

1. **Clone o repositório**
2. **Escolha um módulo** para trabalhar
3. **Compile e teste** antes de fazer mudanças: `make`
4. **Faça suas modificações** no módulo específico
5. **Recompile**: `make rebuild`
6. **Teste** se o programa ainda funciona corretamente
7. **Commit e push** suas mudanças

## Convenções de Código

- Use nomes descritivos para funções e variáveis
- Adicione comentários para código complexo
- Mantenha a indentação consistente (4 espaços)
- Teste sempre antes de fazer commit

## Exemplo de Extensão

Para adicionar uma janela na parede frontal:

```cpp
// Em parede.cpp, na função desenha_parede()
void desenha_janela_frontal() {
    glColor3f(0.0f, 0.0f, 0.8f); // Azul para vidro
    glBegin(GL_QUADS);
        glVertex3f(-5.0f, 10.0f, 0.1f);
        glVertex3f( 5.0f, 10.0f, 0.1f);
        glVertex3f( 5.0f, 15.0f, 0.1f);
        glVertex3f(-5.0f, 15.0f, 0.1f);
    glEnd();
}
```

## Compilação

Sempre use o Makefile:
- `make` - Compila o projeto
- `make clean` - Remove arquivos compilados
- `make rebuild` - Limpa e recompila tudo
