CXX = g++  # El compilador que utilizarás (en este caso, g++)
CXXFLAGS = -std=c++11 -Wall -Wextra  # Opciones para el compilador

# Nombre del ejecutable final
TARGET = parejas

# Archivos de código fuente y objeto
SRCS = parejas.cpp
OBJS = $(SRCS:.cpp=.o)

# Regla para compilar los archivos objeto
$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar el programa final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f $(OBJS) $(TARGET)

# Establece la regla "all" para compilar todo
all: $(TARGET)

# Por defecto, el objetivo "all" es el predeterminado
.DEFAULT_GOAL := all

# Indica a make que los siguientes nombres no corresponden a archivos
.PHONY: all clean