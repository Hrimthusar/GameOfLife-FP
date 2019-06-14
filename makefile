CC  	= gcc
CCLIBS = -lsfml-graphics -lsfml-window -lsfml-system
CCFLAGS	= -Wall -Wextra
PROGRAM	= game_of_life
OBJ 	= 		 \
	main.o
VPATH 	= src

%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CCLIBS) $(CCFLAGS)

.PHONY: clean

clean:
	rm -f src/*.swp *.swp *~ src/*~ *.o

run:
	./game_of_life

