#include "controller.h"

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


void Controller::setObstacle(int x, int y, bool obs)
{
  if (x>=Map.get_m_w() || x<0 || y<0 || y>=Map.get_m_h())
		throw new str_exception("La case n'existe pas");
	else
		(Map.get_Case(x,y)).setObstacle(obs);
}

void Controller::creer_agent(int x, int y, const std::string type, int id)
{
  if (x>=Map.get_m_w() || x<0 || y<0 || y>=Map.get_m_h())
		throw new str_exception("La case n'existe pas");
	else
		Map.addAgent(id, x, y, type);
}

void Controller::demande_chemin(int id, int x, int y)
{
}

void Controller::deplacement_agent(int id, int x, int y)
{
	Map.move_agent(id, x, y);
}

void Controller::supprimer_agent(int id)
{
	Map.suppr_agent(id);
}

void Controller::initiateMap(std::string contentFileName)
{
  int x;
  int y;
  std::string type_terr;
  std::string contrainte ="";
  std::string::size_type sz;
  int obst=0;
  int i;
  std::vector<std::string> splitter;
  std::ifstream fichier (contentFileName.c_str(), std::ios::in);
  if(fichier)
  {
    std::string contenu;
    std::getline(fichier, contenu);
    splitter = split(contenu, ' ');
    x = atoi(splitter[0].c_str());
    y = atoi(splitter[1].c_str());
    Map M(x,y);
    while (std::getline(fichier, contenu))
    {
      splitter.clear();
      splitter = split(contenu, ' ');  
      x = atoi(splitter[0].c_str());
      y = atoi(splitter[1].c_str());
      type_terr = splitter[2];
      switch (splitter.size())
      {
	case 4:
	  contrainte = splitter[3];
	  (M.get_Case(x,y)).setContrainte(contrainte);
	  break;
	case 5:
	  contrainte = splitter[3];
	  obst = atoi(splitter[4].c_str());
	  (M.get_Case(x,y)).setContrainte(contrainte);
	  (M.get_Case(x,y)).setObstacle(obst);
	  break;
      }
      M.set_Terrait(x,y,type_terr);
    }
    fichier.close();
  }
   else
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
    xmlpp::NodeList c_attributes = (*i).get_children();
    for (xmlpp::NodeList::iterator a_i=c_attributes.begin(); a_i != c_attributes.end(); i++)
    {
      xmlpp::Attribute &attribute = dynamic_cast<xmlpp::Attribute&>(*a_i);
      map->addContrainte(attribute.get_value().raw());
    }
  }
  xmlpp::NodeSet terrains = rootNode->find("/regle/terrains");
  for(xmlpp::NodeSet::iterator i=terrains.begin(); i != terrains.end(); ++i){
    xmlpp::NodeList t_attributes = (*i).get_children();
    std::string type, contrainte_def;
    bool obstacle = false;
    std::vector< std::pair< std::string,float > > _contraintes;
    for (xmlpp::NodeList::iterator a_i=t_attributes.begin(); a_i != t_attributes.end(); i++)
    {
      xmlpp::Attribute &attribute = dynamic_cast<xmlpp::Attribute&>(*a_i);
      if (attribute.get_name() == "type")
      {
	  type = attribute.get_value().raw();
      } else if(attribute.get_name() == "contrainte_defaut")
      {
	contrainte_def = attribute.get_value().raw();
	std:vector<std::string> vec_contrainte = split(contrainte_def,';');
	for(std::vector::iterator v_i = vec_contrainte.begin(); v_i != vec_contrainte.end(); ++i)
	{
	  std:vector<std::string> vec_detail = split(*v_i,':');
	  _contraintes.push_back(std::pair<std::string,float>(vec_detail[0], ::atof(vec_detail[1].c_str()));
	}
      } else if(attribute.get_name() == "obstacle")
      {
	 obstacle = true;
      }
    }
    map->addTerrain(type,_contraintes,obstacle);
    
  }
  xmlpp::NodeSet unites = rootNode->find("/regle/unites");
  for(xmlpp::NodeSet::iterator i=unites.begin(); i != unites.end(); ++i){
    xmlpp::NodeList u_attributes = (*i).get_children();
    std::string type, contrainte, deplacement;
    std::vector< std::pair< std::string,float > > _contraintes, _deplacements;
    for (xmlpp::NodeList::iterator a_i=u_attributes.begin(); a_i != u_attributes.end(); i++)
    {
      xmlpp::Attribute &attribute = dynamic_cast<xmlpp::Attribute&>(*a_i);
      if (attribute.get_name() == "type"){
	  type = attribute.get_value().raw();
      } else if(attribute.get_name() == "contrainte"){
	contrainte = attribute.get_value().raw();
	std:vector<std::string> vec_contrainte = split(contrainte,';');
	for(std::vector::iterator v_i = vec_contrainte.begin(); v_i != vec_contrainte.end(); ++i){
	  std:vector<std::string> vec_detail = split(*v_i,':');
	  _contraintes.push_back(std::pair<std::string,float>(vec_detail[0], ::atof(vec_detail[1].c_str()));
	}
      } else if(attribute.get_name() == "deplacement"){
	deplacement = attribute.get_value().raw();
	std:vector<std::string> vec_deplacement = split(deplacement,';');
	for(std::vector::iterator v_i = vec_deplacement.begin(); v_i != vec_deplacement.end(); ++i){
	  std:vector<std::string> vec_detail = split(*v_i,':');
	  _deplacements.push_back(std::pair<std::string,float>(vec_detail[0], ::atof(vec_detail[1].c_str()));
	}
      }
    }
    map->addUnite(type,_contraintes,_deplacements);
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


Controller::~Controller()
{

}
