OBJECTS=alphabeta.o board.o eval-simple.o four.o minmax.o

four : $(OBJECTS)
	cc -o four $(OBJECTS) $(CFLAGS) $(LDFLAGS)

${OBJECTS}: four.h

clean : 
	rm four $(OBJECTS)