CC  	= gcc
CCLIBS	= -lGL -lGLU -lglut
CCFLAGS	= -Wall -Wextra
PROGRAM	= rubik
OBJ 	= 		 \
	main.o  	 \
	callbacks.o	 \
	draw.o  	 \
	matrices.o	 \
	timers.o	 \
	init.o  	 \
	moves.o		 \
	rand.o  	 \
	gui.o   	 \
	textures.o
VPATH 	= src


%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CCLIBS) $(CCFLAGS)


.PHONY: clean

clean:
	rm -f src/*.swp *.swp *~ src/*~ *.o

