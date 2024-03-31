CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET_BASIC = organizacionCampeonato_Basico
TARGET_DYV = organizacionCampeonato_DyV

SRCS_BASIC = organizacionCampeonato_Basico.cpp
SRCS_DYV = organizacionCampeonato_DyV.cpp

OBJS_BASIC = $(SRCS_BASIC:.cpp=.o)
OBJS_DYV = $(SRCS_DYV:.cpp=.o)

all: $(TARGET_BASIC) $(TARGET_DYV)

$(TARGET_BASIC): $(OBJS_BASIC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_DYV): $(OBJS_DYV)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET_BASIC) $(TARGET_DYV) $(OBJS_BASIC) $(OBJS_DYV)
