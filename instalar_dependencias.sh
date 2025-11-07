#!/bin/bash

echo "================================================"
echo "  INSTALANDO DEPENDÊNCIAS - IGREJA 3D"
echo "================================================"

# Atualizar repositórios
echo "🔄 Atualizando repositórios..."
sudo apt-get update

# Instalar bibliotecas necessárias
echo "📦 Instalando bibliotecas OpenGL..."
sudo apt-get install -y freeglut3-dev \
                        libglu1-mesa-dev \
                        mesa-common-dev \
                        libsoil-dev \
                        build-essential

# Verificar instalação
echo ""
echo "✅ Verificando instalação..."

if pkg-config --exists glut; then
    echo "✓ GLUT instalado"
else
    echo "✗ GLUT NÃO instalado"
fi

if pkg-config --exists glu; then
    echo "✓ GLU instalado"
else
    echo "✗ GLU NÃO instalado"
fi

if [ -f "/usr/include/SOIL/SOIL.h" ]; then
    echo "✓ SOIL instalado"
else
    echo "✗ SOIL NÃO instalado"
    echo "⚠️  Tentando método alternativo..."
    cd /tmp
    wget https://www.lonesock.net/files/soil.zip
    unzip soil.zip
    cd Simple\ OpenGL\ Image\ Library/projects/makefile
    mkdir -p obj
    make
    sudo cp lib/libSOIL.a /usr/local/lib/
    sudo cp src/SOIL.h /usr/local/include/
    cd ~
fi

echo ""
echo "================================================"
echo "  ✅ INSTALAÇÃO CONCLUÍDA!"
echo "================================================"
