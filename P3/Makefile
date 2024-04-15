CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS =
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

TARGET = $(BIN_DIR)/eficiencias
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run:
	@echo "Ejemplo de uso: ./bin/tuercas tiempos.txt 12345 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000"


clean:
	rm -f $(TARGET) $(OBJECTS)
