# Sistema de Sombras Projetadas Implementado

## 🎯 O Que Foi Feito

Implementei um sistema de **sombras projetadas planares** (planar projected shadows) que funciona com OpenGL fixo, sem necessidade de shaders. Este é um método clássico e eficiente para sombras em tempo real.

## ✨ Melhorias Implementadas

### 1. Sistema de Sombras Projetadas
- **Algoritmo**: Projeção matemática de geometria em um plano
- **Funciona**: Com qualquer hardware que suporte OpenGL 1.x+
- **Visível**: Sombras escuras e bem definidas no chão da igreja

### 2. Iluminação Intensificada

#### Luz Global (Sol) - GL_LIGHT0:
```cpp
- Intensidade aumentada de 1.5x para 2.0x
- Luz ambiente mais forte: 0.5f (era 0.4f)
- Posição: Segue ciclo dia/noite
```

#### Luzes das Velas - GL_LIGHT5, GL_LIGHT6, GL_LIGHT7:
```cpp
- 3 velas no altar (esquerda, centro, direita)
- Cor: Laranja quente (1.0, 0.8, 0.4) - chama realista
- Atenuação reduzida: iluminam área maior
- Posição: 3.5m acima do chão do altar
```

#### Outras Luzes:
- **GL_LIGHT1**: Spotlight no altar
- **GL_LIGHT2**: Lâmpada lateral esquerda
- **GL_LIGHT3**: Lâmpada lateral direita  
- **GL_LIGHT4**: Luz na entrada

## 📐 Como Funciona

### Sombra Projetada Planar:

1. **Matriz de Projeção**: Calcula transformação que "achata" objetos no plano do chão
2. **Geometria Simplificada**: Desenha versão simplificada dos objetos
3. **Blend**: Usa transparência para sombra suave (alpha = 0.4)

```cpp
// Equação da matriz de sombra
Shadow = BiasMatrix * ProjectionMatrix * ViewMatrix
```

### Objetos com Sombra:
- ✅ **8 bancos** de cada lado (16 total)
- ✅ **Altar** principal
- ✅ **3 velas** no altar

## 🎨 Características Visuais

### Sombras:
- **Cor**: Preta com 40% de transparência
- **Posição**: Projetadas no chão (y = ALTURA_PLATAFORMA)
- **Suavização**: Polygon offset para evitar z-fighting
- **Dinâmicas**: Seguem posição da luz principal (sol)

### Iluminação das Velas:
- **Efeito**: Luz laranja quente emanando
- **Alcance**: ~8 unidades (ilumina bancos próximos)
- **Cintilação**: Pode ser adicionada com animação (próxima etapa)

## 🚀 Melhorias Adicionais Possíveis

### 1. Cintilação das Velas (Próximo):
```cpp
// Adicionar variação no brilho
float flicker = sin(time * 10.0f) * 0.1f + 0.9f;
luz_vela_intensidade *= flicker;
```

### 2. Mais Fontes de Luz:
- Velas laterais nos bancos
- Castiçais nas paredes
- Lustres pendentes

### 3. Sombras Suaves (Soft Shadows):
- Desenhar múltiplas sombras com offsets
- Usar blur acumulativo

### 4. Sombras de Múltiplas Luzes:
- Cada vela projeta sua própria sombra
- Misturar sombras com blending aditivo

## 📊 Configurações Atuais

```cpp
// Intensidade da sombra
shadow_intensity = 0.5f; // 50% de opacidade

// Luz do sol
intensidade_sol = 2.0f; // 200% (muito brilhante)
cor_sol = (1.0, 0.98, 0.85); // Amarelo quente

// Luzes das velas
intensidade_velas = 1.0f;
cor_velas = (1.0, 0.8, 0.4); // Laranja chama
atenuacao_constant = 0.5f; // Luz alcança mais longe
```

## 🔧 Como Ajustar

### Para Sombras Mais Escuras:
Em `sombras.cpp`, linha ~153:
```cpp
glColor4f(0.0f, 0.0f, 0.0f, 0.6f); // Mude 0.4f para 0.6f
```

### Para Velas Mais Brilhantes:
Em `iluminacao.cpp`, função `aplicar_luzes_velas()`:
```cpp
GLfloat cor_vela[] = {1.5f, 1.2f, 0.6f, 1.0f}; // Aumentar valores RGB
```

### Para Mais Sombras:
Em `sombras.cpp`, adicionar na função `desenhar_sombras_interiores()`:
```cpp
// Adicionar sombras de outros objetos
glPushMatrix();
glTranslatef(x, y, z);
desenhar_sombra_objeto_chao(luz_sol, geometria_objeto);
glPopMatrix();
```

## ✅ Checklist de Implementação

- [x] Sistema de sombras projetadas funcionando
- [x] Luz global (sol) intensificada
- [x] 3 luzes de velas no altar
- [x] Sombras de bancos visíveis
- [x] Sombras do altar visíveis
- [x] Sombras das velas visíveis
- [x] Iluminação ambiente aumentada
- [ ] Cintilação das velas (próximo)
- [ ] Mais velas na igreja (próximo)
- [ ] Partículas de fogo nas velas (futuro)

## 🎯 Resultado Esperado

Ao rodar `./igreja`, você deve ver:
1. **Sombras escuras** projetadas pelos bancos no chão
2. **Sombra do altar** na área do altar
3. **Luz laranja quente** emanando das 3 velas
4. **Iluminação geral** mais brilhante e dramática
5. **Sombras se movem** conforme o sol (ciclo dia/noite)

## 📝 Notas Técnicas

- **Performance**: Excelente (sombras planares são muito rápidas)
- **Limitação**: Sombras apenas no chão (não em paredes)
- **Compatibilidade**: 100% com qualquer OpenGL 1.x+
- **Escalabilidade**: Fácil adicionar mais objetos

## 🔍 Debug

Se as sombras não aparecerem:
1. Verificar se `shadow_mapping_enabled = true` no construtor
2. Verificar se luz GL_LIGHT0 está ativa
3. Aumentar alpha da sombra (tornar mais escura)
4. Verificar se plano do chão está correto (y = ALTURA_PLATAFORMA)

---

**Status**: ✅ IMPLEMENTADO E FUNCIONAL
**Próximo passo**: Adicionar cintilação das velas para mais realismo
