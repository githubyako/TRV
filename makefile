#authors: Corentin Talarmain, Nicolas Roux, Théo Voillemin
CPP = *.cpp

FLAGS = -O2 -Wall -std=c++11

all: trv.exe
	@echo "-> Execute roux_nicolas.exe"
	./roux_nicolas.exe


trv.exe:
	@echo "-> Compiling $@"
	g++ main.cpp $(CPP) $(FLAGS) -o trv.exe
	
clean:
	@echo "-> Clean project"
	rm -rf *.exe
