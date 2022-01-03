IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR= ./obj
LDIR =../lib

LIBS= -lopengl32 -lgdi32 -lmingw32 -L$(LDIR) -lglfw3

_DEPS = glad/glad.h glfw/glfw.h shader.h model.h memory.h HandmadeMath.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o glad.o shader.o model.o memory.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

../bin/Game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 