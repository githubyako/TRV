#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>
#include "str_exception.h"
#include "map.h"
#include <libxml++/libxml++.h>

// Classe représentant le controlleur utile à la communication entre le jeu et la recherche de pathfinding 
// Classe réalisée avec le design pattern "singleton"
class Controller{
private:
  static Controller * s_controller;
  Map* map; // La map associé au controlleur, c'est sur celle-ci que se déroule le jeu et le pathfinding
  
  // Constructeurs :
  Controller();
  Controller(Controller const & _controller);
  
  
public:

  // Destructeur
  ~Controller();
  
  // 
  static Controller * create();
  
  // Fonction de création d'un agent, créé un instance de la classe Agent lorsque le jeu génère une nouvelle unité
  void creer_agent(int x, int y, const std::string type, int id);
  
  // Fonction de suppression d'agent, supprime l'instance d'Agent à l'identificateur id
  void supprimer_agent(int id);
  
  // Fonction de déplacement d'agent, déplace l'Agent d'identificateur id à la case de coordonnées x,y
  void deplacement_agent(int id, int x, int y);
  
  // Fonction permettant la création ou la suppression d'un obstacle à la case de coordonnées x,y
  void setObstacle(int x, int y, bool obs);
  
  // Fonction demande une recherche de chemin par pathfind à l'Agent d'identificateur id à la case de coordonnées x,y
  void demande_chemin(int id, int x, int y);
  
  // Fonction de parsing du fichier regle.xml représentant les règles de leur jeu (description de toutes les unités, contraintes et terrains différents)
  void initiateRules(std::string xmlFileName);
  
  // Fonction de parsing du fichier map.txt représentant la map actuelle de leur jeu (description de toutes les cases variant du terrain par défaut)
  void initiateMap(const std::string & contentFileName);
  
  // Fonction spéciale au parsing utile à la décomposition de la chaîne str par le délimiteur delimiter
  std::vector<std::string> split(std::string str, char delimiter);
};

#endif
