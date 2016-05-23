#include "map.h"
Map * Map::m_map;
// *************
// Constructeurs
// *************

Map::Map() : m_w(),m_h(),m_sommets(), m_terrains(), m_agents(), m_unites(), m_contraintes()
{
}

Map::Map(const Map& _map)
{

}


// ************
// Destructeurs
// ************

Map::~Map()
{
  for(std::map<int, Case*>::iterator it = m_sommets.begin();it!=m_sommets.end();it++){
    delete it->second;
  }
  for(std::vector<Terrain*>::iterator it = m_terrains.begin();it!=m_terrains.end();it++){
    delete *it;
  }
  for(std::vector<Agent*>::iterator it = m_agents.begin();it!=m_agents.end();it++){
    delete *it;
  }
  for(std::vector<Unite*>::iterator it = m_unites.begin();it!=m_unites.end();it++){
    delete *it;
  }
  for(std::vector<Contrainte*>::iterator it = m_contraintes.begin();it!=m_contraintes.end();it++){
    delete *it;
  }

}

// On ne veut pas donner accès au constructeur de Controller car on ne souhaite qu'une instance de Controller à la fois
Map* Map::create()
{
  if(Map::m_map==nullptr){ // On regarde si une map existe déjà
    Map::m_map = new Map(); // Si non, on en créé une
    return Map::m_map;
  }else{
    throw new str_exception("Une map existe déjà."); //Si oui, on lève une exception
  }
}

// Fonction pour ajouter les voisins d'une case
void Map::Init_vois()
{
  unsigned int x;
  unsigned int y;
  unsigned int j;
  unsigned int k;
  unsigned int maxX;
  unsigned int maxY;
  for(unsigned int i=0; i<m_sommets.size(); ++i)
  {
    x = m_sommets.at(i)->getX();
    y = m_sommets.at(i)->getY();
    (x==0) ? j=x : j=x-1;
    (x==(unsigned int)m_w-1) ? maxX=x : maxX=x+1;
    (y==0) ? k=y : k=y-1;
    (y==(unsigned int)m_h-1) ? maxY=y : maxY=y+1;
    for (;j<=maxX;++j)
      if (j!=x)
	m_sommets.at(i)->set_cases_vois(m_sommets.at(j*m_h+y));
    for (;k<=maxY;++k)
      if (k!=y)
    	m_sommets.at(i)->set_cases_vois(m_sommets.at(x*m_h+k));
  }
}

// Fonction d'ajout de Terrain (sans précision d'obstacle) à la map

void Map::addTerrain(const std::string& _type, std::vector< std::pair<std::string const &, float > > & _contraintes_defaut)
{
  // On regarde si le terrain existe déjà au vector m_terrains de la map
  std::vector< std::pair<Contrainte*, float> > vec_cont;
  for(unsigned int i=0;i<m_terrains.size();++i){
    if(m_terrains.at(i)->getType()==_type){
      // Si oui, on lève une exception
      throw new str_exception("Le terrain '" + _type + "' existe déjà");
    }
  }
  // Si non, on créé une nouvelle pair à ajouter au vector m_terrains
  for(unsigned int i=0;i<_contraintes_defaut.size();++i){			// creation du vecteur de contraintes
    Contrainte * t = this->get_Contrainte(_contraintes_defaut.at(i).first);
    vec_cont.push_back(std::make_pair(t,_contraintes_defaut.at(i).second));
  }
  m_terrains.push_back(new Terrain(_type,vec_cont));
}

// Fonction d'ajout de Terrain (avec précision d'obstacle) à la map

void Map::addTerrain(const std::string& _type, std::vector< std::pair<std::string const &, float > > & _contraintes_defaut, bool _obstacle)
{
  // On regarde si le terrain existe déjà au vector m_terrains de la map
  std::vector< std::pair<Contrainte*, float> > vec_cont;
  for(unsigned int i=0;i<m_terrains.size();++i){
    if(m_terrains.at(i)->getType()==_type){
      // Si oui, on lève une exception
      throw new str_exception("Le terrain '" + _type + "' existe déjà");
    }
  }
  // Si non, on créé une nouvelle pair à ajouter au vector m_terrains
  for(unsigned int i=0;i<_contraintes_defaut.size();++i){			// creation du vecteur de contraintes
    Contrainte * t = this->get_Contrainte(_contraintes_defaut.at(i).first);
    vec_cont.push_back(std::make_pair(t,_contraintes_defaut.at(i).second));
  }
  m_terrains.push_back(new Terrain(_type,vec_cont,_obstacle));
}

