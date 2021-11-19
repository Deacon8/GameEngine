IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR= ./src

LIBS= -lopengl32 -L./libs -lglfw3

_DEPS = stuff.h morestuff.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Test.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/Test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 