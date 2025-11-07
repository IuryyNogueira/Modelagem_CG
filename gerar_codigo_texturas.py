#!/usr/bin/env python3
import os
import glob

PASTA_TEXTURAS = "texturas"

# Mapeamento de texturas esperadas
texturas_esperadas = {
    "parede_externa": "Parede externa da igreja",
    "parede_interna": "Parede interna",
    "piso_marmore": "Piso de mármore",
    "madeira_escura": "Madeira escura (bancos)",
    "madeira_porta": "Madeira das portas",
    "concreto": "Concreto (escadas/plataforma)",
    "telha_colonial": "Telhas do telhado",
    "vitral_colorido": "Vitral das janelas",
    "grama": "Grama do terreno",
    "pedra_caminho": "Pedras do caminho",
    "metal_bronze": "Metal bronze (castiçais)",
    "tecido_vermelho": "Tecido vermelho"
}

def encontrar_textura(nome_base):
    """Procura por arquivo com qualquer extensão de imagem"""
    # Extensões comuns de imagem
    extensoes = ['jpg', 'jpeg', 'png', 'bmp', 'tga', 'tif', 'tiff']
    
    # Verificar variações no nome
    for arquivo in os.listdir(PASTA_TEXTURAS):
        if os.path.isfile(os.path.join(PASTA_TEXTURAS, arquivo)):
            nome_sem_ext = os.path.splitext(arquivo)[0].lower()
            if nome_sem_ext == nome_base.lower():
                return arquivo
    
    return None

print("=" * 60)
print("  GERADOR AUTOMÁTICO DE CÓDIGO - TEXTURAS")
print("=" * 60)
print()

# Detectar texturas
texturas_encontradas = {}
texturas_faltando = []

for nome, descricao in texturas_esperadas.items():
    arquivo = encontrar_textura(nome)
    if arquivo:
        texturas_encontradas[nome] = arquivo
        print(f"✓ {nome}: {arquivo}")
    else:
        texturas_faltando.append(nome)
        print(f"✗ {nome}: NÃO ENCONTRADO")

print()
print("=" * 60)

if texturas_faltando:
    print(f"⚠️  FALTAM {len(texturas_faltando)} TEXTURAS:")
    for t in texturas_faltando:
        print(f"   - {t}")
    print()

print(f"✅ {len(texturas_encontradas)}/{len(texturas_esperadas)} texturas encontradas")
print()
print("Código C++ já está correto no texturas.cpp!")
print()
print("=" * 60)
print("PRÓXIMOS PASSOS:")
print("1. Execute: chmod +x instalar_dependencias.sh")
print("2. Execute: ./instalar_dependencias.sh")
print("3. Compile: make clean && make")
print("4. Execute: ./igreja")
print("=" * 60)