// Fonction d'ajout d'Unité à la map

void Map::addUnite(const std::string& _type, std::vector< std::pair< std::string const &, float > >& _vitesse_d, 
		   std::vector< std::pair< std::string const &, float > >& _consoContraintes)
{
  // On regarde si l'unité existe déjà au vector m_terrains de la map
  for(unsigned int i=0;i<m_unites.size();++i){
    if(m_unites.at(i)->getType()==_type){
      // Si oui, on lève une exception
      throw new str_exception("Le type d'unité '" + _type + "' existe déjà");
    }
  }
  // Si non, on construit la nouvelle unité puis on l'ajoute au vector m_unites
  std::vector< std::pair<Terrain*, float> > vec_vit;
  std::vector< std::pair<Contrainte*, float> > vec_cont;
  for(unsigned int i=0;i<_vitesse_d.size();++i){			// creation du vecteur de vitesses
    Terrain * t = this->get_Terrain(_vitesse_d.at(i).first);
    vec_vit.push_back(std::pair<Terrain*, float>(t,_vitesse_d.at(i).second));
  }
  for(unsigned int i=0;i<_consoContraintes.size();++i){			// creation du vecteur de contraintes
    Contrainte * t = this->get_Contrainte(_consoContraintes.at(i).first);
    vec_cont.push_back(std::pair<Contrainte*, float>(t,_consoContraintes.at(i).second));
  }
  m_unites.push_back(new Unite(_type,vec_vit,vec_cont));
}

// Fonction d'ajout d'un agent à la map
void Map::addAgent(int _iden, int _x, int _y, std::string const & _unite)
{
  
  if(_iden < (int)m_agents.size() && m_agents.at(_iden) != nullptr){
    suppr_agent(_iden);
  }
  
  // On aggrandit le vector m_agents s'il n'y a pas assez de place
  unsigned int id = (unsigned int) _iden;
  if(m_agents.size()<=id){
    m_agents.resize(id+10);
  }
  // On récupère le pointeur vers la case de coordonnée x,y du vector m_sommets de la map
  Case * caseptr = m_sommets.at((_x*m_h)+_y);
  Unite * uniteptr = nullptr;
  // On récupère l'unité de nom _unite avec le vector m_unites de map
  for(unsigned int i=0;i<m_unites.size();++i){
    if(m_unites.at(i)->getType()==_unite){
      uniteptr=m_unites.at(i);
      break;
    }
  }
  // On regarde si la case et l'unité existe dans les différents vector de la map
  if(caseptr==nullptr||uniteptr==nullptr){
    // Si non, on lève une exception
    throw new str_exception("Impossible de créer l'agent '" + std::to_string(id) +"': coordonnées ou type d'unité non valides");
  }else{
    // Si oui, on créer et rajoute le nouvelle agent
    m_agents.at(id)=new Agent(id,caseptr,uniteptr);
  }
  
}

// Fonction d'ajout d'une Contrainte à la map
void Map::addContrainte(std::string const & _contrainte)
{
  // On regarde si la contrainte existe déjà au vector m_terrains de la map
  for(unsigned int i=0;i<m_contraintes.size();++i){
    if(m_contraintes.at(i)->getNom()==_contrainte){
      // Si oui, on lève une exception
      throw new str_exception("La contrainte '" + _contrainte + "' existe déjà");
    }
  }
  // Si non, on créer et rajoute une nouvelle contrainte
  m_contraintes.push_back(new Contrainte(_contrainte));
}

