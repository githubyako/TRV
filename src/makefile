#authors: Corentin Talarmain, Nicolas Roux, Théo Voillemin
CPP = *.cpp

FLAGS = -O2 -Wall -std=c++11

all: trv.exe
	@echo "-> Execute trv.exe"
	./trv.exe

trv.exe:
	@echo "-> Compiling $@"
	g++ $(CPP) $(FLAGS) $$(pkg-config --cflags --libs libxml++-2.6) -o trv.exe
	
clean:
	@echo "-> Clean project"
	rm -rf *.exe
