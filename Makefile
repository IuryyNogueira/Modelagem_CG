# Makefile para o projeto Igreja 3D
CXX = g++
CXXFLAGS = -Wall -std=c++11 -O3
LIBS = -lglut -lGLU -lGL -lSOIL -lm
INCLUDES = -I/usr/include

SOURCES = igreja.cpp \
          constantes.cpp \
          inicializacao.cpp \
          parede.cpp \
          telhado.cpp \
          escada.cpp \
          arco.cpp \
          igreja_componente.cpp \
          controles.cpp \
          interior.cpp \
          texturas.cpp \
          iluminacao.cpp \
          skybox.cpp \
          sombras.cpp \
          feixes_luz.cpp \
          particulas.cpp \
          janela.cpp

OBJECTS = $(SOURCES:.cpp=.o)
TARGET = igreja

# Regra principal
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "✅ Compilação concluída!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Regra para limpar arquivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Arquivos limpos!"

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)

# Regra para instalar dependências
install-deps:
	@echo "📦 Instalando dependências..."
	sudo apt-get update
	sudo apt-get install -y freeglut3-dev libsoil-dev build-essential

.PHONY: all clean run install-deps