// Fonction pour la déplacement d'un agent d'identifiant id et à la "position" id du vector m_agents vers la case de coordonnées x,y
void Map::move_agent(int id, int x, int y)
{
  // On recherche si l'agent existe dans le vector m_agnets de la map
  unsigned int id2 = (unsigned int) id;
	if (id2 > m_agents.size())
		// Si non, on lève une excpetion
		throw new str_exception("Cette unité n'existe pas");
	// Si oui
	else
	{
		// On regarde si l'unité existe encore
		if (m_agents[id2]==NULL)
			// Si non, on lève une exception
			throw new str_exception("Cette unité n'existe plus");
		else
			if (x >= m_w || y >= m_h)
			  throw new str_exception("Cette case n'existe pas");
			else
			  m_agents[id2]->setCase(Map::m_map->get_Case(x,y));
	}
}

// Fonction pour la suppresion d'un agent d'identifiant id et à la "position" id du vector m_agents
void Map::suppr_agent(int id)
{
  unsigned int id2 = (unsigned int) id;
        // On regarde si l'unité existe encore 
	if (m_agents[id2]==nullptr)
	  // Si non, on lève une exception
	  throw new str_exception("Cette unité n'existe plus");
	else
		// Si oui, on mets le pointeur à NULL
	  delete m_agents[id2];
	  m_agents[id2]=nullptr;
}

// ********
// Getteurs
// ********

int Map::get_m_h() const
{
  return m_h;
}

int Map::get_m_w() const
{
  return m_w;
}

Case* Map::get_Case(int _x, int _y) const
{
  return m_sommets.at((_x*m_h)+_y);
}

Case* Map::get_Case(int _somm) const
{
  return m_sommets.at(_somm);
}


Agent* Map::get_Agent(int id) const
{
  unsigned int id2 = (unsigned int) id;
	if (id2 > m_agents.size())
		throw new str_exception("Cette unité n'existe pas");
	else
	{
		if (m_agents[id2]==NULL)
			throw new str_exception("Cette unité n'existe plus");
		else
			return m_agents[id2];
	}
}

Terrain* Map::get_Terrain(const std::string& _terrName) const
{
  for(unsigned int j=0;j<m_terrains.size();++j){
    if(m_terrains.at(j)->getType()==_terrName){
      return m_terrains.at(j);
    }
  }
  throw new str_exception("Erreur: le terrain '" + _terrName + "' n'existe pas.");
}

Contrainte* Map::get_Contrainte(const std::string& _contrName) const
{
  for(unsigned int j=0;j<m_contraintes.size();++j){
    if(m_contraintes.at(j)->getNom()==_contrName){
      return m_contraintes.at(j);
    }
  }
  throw new str_exception("Erreur: la contrainte '" + _contrName + "' n'existe pas.");
}

const std::map< int, Case* >* Map::get_sommets() const
{
  return &m_sommets;
}


// ********
// Setteurs
// ********

// Fonction pour changer le type de la case de coordonnée x,y en terrain de type _terrName
void Map::set_Terrain(int _x, int _y, const std::string& _terrName)
{
  Case * c = this->get_Case(_x,_y);
  Terrain * t = this->get_Terrain(_terrName);
  c->setTerrain(t);
}

// Fonction pour changer le type de la case de coordonnée x,y en contrainte de type _contrName
void Map::set_Contrainte(int _x, int _y, const std::string& _contrName)
{
  Case * c = this->get_Case(_x,_y);
  Terrain * terr = this->get_Terrain(_contrName);
  c->setContrainte(terr->getContraintes());
}

// Fonction pour changer le type de la case de coordonnée x,y en contrainte de type _contrName et en obstacle
void Map::set_Contrainte(int _x, int _y, const std::string& _contrName, float _qte)
{
 Case * c = this->get_Case(_x,_y);
 Contrainte * con = this->get_Contrainte(_contrName);
 c->setContrainte(con,_qte);
 
}

// Fonction changeant le booléen obst de la case à la coordonnée x,y
void Map::set_Obstacle(int _x, int _y, int obst)
{
  Case * c = this->get_Case(_x,_y);
  if (obst == 0)
    c->setObstacle(false);
  else
    c->setObstacle(true);
}

