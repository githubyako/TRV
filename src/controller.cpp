#include "controller.h"

Controller* Controller::s_controller;

// *************
// Constructeurs
// *************

Controller::Controller()
{

}

Controller::Controller(const Controller& _controller)
{
   
}

// On ne veut pas donner accès au constructeur de Controller car on ne souhaite qu'une instance de Controller à la fois
Controller* Controller::create()
{
  if(Controller::s_controller!=nullptr){ // On regarde si un Controller existe déjà
    throw new str_exception("An instance of controller already exists"); // Si oui, on lève une exception
  }else{
    Controller::s_controller = new Controller(); // Si non, on créé le controller
    // thread?
    return Controller::s_controller;
  }
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
  try{
  // On regarde si la case de coordonnées x,y existe
  if (x>=map->get_m_w() || x<0 || y<0 || y>=map->get_m_h())
		throw new str_exception("La case n'existe pas");
	else
		map->addAgent(id, x, y, type);
  }catch(str_exception* e){
    throw(*e);
  }
}

// Fonction demandant une recherche de chemin par pathfinding Dijkstra à l'Agent d'identificateur id à la case de coordonnées x,y
void Controller::demande_chemin(int id, int x, int y)
{
  if (x >= map->get_m_w() || y >= map->get_m_h()) // On test si la case de destination est bien compris dans la map
    throw new str_exception("Cette case n'existe pas"); // Si non, on lève une exception
  else // Si oui, on lance l'algorithme de Dijkstra
    std::vector<std::pair<bool,bool>*> vec = map->dijkstra_GA(map->get_Agent(id)->getCase()->get_sommet(), map->get_Case(x,y)->get_sommet(), map->get_Agent(id)->getUnite()); 
}

// Fonction demandant une recherche de chemin par pathfinding A* à l'Agent d'identificateur id à la case de coordonnées x,y
void Controller::demande_chemin_A_star(int id, int x, int y)
{
  if (x >= map->get_m_w() || y >= map->get_m_h()) // On test si la case de destination est bien compris dans la map
    throw new str_exception("Cette case n'existe pas"); // Si non, on lève une exception
  else // Si oui, on lance l'algorithme A*
	std::vector<std::pair<bool, bool>*> vec2 = map->A_star_GA(map->get_Agent(id)->getCase()->get_sommet(), map->get_Case(x,y)->get_sommet(), map->get_Agent(id)->getUnite());
}

void Controller::create_algogen()
{
  if(m_algg==nullptr){
// 	float total=0;
// 	unsigned int iteration=1500;
 	unsigned int popsize=100;
	float manhattan = 0.8;
	float mutaRatio = 0.05;
	float popToMutate = 1;
 	unsigned int nbAjouts = 5;
	float ratioSupprs = 0.1;
	float ratioModifs = 0.1;
	float ratioElitism = 0.05;
	float cullRatio = 0.02;
	unsigned int  nbkids=3;

// 	int test=1;
// 	int i=1,j=1;
// 	for(unsigned int popsize=100;popsize<=500;popsize+=200){
// 	  std::cout << "Passe " << i << " sur 10." << std::endl;
	
	// 100, 0, 0.05, 1, 9, 0.09, 0.1, 0.05, 0.15, 3
// 	  for(float manhattan = 0;manhattan <= 1;manhattan+=0.3){
// 	    std::cout << "Passe " << i << "." << j << std::endl;
// 	    for(float mutaRatio = 0.05;mutaRatio<0.5;mutaRatio+=0.2){
// 	      for(float popToMutate=0.2;popToMutate<=1;popToMutate+=0.4){
// 		for(unsigned int nbAjouts = 1;nbAjouts<=10;nbAjouts+=2){
// 		  for(float ratioSupprs=0.05;ratioSupprs<0.1;ratioSupprs+=0.02){
// 		    for(float ratioModifs=0.1;ratioModifs<=0.2;ratioModifs+=0.05){
// 		      for(float ratioElitism = 0.05;ratioElitism<0.3;ratioElitism+=0.1){
// 			for(float cullRatio = 0.05;cullRatio<=0.2;cullRatio+=0.05){
// 			  for(unsigned int nbkids=3;nbkids<=5;nbkids+=2){
			      m_algg = new Algogen (map->get_m_w(),map->get_m_h(),map->get_sommets(),popsize,manhattan,mutaRatio,popToMutate,nbAjouts,ratioSupprs,ratioModifs,ratioElitism,cullRatio,nbkids);
// 			  }
// 			}
// 		      }
// 		    }
// 		  }
// 		}
// 	      }
// 	    }
// 	    j++;
// 	  }
// 	  i++;
// 	}
  }else{
    std::cerr << "Impossible de créer un nouvel algogen: il en existe déjà un" << std::endl;
  }
}

