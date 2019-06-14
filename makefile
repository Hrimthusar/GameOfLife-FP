CXX  		= g++
CXXLIBS 	= -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS	= -g -std=c++14 -Wall -Wextra -I./libs/range-v3/include

SOURCEDIR 	= src
BUILDDIR 	= build

PROGRAM	= game_of_life
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

$(BUILDDIR)/$(PROGRAM): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $^ -o $@ $(CXXLIBS)

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	@echo "Compiling: $@"
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: all dir clean run printObj

all:
	dir $(BUILDDIR)/$(PROGRAM)

dir:
	mkdir -p $(BUILDDIR)

clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(PROGRAM)

run:
	./$(BUILDDIR)/$(PROGRAM)