// Fonction pour modifier la taille de la map
void Map::set_Taille(int _w, int _h)
{
  m_w = _w;
  m_h = _h;
  int casenum=0;
  for(int i=0;i<_w;++i){
    for(int j=0;j<_h;++j){
      m_sommets.insert( std::pair<int, Case*>(casenum++,new Case(i,j,(i*_h)+j,m_terrains.at(0))) );
    }
  }
}

// Fonction pour tester l'état de la map
void Map::test()
{
    std::cout << m_w << " " << m_h << std::endl;
  
}

// Fonction pour trouver un chemin vers une case cible pour un agent avec l'algorithme de Dijkstra adapté pour l'algorithme génétique
const std::vector<std::pair<bool,bool>*> Map::dijkstra_GA(unsigned int id, unsigned int idCible, const Unite* unite)
{
  std::vector<std::pair<bool,bool>*> chemin; // Vecteur de pair de bool représentant le chemin de déplacement de l'agent pour aller de id à idCible
  if (m_sommets.at(idCible)->isObstacle()) // Si la case cible est un obstacle
  {
    return chemin; // On retourne un chemin vide
  }
  bool end = false; // Booléen représentant la fin de recherche de l'algorithme
  unsigned int tmp_somm; // Unsigned int représentant le sommet sur lequel on est en train de réfléchir
  unsigned int somm_act; // Unsigned int représentant le sommet sur lequel on vient de réfléchir
  std::unordered_map<unsigned int, float> couts; // Vecteur de pair représentant pour un sommet (unsigned int) le plus petit coûts (float) trouvé pour l'atteindre à un moment donné
  std::unordered_map<unsigned int, int> antec; // Vecteur de pair représentant, pour un sommet_1, son sommet_2 prédecesseur (sommet_2 prédecesseur pour le chemin le plus court pour atteindre sommet_1)
  std::vector<unsigned int> parcouru; // Vecteur contenant les sommets qu'on a déjà étudié
  std::vector<Case*> tmp_vois; // Vecteur de Case* contenant tous les sommets voisins du sommet sur lequel on est en train de réfléchir
  for(std::map<int, Case*>::iterator i = m_sommets.begin(); i!= m_sommets.end(); i++){ // Initialisation des vecteur couts et antec
    couts.insert(std::pair<unsigned int,float>((unsigned int)(i->first), -1)); // On initialise le vecteur couts à -1 pour tous les sommets
    antec.insert(std::pair<unsigned int,int>((unsigned int)(i->first), -1)); // On initialise le vecteur antec à -1 pour tous les sommets
  }
  tmp_somm = id; // On initialise le sommet sur lequel réfléchir à la case d'origine
  couts.at(id) = 0; // On place le cout du sommet d'origine à 0
  tmp_vois = m_sommets.at(id)->getVois(); // On récupère les voisins de la case d'origine
  
  while(!end){ // Tant que l'on a pas fini :
    for(std::vector<Case*>::iterator i1 = tmp_vois.begin(); i1 != tmp_vois.end(); i1++){ // On parcours tous les voisins de tmp_somm
      if(std::find(parcouru.begin(), parcouru.end(), (*i1)->get_sommet()) == parcouru.end()){ // Si le voisin n'a pas déjà été étudié :
	if((*i1)->isObstacle()){ // On regarde s'il s'agit d'un obstacle
	   couts.at((*i1)->get_sommet()) = -1; // Si oui, on met directement son coûts à -1 et...
	   parcouru.push_back((*i1)->get_sommet()); // On le push ("à tord") dans les sommets parcourus pour ne pas y revenir
	}
	else{ // Si non :
	  if(couts.at((*i1)->get_sommet()) == -1){ // Si on ne l'a encore jamais parcouru
	    couts.at((*i1)->get_sommet()) = couts.at(tmp_somm) + unite->getVitesse(m_sommets.at(tmp_somm)->getTerrain()); // On met à jour son coûts
	    antec.at((*i1)->get_sommet()) = tmp_somm; // On met le sommet actuel comme étant son prédecesseur
	  }else{
	    int tmp_cout = couts.at(tmp_somm) + unite->getVitesse(m_sommets.at(tmp_somm)->getTerrain()); // Si non, on calcul le coût potentiel de tmp_som jusqu'à ce sommet
	    if(tmp_cout < couts.at((*i1)->get_sommet())){ // Si ce nouveau coûts est plus faible que le précedent calculé
	      couts.at((*i1)->get_sommet()) = tmp_cout; // On met à jour le coût
	      antec.at((*i1)->get_sommet()) = tmp_somm; // On met à jour le prédecesseur
	    }
	  }
	}
      }
    }
    parcouru.push_back(tmp_somm); // On met tmp_somm dans les sommets parcourus
    somm_act = tmp_somm;
    for(std::unordered_map<unsigned int, float>::iterator i3 = couts.begin(); i3 != couts.end(); i3++) // On parcours le vecteur coûts à la recherche de la case non parcouru ayant le plus faible coût
    {
      if ((tmp_somm == somm_act) // Si le sommets actuel n'a pas encore été changé et...
	  && (i3->second > 0) // Le coût du sommet est supérieur à 0 et...
	  && (std::find(parcouru.begin(), parcouru.end(), i3->first) == parcouru.end())) // Que l'on a pas encore parcouru
      {
	tmp_somm=i3->first; // On change tmp_somm
      }
      else if((i3->second > 0)  // Si non, si le coût du sommet est supérieur à 0 et...
	  && (std::find(parcouru.begin(), parcouru.end(), i3->first) == parcouru.end()) // La case n'a pas déjà été étudiée
	  && (i3->second < couts.at(tmp_somm) )) // Le coût de ce sommet est plus petit que celui de tmp_somm
      {
	tmp_somm=i3->first; // On change tmp_somm
      }
    }
    tmp_vois = m_sommets.at(tmp_somm)->getVois(); // On met à jour tmp_vois
    if(couts.at(idCible) != -1) // On test si la case cible à déjà été atteinte
    {
      end = true; // On met end à true
      for (std::unordered_map<unsigned int, float>::iterator i4 = couts.begin(); i4 != couts.end() ; i4++) // Pour tous les sommets, on regarde s'il existe un sommet au coût inférieur à celui de idCible
      {
	if(std::find(parcouru.begin(), parcouru.end(), i4->first) == parcouru.end() // S'il n'a pas déjà été parcouru et...
	  && i4->second != -1 // On lui a déjà calculé au moins un coût et...
	  && i4->second < couts.at(idCible)) // ce coût est inférieur à celui de idCible
	{
	  end = false; // On met à jour end
	}
      }
    }
  }
  int sommet_cour = antec.at(idCible); // On récupère le prédecesseur de idCible
  unsigned int sommet_cible = idCible; // On récupère le sommet actuel en traitement (initialisation à idCible)
  int diff=0; // int récupérant le différence entre sommet_cible et sommet_cour
  while(sommet_cour != -1) // Tant que sommet_cour n'est pas -1 (donc que sommet_cible n'est pas la case d'origine id)
  {
    diff = sommet_cible - sommet_cour; // On calcule diff
    if (diff == 1){ // Cas où sommet_cible est au dessus de sommet_cour
      chemin.push_back(new std::pair<bool,bool>(0,0));
    }
    else if (diff == -1){ // Cas où sommet_cible est au dessous de sommet_cour
      chemin.push_back(new std::pair<bool,bool>(1,0));
    }
    else if (diff == m_h){ // Cas où sommet_cible est à droite de sommet_cour
      chemin.push_back(new std::pair<bool,bool>(0,1));
    }
    else if (diff == -m_h){ // Cas où sommet_cible est à gauche de sommet_cour
      chemin.push_back(new std::pair<bool,bool>(1,1));
    }
    sommet_cible = sommet_cour; // On met à jour sommet_cible...
    sommet_cour = antec.at(sommet_cour); // et sommet_cour
  }
  return chemin; // On retourne le chemin
}

