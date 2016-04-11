#include "controller.h"

// *************
// Constructeurs
// *************

Controller::Controller()
{
  // création des pipes entrants ? IL FAUT CHOISIR CLASSE INTERFACE OU THREAD+PIPES
  /*int creation_unite[2],;
  pipe(creation_unite);*/
  
  // création du pipe sortant
}

Controller::Controller(const Controller& _controller)
{
   
}

Controller* Controller::create()
{
  /*if(Controller::s_controller!=nullptr){
    throw new str_exception("An instance of controller already exists");
  }else{
    Controller::s_controller = new Controller();
    // thread?
    return Controller::s_controller;
  }*/
}

// Fonction permettant la création ou la suppression d'un obstacle à la case de coordonnées x,y
void Controller::setObstacle(int x, int y, bool obs)
{
  // On regarde si la case de coordonnées x,y existe
  if (x>=map->get_m_w() || x<0 || y<0 || y>=map->get_m_h())
		throw new str_exception("La case n'existe pas");
	else
		(map->get_Case(x,y))->setObstacle(obs);
}

// Fonction de création d'un agent, créé un instance de la classe Agent lorsque le jeu génère une nouvelle unité
void Controller::creer_agent(int x, int y, const std::string type, int id)
{
  // On regarde si la case de coordonnées x,y existe
  if (x>=map->get_m_w() || x<0 || y<0 || y>=map->get_m_h())
		throw new str_exception("La case n'existe pas");
	else
		map->addAgent(id, x, y, type);
}

void Controller::demande_chemin(int id, int x, int y)
{
}

// Fonction de déplacement d'agent, déplace l'Agent d'identificateur id à la case de coordonnées x,y
void Controller::deplacement_agent(int id, int x, int y)
{
	map->move_agent(id, x, y);
}

// Fonction permettant la création ou la suppression d'un obstacle à la case de coordonnées x,y
void Controller::supprimer_agent(int id)
{
	map->suppr_agent(id);
}

// Fonction de parsing du fichier map.txt représentant la map actuelle de leur jeu (description de toutes les cases variant du terrain par défaut)
void Controller::initiateMap(const std::string& contentFileName)
{
  int x; // Coordonnée x récupérée à chaque lecture de ligne
  int y; // Coordonnée y récupérée à chaque lecture de ligne
  std::string type_terr; // Type de terrain récupéré à chaque lecture de ligne
  std::string contrainte =""; // Contraintes récupérées, ou non, à chaque lecture de ligne
  std::string::size_type sz;
  int obst=0; // Obstacle récupéré, ou non, à chaque lecture de ligne
  std::vector<std::string> splitter; // Chaîne utile à la décomposition de chaque ligne par le délimiteur ' '
  std::ifstream fichier (contentFileName.c_str(), std::ios::in); // On ouvre le fichier
  if(fichier) // On regarde si le fichier s'est bien ouvert
  {
    std::string contenu; // Contenu d'une ligne
    std::getline(fichier, contenu); // On récupère le contenu de la première ligne indiquant la taille de la map en x et y
    splitter = split(contenu, ' '); // On splitt la ligne
    x = atoi(splitter[0].c_str()); // On récupère le nombre de case en x de la map
    y = atoi(splitter[1].c_str()); // On récupère le nombre de case en y de la map
    Map M(x,y); // On créé une map
    while (std::getline(fichier, contenu)) // On récupère le contenu des lignes suivants (décrivant les différentes case différentes du terrain par défaut)
    {
      splitter.clear(); // On vide la chaîne splitter
      splitter = split(contenu, ' '); // On splitt le contenu de la ligne
      x = atoi(splitter[0].c_str()); // On récupère la coordonnée x de la case
      y = atoi(splitter[1].c_str()); // On récupère la coordonnée y de la case
      type_terr = splitter[2]; // On récupère le type de terrain de la case
      switch (splitter.size()) // On switch sur la taille du splitter
      {
	case 4:
	  contrainte = splitter[3]; // Dans ce cas on récupère les contraintes de la case
	  M.set_Terrain(x,y,contrainte); // On instancie les contraintes de cette case dans la map
	  break;
	case 5:
	  contrainte = splitter[3]; // Dans ce cas on récupère les contraintes de la case
	  obst = atoi(splitter[4].c_str()); // Ainsi que son obstacle
	  M.set_Terrain(x,y,contrainte); // On instancie les contraintes de cette case dans la map
	  M.set_Obstacle(x,y,obst); // On instancie l'obstacle de cette case dans la map
	  break;
      }
      M.set_Terrain(x,y,type_terr); // On instancie le type de terrain de cette case dans la map
    }
    fichier.close(); // On ferme le fichier
  }
   else // Cas où le fichier s'est mal ouvert
   {
     std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
   }
}

