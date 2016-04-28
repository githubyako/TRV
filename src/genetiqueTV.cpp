#include "genetiqueTV.h"

genetiqueTV::genetiqueTV(Map* map, Agent* agent, int arrivee)
:m_map(map), m_agent(agent), m_arrivee(arrivee)
{
  m_depart=agent->getCase()->get_sommet();
}

// const std::vector< Case* > genetiqueTV::recherche_chemin()
// {
//   
// }