// Fonction pour trouver un chemin vers une case cible pour un agent avec l'algorithme A* adapté pour l'algorithme génétique
const std::vector< std::pair< bool,bool>*> Map::A_star_GA(unsigned int id, unsigned int idCible, const Unite* unite)
{
  if(unite == nullptr){
    unite = m_unites.at(0);
  }
  int start = std::clock();
  std::vector<std::pair<bool,bool>*> chemin; // Vecteur de pair de bool représentant le chemin de déplacement de l'agent pour aller de id à idCible
  if (m_sommets.at(idCible)->isObstacle()) // Si la case cible est un obstacle
  {
    return chemin; // On retourne un chemin vide
  }
  unsigned int tmp_somm; // Unsigned int représentant le sommet sur lequel on est en train de réfléchir
  unsigned int x1 = m_sommets.at(idCible)->getX(); // On récupère la coordonnée x de idCible
  unsigned int y1 = m_sommets.at(idCible)->getY(); // On récupère la coordonnée y de idCible
  unsigned int x2; // coordonnée x de la case en traitement
  unsigned int y2; // coordonnée y de la case en traitment
  std::vector<unsigned int> list_ouv; // vecteur de sommets représentant la liste ouverte (liste des sommets à étudier)
  std::vector<unsigned int> list_ferm; // vecteur des sommets représentant la liste fermé (liste des sommets déjà traiter ou qui ne présente plus d'intérêts à être étudié)
  std::unordered_map<unsigned int, float> couts; // Vecteur de pair représentant pour un sommet (unsigned int) le plus petit coûts (float) trouvé pour l'atteindre à un moment donné
  std::unordered_map<unsigned int, int> antec; // Vecteur de pair représentant, pour un sommet_1, son sommet_2 prédecesseur (sommet_2 prédecesseur pour le chemin le plus court pour atteindre sommet_1)
  std::vector<Case*> tmp_vois;
  bool end = false; // Booléen représentant la fin de recherche de l'algorithme
  float distance; // float représentant la distance euclidienne entre la case en traitement et la case cible idCible  
  float couts_act; // float représentant le plus petit coûts des sommets de la liste ouverte
  for(std::map<int, Case*>::iterator i = m_sommets.begin(); i!= m_sommets.end(); i++){ // Initialisation des vecteur couts et antec
    couts.insert(std::pair<unsigned int,float>((unsigned int)(i->first), -1)); // On initialise le vecteur couts à -1 pour tous les sommets
    antec.insert(std::pair<unsigned int,int>((unsigned int)(i->first), -1)); // On initialise le vecteur antec à -1 pour tous les sommets
  }
  tmp_somm = id; // On initialise le sommet sur lequel réfléchir à la case d'origine
  couts.at(id) = 0; // On place le cout du sommet d'origine à 0
  tmp_vois = m_sommets.at(id)->getVois(); // On récupère les voisins de la case d'origine
  list_ouv.push_back(tmp_somm); // On met le sommet d'origine dans la liste ouverte
  while(!end){ // Tant que l'on a pas fini :
    int exectime = (std::clock()-start)/double(CLOCKS_PER_SEC)*1000;
    if (exectime >= 200){
      return chemin;
    }
    for(std::vector<Case*>::iterator i1 = tmp_vois.begin(); i1 != tmp_vois.end(); i1++){ // On parcours tous les voisins de tmp_somm
      if(std::find(list_ferm.begin(), list_ferm.end(), (*i1)->get_sommet()) == list_ferm.end()){ // Si le voisin ne fait pas parti de la liste fermée
	if((*i1)->isObstacle()){ // S'il s'agit s'agit d'un obstacle
	   couts.at((*i1)->get_sommet()) = -1; // On met le coûts du sommet à -1 et...
	   list_ferm.push_back((*i1)->get_sommet()); // On l'insère dans la liste fermée pour ne plus le traiter
	}
	else{ // Sinon... 
	  x2 = (*i1)->getX(); // On récupère la coordonée x de la case
	  y2 = (*i1)->getY(); // On récupère la coordonée y de la case
	  if(couts.at((*i1)->get_sommet()) == -1){ // Si on a jamais étudié le coût de la case
	    couts.at((*i1)->get_sommet()) = couts.at(tmp_somm) + unite->getVitesse(m_sommets.at(tmp_somm)->getTerrain()) + std::sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)); // On met à jour le coût de la case (même calcul que Dijkstra mais on rajoute la distance euclidienne au sommet d'arrivé)
	    antec.at((*i1)->get_sommet()) = tmp_somm; // On met à jour le prédecesseur
	    list_ouv.push_back((*i1)->get_sommet()); // On rajoute le sommet dans la liste ouverte
	  }else{ /// Sinon...
	    distance = couts.at(tmp_somm) + unite->getVitesse(m_sommets.at(tmp_somm)->getTerrain()) + std::sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)); // On calcule la nouvelle distance (même calcule que Dijkstra mais on rajoute la distance enclidienne au sommet d'arrivé)
	    if(distance < couts.at((*i1)->get_sommet())){ // Si ce coût est inférieur au précédent calculé
	      couts.at((*i1)->get_sommet()) = distance; // On met le coût à jour
	      antec.at((*i1)->get_sommet()) = tmp_somm; // On met le prédecesseur à jour
	      list_ouv.push_back((*i1)->get_sommet()); // On met ce sommet dans la liste ouverte 
	    }
	  }
	}
      }
    }
    list_ouv.erase(std::find(list_ouv.begin(), list_ouv.end(), tmp_somm)); // On enlève le sommet que l'on traitait de la liste ouverte (le sommet dont on étudiait les voisins)
    if (list_ouv.empty()) // Si dès lors la liste ouverte est vide :
    {
      return chemin; // Alors il n'existe aucun chemin entre id et idCible
    }
    else // Sinon...
    {
      list_ferm.push_back(tmp_somm); // On rajoute tmp_somm à la liste fermée
      tmp_somm = list_ouv.at(0); // On récupère le premier élément de la liste ouverte
      couts_act = couts.at(tmp_somm); // On récupère le coût de cette élément
      unsigned int i3=1;
      for(;i3 < list_ouv.size(); i3++) // Pour tous les autres éléments de la liste ouverte :
      {
	if (couts.at(list_ouv.at(i3)) < couts_act) // Si son coût est inférieur à couts_act
	{
	  tmp_somm = list_ouv.at(i3); // On met à jour tmp_somm
	  couts_act = couts.at(list_ouv.at(i3)); // Ainsi que couts_act
	}
      }
    }
    tmp_vois = m_sommets.at(tmp_somm)->getVois(); // On récupère les voisins du nouveau tmp_somm
    if(std::find(list_ferm.begin(), list_ferm.end(), idCible) < list_ferm.end()) // Si on trouve idCible dans la liste fermée
    {
      end = true; // Alors on a trouvé un chemin entre id et idCible
    }
    }
  int sommet_cour = antec.at(idCible); // On récupère le prédecesseur de idCible
  unsigned int sommet_cible = idCible; // On récupère le sommet actuel en traitement (initialisation à idCible)
  int diff=0; // int récupérant le différence entre sommet_cible et sommet_cour
  while(sommet_cour != -1) // Tant que sommet_cour n'est pas -1 (donc que sommet_cible n'est pas la case d'origine id)
  {
    diff = sommet_cible - sommet_cour; // On calcule diff
    if (diff == 1){ // Cas où sommet_cible est au dessus de sommet_cour
      chemin.push_back(new std::pair<bool,bool>(0,0));
    }
    else if (diff == -1){ // Cas où sommet_cible est au dessous de sommet_cour
      chemin.push_back(new std::pair<bool,bool>(1,0));
    }
    else if (diff == m_h){ // Cas où sommet_cible est à droite de sommet_cour
      chemin.push_back(new std::pair<bool,bool>(0,1));
    }
    else if (diff == -m_h){ // Cas où sommet_cible est à gauche de sommet_cour
      chemin.push_back(new std::pair<bool,bool>(1,1));
    }
    sommet_cible = sommet_cour; // On met à jour sommet_cible...
    sommet_cour = antec.at(sommet_cour); // et sommet_cour
  }
  std::reverse(chemin.begin(),chemin.end());
  return chemin; // On retourne le chemin
}

