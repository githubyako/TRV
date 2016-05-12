#authors: Corentin Talarmain, Nicolas Roux, Théo Voillemin
CPP = *.cpp

FLAGS = -O3 -Wall -std=c++11 $(shell pkg-config --cflags --libs libxml++-2.6)

all: 
	g++ $(CPP) $(FLAGS) -o trv.exe

clean:
	@echo "-> Clean project"
	rm -rf *.exe