void Controller::initiateRules(std::string xmlFileName)
{
   //Parse fichier .xml des règles de la carte
  xmlpp::DomParser parser;
  parser.set_validate();
  parser.parse_file(xmlFileName);
  
  xmlpp::Node* rootNode = parser.get_document()->get_root_node();
  xmlpp::NodeSet contraintes = rootNode->find("/regle/contraintes");
  for(xmlpp::NodeSet::iterator i=contraintes.begin(); i != contraintes.end(); ++i){
    xmlpp::Node::NodeList c_attributes = (*i)->get_children();
    for (xmlpp::Node::NodeList::iterator a_i=c_attributes.begin(); a_i != c_attributes.end(); i++)
    {
      xmlpp::Attribute &attribute = static_cast<xmlpp::Attribute*>(a_i);
      map->addContrainte(attribute.get_value().raw());
    }
  }
  xmlpp::NodeSet terrains = rootNode->find("/regle/terrains");
  for(xmlpp::NodeSet::iterator i=terrains.begin(); i != terrains.end(); ++i){
    xmlpp::Node::NodeList t_attributes = (*i)->get_children();
    std::string type, contrainte_def;
    bool obstacle = false;
    std::vector< std::pair< std::string,float > > _contraintes;
    for (xmlpp::Node::NodeList::iterator a_i=t_attributes.begin(); a_i != t_attributes.end(); i++)
    {
      xmlpp::Attribute &attribute = static_cast<xmlpp::Attribute&>(a_i);
      if (attribute.get_name() == "type")
      {
	  type = attribute.get_value().raw();
      } else if(attribute.get_name() == "contrainte_defaut")
      {
	contrainte_def = attribute.get_value().raw();
	std::vector<std::string> vec_contrainte = split(contrainte_def,';');
	for(std::vector<std::string>::iterator v_i = vec_contrainte.begin(); v_i != vec_contrainte.end(); ++i)
	{
	  std::vector<std::string> vec_detail = split(*v_i,':');
	  _contraintes.push_back(std::pair<std::string,float>(vec_detail[0], ::atof(vec_detail[1].c_str())));
	}
      } else if(attribute.get_name() == "obstacle")
      {
	 obstacle = true;
      }
    }
/*    std::vector<std::pair<std::string const&,float> > v;
    for(unsigned int i=0;i<_contraintes.size();++i){
      std::string const & stref = _contraintes.at(i).first;
      v.push_back(std::pair<std::string const&,float>(stref,_contraintes.at(i).second));
    }
    map->addTerrain(type,v,obstacle);
   */ 
  }
  xmlpp::NodeSet unites = rootNode->find("/regle/unites");
  for(xmlpp::NodeSet::iterator i=unites.begin(); i != unites.end(); ++i){
    xmlpp::Node::NodeList u_attributes = (*i)->get_children();
    std::string type, contrainte, deplacement;
    std::vector< std::pair< std::string,float > > _contraintes, _deplacements;
    for (xmlpp::Node::NodeList::iterator a_i=u_attributes.begin(); a_i != u_attributes.end(); i++)
    {
      xmlpp::Attribute &attribute = dynamic_cast<xmlpp::Attribute&>(a_i);
      if (attribute.get_name() == "type"){
	  type = attribute.get_value().raw();
      } else if(attribute.get_name() == "contrainte"){
	contrainte = attribute.get_value().raw();
	std::vector<std::string> vec_contrainte = split(contrainte,';');
	for(std::vector<std::string>::iterator v_i = vec_contrainte.begin(); v_i != vec_contrainte.end(); ++i){
	  std::vector<std::string> vec_detail = split(*v_i,':');
	  _contraintes.push_back(std::pair<std::string,float>(vec_detail[0], ::atof(vec_detail[1].c_str())));
	}
      } else if(attribute.get_name() == "deplacement"){
	deplacement = attribute.get_value().raw();
	std::vector<std::string> vec_deplacement = split(deplacement,';');
	for(std::vector<std::string>::iterator v_i = vec_deplacement.begin(); v_i != vec_deplacement.end(); ++i){
	  std::vector<std::string> vec_detail = split(*v_i,':');
	  _deplacements.push_back(std::pair<std::string,float>(vec_detail[0], ::atof(vec_detail[1].c_str())));
	}
      }
    }
//     std::vector<std::pair<std::string const&,float> > v,v2;
//     for(unsigned int i=0;i<_contraintes.size();++i){
//       std::string const & stref = _contraintes.at(i).first;
//       v.push_back(std::pair<std::string const&,float>(stref,_contraintes.at(i).second));
//     }
//     for(unsigned int i=0;i<_deplacements.size();++i){
//       std::string const& stref = _deplacements.at(i).first;
//       v2.push_back(std::pair<std::string const&,float>(stref,_deplacements.at(i).second));
//     }
//     map->addUnite(type,v,v2);
  }
  
}

std::vector< std::string > Controller::split(std::string str, char delimiter)
{
  std::vector<std::string> internal;
  std::stringstream ss(str);
  std::string tok;
  
  while(std::getline(ss, tok, delimiter))
  {
    internal.push_back(tok);
  }
  return internal;
}

// ***********
// Destructeur
// ***********

Controller::~Controller()
{

}