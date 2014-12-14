objects = main.o

bezier : $(objects)
	g++ -o bezier $(objects)

main.o : Bezier.h

clean : 
	rm bezier $(objects)
