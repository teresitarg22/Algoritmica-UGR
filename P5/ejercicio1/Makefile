# Variables
SRCDIR := .
BINDIR := .
CPP_FILES := $(wildcard $(SRCDIR)/*.cpp)
EXECUTABLES := $(CPP_FILES:$(SRCDIR)/%.cpp=$(BINDIR)/%)

# Compiler
CXX := g++
CXXFLAGS := -std=c++11 -Wall

# Targets
all: $(EXECUTABLES)

$(BINDIR)/%: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR)
