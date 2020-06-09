LIBS=-lcsfml-graphics -lcsfml-window -lcsfml-system

_DEPS=CellularAutomata.h CA.h
DEPS=$(patsubst %,src/%,$(_DEPS))

CC=gcc
CFLAGS=-I src

ODIR=obj
_OBJ=main.o CellularAutomata.o CA.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

ca.out: $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm $(ODIR)/*.o ca.out