// Fonction demandant une recherche de chemin par pathfinding génétique à l'Agent d'identificateur id à la case de coordonnées x,y
void Controller::demande_chemin_algogen(int id, int x, int y)
{
  if (x >= map->get_m_w() || y >= map->get_m_h())
    throw new str_exception("Cette case n'existe pas");
  else{
    int idsource = map->get_Agent(id)->getCase()->get_sommet();
    const Unite * typeAgent = map->get_Agent(id)->getUnite();
    m_algg->addDeplacement(id, idsource,x*map->get_m_h()+y,typeAgent);
  }
}

void Controller::iterate_algogen(unsigned int _nbIts)
{
  for(unsigned int i=0;i<_nbIts;++i){
    m_algg->iterate();
    if(i%100 == 0){
      std::cout << i << std::endl;
    }
  }
  m_algg->calcSousMinions();
  m_algg->show();
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
  std::string contraintes =""; // Contraintes récupérées, ou non, à chaque lecture de ligne
  std::string::size_type sz;
  bool obst=false; // Obstacle récupéré, ou non, à chaque lecture de ligne
  std::vector<std::string> splitter; // Chaîne utile à la décomposition de chaque ligne par le délimiteur ' '
  std::vector<std::string> contrainte;
  std::vector<std::string> splitter3;
  std::ifstream fichier (contentFileName.c_str(), std::ios::in); // On ouvre le fichier
  if(fichier) // On regarde si le fichier s'est bien ouvert
  {
    std::string contenu; // Contenu d'une ligne
    std::getline(fichier, contenu); // On récupère le contenu de la première ligne indiquant la taille de la map en x et y
    splitter = split(contenu, ' '); // On splitt la ligne
    x = atoi(splitter[0].c_str()); // On récupère le nombre de case en x de la map
    y = atoi(splitter[1].c_str()); // On récupère le nombre de case en y de la map
    map->set_Taille(x,y); // On créé une map
    while (std::getline(fichier, contenu)) // On récupère le contenu des lignes suivants (décrivant les différentes case différentes du terrain par défaut)
    {
      obst = false;
      splitter.clear(); // On vide la chaîne splitter
      splitter = split(contenu, ' '); // On splitt le contenu de la ligne
      x = atoi(splitter[0].c_str()); // On récupère la coordonnée x de la case
      y = atoi(splitter[1].c_str()); // On récupère la coordonnée y de la case
      type_terr = splitter[2]; // On récupère le type de terrain de la case
      map->set_Terrain(x,y,type_terr); // On instancie le type de terrain de cette case dans la map
      map->set_Contrainte(x,y,type_terr);
      switch (splitter.size()) // On switch sur la taille du splitter
      {
	case 4:
	  contraintes = splitter[3]; // Dans ce cas on récupère les contraintes de la case
	  contrainte = split(contraintes, ';'); // On split les différentes contraintes (séparées par un ';')
	  for (unsigned int i=0; i<contrainte.size(); i++) // Pour chaque split
	  {
	    splitter3 = split(contrainte[i], ':'); // On split les différentes contraintes pour récupérer son nom (splitter3[0]) et sa valeur (splitter3[1])
	    map->set_Contrainte(x,y,splitter3[0],atof(splitter3[1].c_str())); // On instancie les contraintes de cette case dans la map
	  }
	  break;
	case 5:
	  contraintes = splitter[3]; // Dans ce cas on récupère les contraintes de la case
	  contrainte = split(contraintes, ';'); // On split les différentes contraintes (séparées par un ';')
	  for (unsigned int i=0; i<contrainte.size(); i++) // Pour chaque split
	  {
	    splitter3 = split(contrainte[i], ':'); // On split les différentes contraintes pour récupérer son nom (splitter3[0]) et sa valeur (splitter3[1])
	    map->set_Contrainte(x,y,splitter3[0],atof(splitter3[1].c_str())); // On instancie les contraintes de cette case dans la map
	  }
	  if (atoi(splitter[4].c_str()) == 1)
	    obst = true; // Ainsi que son obstacle
	  map->set_Obstacle(x,y,obst); // On instancie l'obstacle de cette case dans la map
	  break;
      }
    }
    map->Init_vois();
    fichier.close(); // On ferme le fichier
  }
   else // Cas où le fichier s'est mal ouvert
   {
     std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
   }
   
}

