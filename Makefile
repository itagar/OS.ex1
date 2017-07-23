CXX= g++
CXXFLAGS= -c -Wall -O0 -std=c++11
CODEFILES= ex1.tar osm.cpp emptyFunction.h Makefile README
LIBOBJECTS= osm.o


# Default
default: osm


# Executables
osm: osm.o
	ar rcs libosm.a $(LIBOBJECTS)
	-rm -vf *.o


# Object Files
osm.o: osm.cpp osm.h emptyFunction.h
	$(CXX) $(CXXFLAGS) osm.cpp -o osm.o


# tar
tar:
	tar -cvf $(CODEFILES)


# Other Targets
clean:
	-rm -vf *.o *.a *.tar


# Valgrind
Valgrind: osm
	$(CXX) -g -Wall -std=c++11 simpletest.cpp -L. -losm -o Valgrind 
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes ./Valgrind
	-rm -vf *.o *.a Valgrind	
	
