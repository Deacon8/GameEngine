IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR= ./src

LIBS= -lopengl32 -lgdi32 -L./libs -lglfw3

_DEPS = KHR/khrplatform.h glfw/glfw3.h glad/glad.h
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