void Controller::initiateRules(std::string xmlFileName)
{
   //Parse fichier .xml des règles 	de la carte
  
  map = Map::create();
  xmlpp::DomParser parser;		//Objet parser DOM de libxml++
  parser.set_validate();		//Demande de validation automatique à l'ouverture d'un fichier
  parser.parse_file(xmlFileName);	//Ouverture du xml avec validation
  xmlpp::Node* rootNode = parser.get_document()->get_root_node();	//On prend le tout premier noeud du xml (<regles>)
  
    
  
  
  
  // **************************** CONTRAINTES **********************************************
  
  
  xmlpp::NodeSet contraintes = rootNode->find("//regle/contraintes");	//XPath, on va chercher les balises concernant les contraintes
  xmlpp::Node* contrainte = contraintes[0];
  xmlpp::Node::NodeList l_c = contrainte->get_children("contrainte");
  for(xmlpp::Node::NodeList::iterator i=l_c.begin(); i != l_c.end(); ++i){	//iterations sur les noeuds de contraintes
    xmlpp::Element * element = dynamic_cast<xmlpp::Element*>(*i);			//On transforme le noeud en "Element", pour pouvoir prendre ses attributs
    xmlpp::Element::AttributeList c_attributes = element->get_attributes();		// On prend les attributs de l'élement
    for (xmlpp::Element::AttributeList::iterator a_i=c_attributes.begin(); a_i != c_attributes.end(); a_i++) //On itère sur les attributs
    {
      xmlpp::Attribute *attribute = *a_i;	//On prend l'attribut
      map->addContrainte(attribute->get_value().raw());	//On prend sa valeur
    }
  }
  
  
  
  
  // **************************** TERRAINS **********************************************
  
  
  xmlpp::NodeSet terrains = rootNode->find("//regle/terrains");	//XPath, on va chercher les balises concernant les terrains
  xmlpp::Node* terrain = terrains[0];  
  xmlpp::Node::NodeList l_t = terrain->get_children("terrain_defaut");
  for(xmlpp::Node::NodeList::iterator i=l_t.begin(); i != l_t.end(); ++i){	//On itère sur les noeuds de terrains
    xmlpp::Element * element = dynamic_cast<xmlpp::Element*>(*i);		//On transforme le noeud en Element
    xmlpp::Element::AttributeList t_attributes = element->get_attributes();	//On prend les attributs de l'élement
    			
    std::string type, contrainte_def;						//On définit ici les différentes informations qui nous intéressent 
    bool obstacle = false;
    std::vector< std::pair< std::string,float > > _contraintes;			//Le vecteur renvoyé au final
    for (xmlpp::Element::AttributeList::iterator a_i=t_attributes.begin(); a_i != t_attributes.end(); a_i++)	//on itère sur les attributs de la chaque terrain
    {
      
      xmlpp::Attribute *attribute = *a_i;	//On prend l'attribut
     
      
      if (attribute->get_name() == "type")	// Type : On prend le string sans traitement
      {
	  type = attribute->get_value().raw();
      } else if(attribute->get_name() == "contrainte_defaut")	//Contraintes : On doit parser le string qu'on nous envoie
      {
	contrainte_def = attribute->get_value().raw();		//On prend le string contenant toutes les contraintes
	std::vector<std::string> vec_contrainte = split(contrainte_def,';');	//On utilise la méthode split pour avoir tous les string séparés par des ";"
	for(std::vector<std::string>::iterator v_i = vec_contrainte.begin(); v_i != vec_contrainte.end(); ++v_i)	//On itère sur ces strings
	{
	  std::vector<std::string> vec_detail = split(*v_i,':');		//On utilise la méthode split pour avoir tous les string séparés par des ":"
	  _contraintes.push_back(std::pair<std::string,float>(vec_detail[0], ::atof(vec_detail[1].c_str())));	//Le string renvoyé contiendra forcément deux string, donc on envoie les deux
	  // Ici, le premier est le nom de la contrainte, et le deuxième la valeur
	}
      } else if(attribute->get_name() == "obstacle")	//Obstacle : On indique seulement que le terrain est un obstacle
      {
	 obstacle = true;
      }
    }	
    std::vector<std::pair<std::string const&,float> > v;	//On transforme le vecteur sans reference de string en references de string
    for(unsigned int i=0;i<_contraintes.size();++i){
      std::string const & stref = _contraintes.at(i).first;
      v.push_back(std::pair<std::string const&,float>(stref,_contraintes.at(i).second));
    }		
    map->addTerrain(type,v,obstacle);			//On envoie le vecteur
    if(i ==l_t.begin() && (*i)->get_name() == "terrain_defaut"){
      l_t = terrain->get_children("terrain");
      i = l_t.begin();
      i--;
    }
  }
    
  
  
  
  // **************************** UNITES **********************************************
 
  xmlpp::NodeSet unites = rootNode->find("//regle/unites");		//XPath, on va chercher les balises concernant les unités
  xmlpp::Node* unite = unites[0];  
  xmlpp::Node::NodeList l_u = unite->get_children("unite");
  for(xmlpp::Node::NodeList::iterator i=l_u.begin(); i != l_u.end(); ++i){	//On itère sur les unités
    xmlpp::Element * element = dynamic_cast<xmlpp::Element*>(*i);		//On transforme le noeud en élement
    xmlpp::Element::AttributeList u_attributes = element->get_attributes();	//On prend les attributs de l'éléments
    std::string type, contrainte, deplacement;					//On indique ce qu'on veut récupérer
    std::vector< std::pair< std::string,float > > _contraintes, _deplacements;
    for (xmlpp::Element::AttributeList::iterator a_i=u_attributes.begin(); a_i != u_attributes.end(); a_i++)	//On itère sur les attributs de chaque unités
    {
      xmlpp::Attribute *attribute = *a_i;		//On prend l'attribut
      if (attribute->get_name() == "type"){		//Type : On prend le string
	  type = attribute->get_value().raw();
      } else if(attribute->get_name() == "contrainte"){	//Contrainte : On doit traiter le string qui nous ait envoyé
	contrainte = attribute->get_value().raw();	//On prend le string qui nous ait envoyé
	std::vector<std::string> vec_contrainte = split(contrainte,';');	//On split le string selon les ";"
	for(std::vector<std::string>::iterator v_i = vec_contrainte.begin(); v_i != vec_contrainte.end(); ++v_i){	//On itère sur les string séparés
	  std::vector<std::string> vec_detail = split(*v_i,':');						//On split chaque string selon ":"
	  //On a alors exactement deux string, le premier donnant la contrainte et le deuxième sa valeur
	  _contraintes.push_back(std::pair<std::string,float>(vec_detail[0], ::atof(vec_detail[1].c_str())));	
	}
      } else if(attribute->get_name() == "deplacement"){	//Deplacement : On doit traiter le string qui nous ait envoyé
	deplacement = attribute->get_value().raw();		// On prend le string qui nous ait envoyé
	std::vector<std::string> vec_deplacement = split(deplacement,';');	//On sépare le string selon les ";"
	for(std::vector<std::string>::iterator v_i = vec_deplacement.begin(); v_i != vec_deplacement.end(); ++v_i){	//On itère sur les string séparés
	  std::vector<std::string> vec_detail = split(*v_i,':');						//On sépare chaque string selon les ":"
	  //On a alors exactement deux string, le premier donnant le terrain concerné et le deuxième sa valeur
	  _deplacements.push_back(std::pair<std::string,float>(vec_detail[0], ::atof(vec_detail[1].c_str())));	
	}
      }
    }
    //On convertit les deux vecteur à envoyé de string en &string
    std::vector<std::pair<std::string const&,float> > v,v2;	
     for(unsigned int i=0;i<_contraintes.size();++i){
       std::string const & stref = _contraintes.at(i).first;
       v.push_back(std::pair<std::string const&,float>(stref,_contraintes.at(i).second));
     }
     for(unsigned int i=0;i<_deplacements.size();++i){
       std::string const& stref = _deplacements.at(i).first;
       v2.push_back(std::pair<std::string const&,float>(stref,_deplacements.at(i).second));
     }
     
      map->addUnite(type,v2,v);
    
  }
}

// Fonction spéciale au parsing utile à la décomposition de la chaîne str par le délimiteur delimiter
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

// Fonction pour tester l'état de notre map
void Controller::test()
{
  map->test();
}

// ***********
// Destructeur
// ***********

Controller::~Controller()
{
  delete map;
  delete m_algg;
}

void Controller::delete_controller()
{
  delete s_controller;
}

