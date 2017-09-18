IDIR =include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=obj
LDIR =lib

LIBS=-lm -lev

_DEPS = StaticWebServer.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Buffer.o StaticWebInstance.o StaticWebServer.o main.o HTTPRequestHeader.o HTTPResponseHeader.o SocketBufferWriteRequest.o SocketWriteRequest.o SocketFileWriteRequest.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ main 
