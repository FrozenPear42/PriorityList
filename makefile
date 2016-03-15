# ---------------------------
# Generic Makefile
# Author: Wojciech Gruszka
# Email:  wojciech@gruszka.eu
# ---------------------------
TARGET = PROI_1

CXX = g++

SRCDIR = src
INCDIR = inc
BINDIR = bin

CXXFLAGS = -Wall -I$(INCDIR) -std=c++11
LFLAGS = -Wall -std=c++11

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.hpp) $(wildcard $(INCDIR)/*.h)
#OBJECTS  := $(patsubst %.cpp, $(BINDIR)/%.o, $(SOURCES))
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

$(TARGET): $(OBJECTS)
	@$(CXX) -o $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(BINDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(BINDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	@rm -rf $(BINDIR)
	@rm -f	$(TARGET)

.PHONEY: files
files:
	@echo "src:\n"$(SOURCES)
	@echo "inc:\n"$(INCLUDES)
	@echo "obj:\n"$(OBJECTS)

.PHONEY: run
run: $(TARGET)
	@./$(TARGET)
