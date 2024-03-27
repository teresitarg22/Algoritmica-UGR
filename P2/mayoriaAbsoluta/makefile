# Makefile para compilar el algoritmo de Mayoría Absoluta con Divide y Vencerás

# CXX = g++               # Compilador C++
# CXXFLAGS = -std=c++11    # Opciones del compilador

# # Nombre del programa de salida
# TARGET_DIVIDE_Y_VENCERAS = mayoriaAbsoluta_DyV

# # Lista de archivos fuente
# SRCS_DIVIDE_Y_VENCERAS = mayoriaAbsoluta_DyV.cpp

# # Genera los nombres de los archivos objeto a partir de los archivos fuente
# OBJS_DIVIDE_Y_VENCERAS = $(SRCS_DIVIDE_Y_VENCERAS:.cpp=.o)

# # Regla de compilación para generar el programa de salida
# $(TARGET_DIVIDE_Y_VENCERAS): $(OBJS_DIVIDE_Y_VENCERAS)
# 	$(CXX) $(CXXFLAGS) -o $(TARGET_DIVIDE_Y_VENCERAS) $(OBJS_DIVIDE_Y_VENCERAS)
# 	@echo "Ejemplo de ejecución de mayoriaAbsoluta_DyV: ./mayoriaAbsoluta_DyV mayoriaAbsoluta_DyV.txt 12345 1000 2000 3000"

# # Regla de compilación para generar archivos objeto
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Regla para limpiar los archivos objeto y el programa de salida
# clean:
# 	rm -f $(OBJS_DIVIDE_Y_VENCERAS) $(TARGET_DIVIDE_Y_VENCERAS)


# ----------------------------------------------------

CXX = g++               # Compilador C++
CXXFLAGS = -std=c++11    # Opciones del compilador

# Nombre del programa de salida
TARGET = mayoriaAbsoluta_basico

# Lista de archivos fuente
SRCS = mayoriaAbsoluta_basico.cpp

# Genera los nombres de los archivos objeto a partir de los archivos fuente
OBJS = $(SRCS:.cpp=.o)

# Regla de compilación para generar el programa de salida
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Ejemplo de ejecución: ./mayoriaAbsoluta_basico mayoriaAbsoluta_basico.txt 12345 1000 2000 3000"

# Regla de compilación para generar archivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos objeto y el programa de salida
clean:
	rm -f $(OBJS) $(TARGET)
