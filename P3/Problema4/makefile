# Makefile para compilar el algoritmo de Minima Transmision

CXX = g++               # Compilador C++
CXXFLAGS = -std=c++11    # Opciones del compilador

# Nombre del programa de salida
TARGET = minimaTransmision

# Lista de archivos fuente
SRCS = minimaTransmision.cpp

# Genera los nombres de los archivos objeto a partir de los archivos fuente
OBJS = $(SRCS:.cpp=.o)

# Regla de compilación para generar archivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar el programa de salida
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Regla para limpiar los archivos objeto y el programa de salida
clean:
	rm -f $(OBJS) $(TARGET)
