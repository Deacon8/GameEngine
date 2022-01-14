IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR) -g
OUTPUT=bin/Game

SDIR=./src
#Should be ./obj but it works
ODIR=./src

LIBS= -lopengl32 -lgdi32 -lmingw32 -L./libs -lglfw3

_DEPS = glad/glad.h glfw/glfw.h shader.h model.h texture.h memory.h camera.h transform.h renderer.h entity.h loader.h stb_image.h utilities.h HandmadeMath.h engine.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o glad.o shader.o model.o memory.o camera.o texture.o transform.o renderer.o entity.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del .\src\*.o
