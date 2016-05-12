#ifndef MAP_H
#define MAP_H

#include <map>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <ctime>

#include "case.h"
#include "terrain.h"
#include "agent.h"
#include "unite.h"

// #include "minion.h"

class Map{
private:
  friend class Algogen;
  static Map* m_map; // On ne souhaite qu'il n'y ai qu'une et une seule instance de Map
  int m_w,m_h; // Nombre de case en x (m_w) et nombre de case en y (m_h) de la map
  std::map<int, Case*> m_sommets; // Map associant à un indice int, une case Case*
  std::vector<Terrain*> m_terrains; // Vector contenant tout les terrains décrient dans regle.xml
  std::vector<Agent*> m_agents; // Vector contenant tous les agents du jeu. Si on rajoute un agent, on rajoute un élément un vecteur, si on le supprime, on mets cette élément à NULL
  std::vector<Unite*> m_unites; // Vector contenant toutes les unités décrient dans regle.xml
  std::vector<Contrainte*> m_contraintes; // Vector contenant toutes les contraintes décrient dans regle.xml
  // Constructeurs :
  Map();
  Map(Map const & _map);
 
//  friend class Minion;
public:
  
  // On ne veut pas donner accès au constructeur de Controller car on ne souhaite qu'une instance de Controller à la fois
  static Map* create();
  
  // Fonction pour tester l'état de la map
  void test();
  
  // Fonction pour ajouter les voisins d'une case
  void Init_vois();
  
  // Fonction d'ajout de Terrain (avec ou sans obstacle) à la map
  void addTerrain(std::string const & _type, std::vector<std::pair<std::string const &, float> > & _contraintes_defaut);
  void addTerrain(std::string const & _type, std::vector<std::pair<std::string const &, float> > & _contraintes_defaut, bool _obstacle);
  
  // Fonction d'ajout d'Unité à la map 
  void addUnite(const std::string& _type, std::vector< std::pair< std::string const&, float > >& _vitesse_d, 
		std::vector< std::pair< std::string const&, float > >& _consoContraintes);
		
  // Fonction d'ajout d'un agent à la map
  void addAgent(int _iden, int _x, int _y, std::string const &_unite);
  
  // Fonction d'ajout d'une Contrainte à la map
  void addContrainte(std::string const& _contrainte);
  
  // Fonction pour la déplacement d'un agent d'identifiant id et à la "position" id du vector m_agents vers la case de coordonnées x,y
  void move_agent(int id, int x, int y);
  
  // Fonction pour la suppresion d'un agent d'identifiant id et à la "position" id du vector m_agents
  void suppr_agent(int id);
  
  // Fonction pour trouver un chemin vers une case cible pour un agent avec l'algorithme de Dijkstra adapté pour l'algorithme génétique
  const std::vector<std::pair<bool,bool>*> dijkstra_GA(unsigned int id, unsigned int idCible, const Unite* unite);
  
  // Fonction pour trouver un chemin vers une case cible pour un agent avec l'algorithme A* adapté pour l'algorithme génétique
  const std::vector<std::pair<bool,bool>*> A_star_GA(unsigned int id, unsigned int idCible, const Unite* unite);
  
  // Getteurs :
  int get_m_w() const;
  int get_m_h() const;
  Case* get_Case(int _x, int _y) const;
  Case* get_Case(int _somm) const;
  Agent* get_Agent(int id) const;
  Terrain* get_Terrain(std::string const & _terrName) const;
  Contrainte * get_Contrainte(std::string const & _contrName) const;
  const std::map<int,Case*>*get_sommets() const;
  
  // Setteurs :
  
  // Fonction pour changer le type de la case de coordonnée x,y en terrain de type _terrName
  void set_Terrain(int _x, int _y, std::string const & _terrName);
 
  // Fonction pour changer le type de la case de coordonnée x,y en contrainte de type _contrName
  void set_Contrainte(int _x, int _y, std::string const & _contrName);
  
  // Fonction pour changer le type de la case de coordonnée x,y en contrainte de type _contrName et en obstacle
  void set_Contrainte(int _x, int _y, std::string const & _contrName, float _qte);
  
  // Fonction changeant le booléen obst de la case à la coordonnée x,y
  void set_Obstacle(int _x, int _y, int obst);
  
  // Fonction pour modifier la taille de la map
  void set_Taille(int _w, int _h);
  
  // Destructeur
  ~Map();
  
};


#endif