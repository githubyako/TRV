#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>
#include "str_exception.h"
#include "map.h"
#include "algogen.h"

#include <libxml++/libxml++.h>

// Classe représentant le controlleur utile à la communication entre le jeu et la recherche de pathfinding 
// Classe réalisée avec le design pattern "singleton"
class Controller{
private:
  static Controller * s_controller; // On ne souhaite qu'il n'y ai qu'une et une seule instance de Controller 
  Map* map; // La map associé au controlleur, c'est sur celle-ci que se déroule le jeu et le pathfinding
  Algogen* m_algg;
  // Constructeurs :
  Controller();
  Controller(Controller const & _controller);
  
  
public:

  // Destructeur
  ~Controller();
  
  // On ne veut pas donner accès au constructeur de Controller car on ne souhaite qu'une instance de Controller à la fois
  static Controller * create();
  static void delete_controller();
  
  // Fonction de création d'un agent, créé un instance de la classe Agent lorsque le jeu génère une nouvelle unité
  void creer_agent(int x, int y, const std::string type, int id);
  
  // Fonction de suppression d'agent, supprime l'instance d'Agent à l'identificateur id
  void supprimer_agent(int id);
  
  // Fonction de déplacement d'agent, déplace l'Agent d'identificateur id à la case de coordonnées x,y
  void deplacement_agent(int id, int x, int y);
  
  // Fonction permettant la création ou la suppression d'un obstacle à la case de coordonnées x,y
  void setObstacle(int x, int y, bool obs);
  
  // Fonction demandant une recherche de chemin par pathfinding Dijkstra à l'Agent d'identificateur id à la case de coordonnées x,y
  void demande_chemin(int id, int x, int y);
  
  // Fonction demandant une recherche de chemin par pathfinding A* à l'Agent d'identificateur id à la case de coordonnées x,y
  void demande_chemin_A_star(int id, int x, int y);
  
  void create_algogen();
  void delete_algogen();
  
  // Fonction demandant une recherche de chemin par pathfinding génétique à l'Agent d'identificateur id à la case de coordonnées x,y
  void demande_chemin_algogen(int id, int x, int y);
  
  void iterate_algogen(unsigned int _nbIts);
  
  // Fonction de parsing du fichier regle.xml représentant les règles de leur jeu (description de toutes les unités, contraintes et terrains différents)
  void initiateRules(std::string xmlFileName);
  
  // Fonction de parsing du fichier map.txt représentant la map actuelle de leur jeu (description de toutes les cases variant du terrain par défaut)
  void initiateMap(const std::string & contentFileName);
  
  // Fonction pour tester l'état de notre map
  void test();
  
  // Fonction spéciale au parsing utile à la décomposition de la chaîne str par le délimiteur delimiter
  std::vector<std::string> split(std::string str, char delimiter);
};

#endif
