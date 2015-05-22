CC = gcc
OBJ =merry-go-round.o LoadShader.o Matrix.o object.o
CFLAGS = -g -Wall -Wextra

LDLIBS=-lm -lglut -lGLEW -lGL

merry-go-around: $(OBJ)
	 $(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

clean:
	rm -f *.o merry-go-around 
.PHONY: all clean
