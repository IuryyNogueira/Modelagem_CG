# Guia para Colaboradores - Igreja 3D

## Estrutura do Projeto

### 1. `constantes.h/cpp`
- Dimensões da igreja baseadas na planta baixa
- Variáveis de controle da câmera e movimento
- Configurações de velocidade e sensibilidade

### 2. `parede.h/cpp`
- 4 paredes da igreja com espessura
- Plataforma elevada com rampas
- Nicho decorativo laranja na frente
- Vão de entrada proporcional

### 3. `telhado.h/cpp`
- Telhado colonial com inclinação 30%
- Telhas vermelhas
- Empenas triangulares

### 4. `escada.h/cpp`
- Escada central com 6 degraus
- Base em formato T
- Rampas laterais para acessibilidade

### 5. `arco.h/cpp`
- Arco parabólico moderno
- Cruz no topo
- Estrutura branca que vai até o chão

### 6. `interior.h/cpp`
- Altar elevado com parede terracota e cruz
- Fileiras de bancos de madeira
- Púlpito lateral direito
- Piso de concreto claro
- Decorações douradas

### 7. `controles.h/cpp`
- Movimento WASD primeira pessoa
- Rotação com mouse
- Detecção de colisão
- Ajuste automático de altura

### 8. `inicializacao.h/cpp`
- Configuração OpenGL
- Iluminação natural (sol)
- Céu azul claro
- Material e luzes

### 9. Arquivos de Versão
- `interior_old.cpp` - versão anterior do interior
- `interior_novo.cpp` - versão alternativa

## Como Contribuir

1. Clone o repositório
2. Escolha um módulo para modificar
3. Compile: `make`
4. Teste suas mudanças
5. Commit e push

## Compilação

```bash
make          # Compila
make clean    # Limpa
make rebuild  # Limpa e recompila
```

## Convenções

- Funções: `snake_case`
- Constantes: `UPPER_CASE`
- Sempre use `glPushMatrix/glPopMatrix`
- Teste antes de commit
