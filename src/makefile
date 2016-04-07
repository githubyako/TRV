#authors: Corentin Talarmain, Nicolas Roux, Théo Voillemin
CPP = *.cpp

FLAGS = -O2 -Wall -std=c++11 -I/usr/include/libxml2 -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/libxml++-2.6 -I/usr/lib/libxml++-2.6/include  -lxml++-2.6 -lxml2 -lglibmm-2.4 -lgobject-2.0 -lsigc-2.0 -lglib-2.0

all: trv.exe


trv.exe:
	@echo "-> Compiling $@"
	g++ $(CPP) $(FLAGS) -o trv.exe
	
clean:
	@echo "-> Clean project"
	rm -rf *.exe
