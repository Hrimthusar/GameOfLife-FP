CC  	= g++
CCLIBS = -lsfml-graphics -lsfml-window -lsfml-system
CCFLAGS	= -Wall -Wextra

SOURCEDIR = src
BUILDDIR = build

PROGRAM	= game_of_life
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

$(BUILDDIR)/$(PROGRAM): $(OBJECTS)
	@echo "Linking: $@"
	$(CC) $^ -o $@ $(CCLIBS)

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	@echo "Compiling: $@"
	$(CC) -c -o $@ $< $(CCFLAGS)

.PHONY: all dir clean run printObj

all:
	dir $(BUILDDIR)/$(PROGRAM)

dir:
	mkdir -p $(BUILDDIR)

clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(PROGRAM)

run:
	./$(BUILDDIR)/$(PROGRAM)

