IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)
OUTPUT=bin/Game

SDIR=./src
#Should be ./obj but it works
ODIR=./src

LIBS= -lopengl32 -lgdi32 -lmingw32 -L./libs -lglfw3

_DEPS = glad/glad.h glfw/glfw.h shader.h model.h memory.h camera.h HandmadeMath.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o glad.o shader.o model.o memory.o camera.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~  
