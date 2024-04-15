CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = costeAsfaltado.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = costeAsfaltado

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)