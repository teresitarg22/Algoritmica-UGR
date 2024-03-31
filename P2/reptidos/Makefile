CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET_BASIC = repetidos_basico
TARGET_DYV = repetidos_dyv

SRCS_BASIC = repetidos_basico.cpp
SRCS_DYV = repetidos_dyv.cpp

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
