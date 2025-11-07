# 🚀 GUIA DE COMPILAÇÃO E EXECUÇÃO - IGREJA 3D

## ✅ PASSO 1: Instalar Dependências

```bash
chmod +x instalar_dependencias.sh
./instalar_dependencias.sh
```

Isso instalará:
- freeglut3-dev
- libglu1-mesa-dev  
- libsoil-dev
- build-essential

## ✅ PASSO 2: Verificar Texturas

```bash
chmod +x gerar_codigo_texturas.py
python3 gerar_codigo_texturas.py
```

Isso verifica se todas as texturas estão presentes na pasta `texturas/`.

## ✅ PASSO 3: Compilar o Projeto

```bash
make clean
make
```

Ou se der erro com SOIL, tente:
```bash
make clean
g++ -Wall -std=c++11 -O3 -o igreja *.cpp -lglut -lGLU -lGL -lSOIL -lm
```

## ✅ PASSO 4: Executar

```bash
./igreja
```

---

## 🎮 CONTROLES

- **WASD** - Movimentação
- **Mouse** - Olhar ao redor
- **E** - Abrir/fechar portas (quando próximo)
- **1-5** - Alternar luzes (funcionalidade futura)
- **ESC** - Sair

---

## 🔧 SOLUÇÃO DE PROBLEMAS

### Erro: "cannot find -lSOIL"

Execute:
```bash
sudo apt-get install libsoil-dev
```

Se ainda não funcionar:
```bash
cd /tmp
wget https://www.lonesock.net/files/soil.zip
unzip soil.zip
cd Simple\ OpenGL\ Image\ Library/projects/makefile
mkdir -p obj
make
sudo cp lib/libSOIL.a /usr/local/lib/
sudo cp src/SOIL.h /usr/local/include/
```

### Erro: "GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT undeclared"

Adicione no topo de texturas.cpp:
```cpp
#ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif
```

### Textura não carrega

Verifique:
1. O arquivo existe em `texturas/`
2. O nome está correto (case-sensitive)
3. O formato é suportado (JPG, PNG, BMP)

---

## 📊 ESTRUTURA DO PROJETO

```
Modelagem_CG/
├── igreja.cpp              # Main
├── constantes.cpp/h        # Constantes globais
├── inicializacao.cpp/h     # Inicialização OpenGL
├── texturas.cpp/h          # Sistema de texturas ✨ NOVO
├── iluminacao.cpp/h        # Sistema de iluminação ✨ NOVO
├── parede.cpp/h            # Paredes da igreja
├── telhado.cpp/h           # Telhado
├── escada.cpp/h            # Escadas de acesso
├── arco.cpp/h              # Arco da entrada
├── interior.cpp/h          # Mobília interna
├── controles.cpp/h         # Controles e câmera
├── igreja_componente.cpp   # Montagem final
├── texturas/               # Pasta de texturas
│   ├── parede_externa.jpg.png
│   ├── piso_marmore.jpg
│   ├── madeira_escura.jpg
│   └── ... (todas as texturas)
├── Makefile               # Compilação
└── README_COMPILACAO.md   # Este arquivo
```

---

## 🎨 NOVAS FUNCIONALIDADES IMPLEMENTADAS

### ✅ Sistema de Texturas
- Carregamento automático de todas as texturas
- Suporte a múltiplos formatos (JPG, PNG, BMP)
- Mipmapping para qualidade à distância
- Anisotropic filtering (RTX 4050 suporta!)

### ✅ Sistema de Iluminação Avançada
- **5 fontes de luz**:
  1. Sol (GL_LIGHT0) - Luz direcional dinâmica
  2. Luz do Altar (GL_LIGHT1) - Spotlight
  3. Luz Lateral Esquerda (GL_LIGHT2)
  4. Luz Lateral Direita (GL_LIGHT3)
  5. Luz da Entrada (GL_LIGHT4)

- **Materiais configuráveis**:
  - Madeira (bancos, portas)
  - Mármore (piso, altar)
  - Metal (castiçais)
  - Tecido (decorações)
  - Parede (reboco)

### ✅ Melhorias Visuais
- Antialiasing habilitado
- Blending para transparências
- Depth test otimizado
- Perspective correction

---

## 🔜 PRÓXIMAS IMPLEMENTAÇÕES

1. **Aplicar texturas nos objetos** (próximo passo)
2. **Iluminação global** (radiosity fake)
3. **Partículas** (chamas de velas)
4. **Skybox** (céu realista)
5. **Vegetação** (árvores ao redor)
6. **Animações** (pessoas, pássaros)

---

## 📝 LOGS DE COMPILAÇÃO

Se der erro, envie a saída completa de:
```bash
make clean && make 2>&1 | tee compile.log
```

E o conteúdo de `compile.log`.
