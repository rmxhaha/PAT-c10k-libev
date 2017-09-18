IDIR =include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=obj
LDIR =lib

LIBS=-lm -lev

_DEPS = EchoServer.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Buffer.o EchoInstance.o EchoServer.o main.o HTTPRequestHeader.o HTTPResponseHeader.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
