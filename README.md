# TRV
#Dependances: gcc, c++11, libxml2, libxml++-2.6, glibmm-2.4

***********************************************************************************
************************************   TO DO   ************************************
***********************************************************************************

- Amélioration de l'algorithme génétique mono agent pour pathfinding multi agent
- Rédaction du compte rendu de stage
- Election du leader, idée : Demande de déplacement d'un groupe d'unités, on parcourt le vecteur pour connaitre l'unité
 avec la plus petite distance de Manhattan -> Le leader, à chaque autre unité du vecteur, on regarde les cases adjacentes pour voir 
si le leader y est, si il n'y est pas on regarde si une unité suivant le leader y est, sinon une unité suivant une unité etc...
Et on fait un A Star sur l'unité jusqu'à l'unité qu'elle doit suivre jusqu'au but


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
