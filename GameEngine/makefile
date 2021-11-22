IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR= ./src

LIBS= -lopengl32 -lgdi32 -lmingw32 -L./libs -lglfw3

_DEPS = glad/glad.h glfw/glfw.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.c glad.c 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/Game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 