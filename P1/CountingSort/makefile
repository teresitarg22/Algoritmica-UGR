CC = g++
CFLAGS = -std=c++11

# Nombre del ejecutable
TARGET = counting_sort

# Fuentes y objetos
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# Regla de construcción del ejecutable
$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^

# Regla de construcción de los objetos
%.o: %.cpp
    $(CC) $(CFLAGS) -c -o $@ $<

# Regla para eliminar los archivos generados
clean:
    rm -f $(OBJS) $(TARGET)