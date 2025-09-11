# Makefile para o projeto Igreja 3D
CXX = g++
CXXFLAGS = -Wall -std=c++11
LIBS = -lglut -lGLU -lGL
TARGET = igreja
SOURCES = igreja.cpp constantes.cpp inicializacao.cpp parede.cpp telhado.cpp escada.cpp arco.cpp igreja_componente.cpp controles.cpp

# Regra principal
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

# Regra para limpar arquivos compilados
clean:
	rm -f $(TARGET)

# Regra para recompilar tudo
rebuild: clean $(TARGET)

.PHONY: clean rebuild
