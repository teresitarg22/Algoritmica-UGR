# Makefile para compilar el algoritmo de Mayoría Absoluta con Divide y Vencerás

CXX = g++               # Compilador C++
CXXFLAGS = -std=c++11    # Opciones del compilador

# Nombre del programa de salida
TARGET = mayoriaAbsoluta

# Lista de archivos fuente
SRCS = mayoriaAbsoluta.cpp

# Genera los nombres de los archivos objeto a partir de los archivos fuente
OBJS = $(SRCS:.cpp=.o)

# Regla de compilación para generar el programa de salida
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Ejemplo de ejecución: ./mayoriaAbsoluta mayoriaAbsoluta.txt 12345 1000 2000 3000"

# Regla de compilación para generar archivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos objeto y el programa de salida
clean:
	rm -f $(OBJS) $(TARGET)
