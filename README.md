# TRV
#Dependancies: gcc, c++11, libxml2, libxml++-2.6, glibmm-2.4

***********************************************************************************
********************************   HOW TO USE   ***********************************
***********************************************************************************
-Write an XML file describing your game rules in compliance with the DTD
-Write a txt file describing the map:
 -first line is two unsigned integers: map width and map height (origin is bottom left corner: 0,0)
 -following lines each describe a tile that you want to be different from the default settings:
    [x(unsigned int)] [y(unsigned int)] [terrain name(string without spaces)] [contrainte 1(string)]:[value 1(float)];[contrainte n]:[value n] [is obstacle(bool)]
  -note the space between the fields. It means that if you do not want to specify any contrainte, but want to set a tile to be impassable, you must put THREE spaces after the terrain name and before the is_obstacle boolean: two for separations and one for empty field.
-Include src/controller.h
-Create a controller object and get its pointer: Controller* controller = Controller::create();
-Initiate the xml rules with: controller->initiateRules("../regle.xml");
-Initiate the map with: controller->initiateMap("../map.txt");
-Create an instance of the pathfinding algorithm with: controller->create_algogen();
-From now on all methods of Controller are available to you. Just ensure that you don't ask a path for an agent that you didn't create.
-The most useful methods will be
 controller->creer_agent(x,y,name,id)
 controller->supprimer_agent(id)
 controller->proch_case(id) ==> returns a pair of ints (x,y) that is the proposed next tile
 controller->deplacement_agent(id,x,y) ==>actually moves the unit to the (x,y) tile
           example:  controller->deplacement_agent(1,controller->proch_case(1).first,controller->proch_case(1).second);
 tic(); starts the calculations.
 toc(); interrupts the calculations. Note that coherent behavior are only guaranteed if you toc() before asking a proch_case or a deplacement_agent
 Controller::delete_controller();
 
***********************************************************************************
************************************   XML   **************************************
***********************************************************************************
- Compliance with the DTD is checked on initialization
- <regle> </regle> : wraps all the rules: <contraintes>, <terrains> and <unites>
- <contrainte /> : can be seen as resources available on a tile. Used to define if a unit can go through/stay on a tile. Has a name. [DEPRECATED]
- <terrain_defaut /> represents the default ground type. Has a name, and a value for each contrainte.
- <terrain /> : represents a ground type. Has a name, and a value for each contrainte.
- <unite /> : Represents a unit type (eg Cavalry). Has a name, a specific time to cross each terrain (set high value for uncrossable terrains), and a value for each contrainte

***********************************************************************************
************************************   TO DO   ************************************
***********************************************************************************

- rapport


***********************************************************************************
************************************   DONE   *************************************
***********************************************************************************

- Recherche et mise en place des librairies C++ nécessaires.
- Modélisation des classes représentant les agents du pathfinding.
- Représentation de la carte.
- Communication des règles du jeu entre l'interface et nous. (XML et DTD)
- Représentation UML de notre projet
- Définition du format d'initialisation de la carte
- Transfert des informations entre interface et pathfinding par bibliothèque.
- Exemple de map en fichier .txt
- Ecriture des classes Unité, Agent, Map, Case, Terrain, COntrainte, Controller
- Fonction pour parser le fichier map.txt pour en créer une map (parsing fait, il reste à créer la map)
- Création d'un exemple pour travail sur algos pathfinding: XML_REGLES(done), INIT_MAP(WIP), CREATE_AGENT(en att),SUPPR_AGENT(en att), DEPLACE_AGENT(en att), SET_OBSTACLE(en att), DEMANDE_CHEMIN(en att)
- Réflexion sur le mono pathfinding à coût variable (dijkstra, A*)
- Écriture des mono pathfinding à coût variable (dijkstra, A*)
- Se renseigner sur les différentes méthodes stochastiques (Algorithme de Monte-Carlo et algorithme génétique).
- Écriture d'un algorithme génétique pour pathfinding mono agent
- Gestion des conflits via un vecteur de sommet et temps
