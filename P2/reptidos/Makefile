CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

REPETIDOS_BASIC = repetidos_basico
REPETIDOS_DYV = repetidos_dyv
TUERCAS = tuercasYTornillos
MAYORIA = mayoriaAbsoluta
CAMPEONATO_BASIC = organizacionCampeonato_Basico
CAMPEONATO_DYV = organizacionCampeonato_DyV
PRODUCTO_BASIC = productoTresElementos_Basico
PRODUCTO_DYV = productoTresElementos_DyV


SRCS_REP_BASIC = repetidos_basico.cpp
SRCS_REP_DYV = repetidos_dyv.cpp
SRCS_TUERCAS = tuercasYTornillos.cpp
SRCS_CAMP_BASIC = organizacionCampeonato_Basico.cpp
SRCS_CAMP_DYV = organizacionCampeonato_DyV.cpp
SRCS_MAYORIA = mayoriaAbsoluta.cpp
SRCS_PRODUC_BASIC = producto_tres_elementos_basico.cpp
SRCS_PRODUC_DYV = producto_tres_elementos_dyv.cpp

OBJS_REP_BASIC = $(SRCS_REP_BASIC:.cpp=.o)
OBJS_REP_DYV = $(SRCS_REP_DYV:.cpp=.o)
OBJS_TUERCAS = $(SRCS_TUERCAS:.cpp=.o)
OBJS_CAMP_BASIC = $(SRCS_CAMP_BASIC:.cpp=.o)
OBJS_CAMP_DYV = $(SRCS_CAMP_DYV:.cpp=.o)
OBJS_MAYORIA = $(SRCS_MAYORIA:.cpp=.o)
OBJS_PRODUC_BASIC = $(SRCS_PRODUC_BASIC:.cpp=.o)
OBJS_PRODUC_DYV = $(SRCS_PRODUC_DYV:.cpp=.o)

all: $(REPETIDOS_BASIC) $(REPETIDOS_DYV) $(TUERCAS) $(MAYORIA) $(CAMPEONATO_BASIC) $(CAMPEONATO_DYV) $(PRODUCTO_BASIC) $(PRODUCTO_DYV)

$(REPETIDOS_BASIC): $(OBJS_REP_BASIC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(REPETIDOS_DYV): $(OBJS_REP_DYV)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TUERCAS): $(OBJS_TUERCAS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(MAYORIA): $(OBJS_MAYORIA)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(CAMPEONATO_BASIC): $(OBJS_CAMP_BASIC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(CAMPEONATO_DYV): $(OBJS_CAMP_DYV)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(PRODUCTO_BASIC): $(OBJS_PRODUC_BASIC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(PRODUCTO_DYV): $(OBJS_PRODUC_DYV)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET_BASIC) $(TARGET_DYV) $(OBJS_BASIC) $(OBJS_DYV)
