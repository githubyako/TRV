#include <iostream>
#include <fstream>
int main(int argc, char **argv) {
  std::string filename = argv[1];
  std::ifstream fichier (filename.c_str(), std::ios::in); // On ouvre le fichier
  if(fichier) // On regarde si le fichier s'est bien ouvert
  {
    unsigned int i=0;
    std::string ligne0, ligne1, ligne2, ligne3, ligne4,ligne5,temp;
    while (std::getline(fichier, temp)) // On récupère le contenu des lignes suivants (décrivant les différentes case différentes du terrain par défaut)
    {
      unsigned int linenbr = i%6;
      
      if(linenbr==0){
	  ligne0 = ligne0 + " " + temp;
      }else if(linenbr==1){
	ligne1 = ligne1 + " " + temp;
      }else if(linenbr==2){
	ligne2 = ligne2 + " " + temp;
      }else if(linenbr==3){
	ligne3 = ligne3 + " " + temp;
      }else if(linenbr==4){
	ligne4 = ligne4 + " " + temp;
      }else if(linenbr==5){
	ligne5 = ligne5 + " " + temp;
      }
      ++i;
    }
    std::cout << ligne0 << std::endl;
    std::cout << ligne1 << std::endl;
    std::cout << ligne2 << std::endl;
    std::cout << ligne3 << std::endl;
    std::cout << ligne4 << std::endl;
    std::cout << ligne5 << std::endl;
   
  }
  fichier.close(); // On ferme le fichier
}