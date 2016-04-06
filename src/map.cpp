#include "map.h"

Map::Map()
{

}

Map::Map(const Map& _map)
{

}
/*A MODIFIER

Map::Map(unsigned int _w, unsigned int _h):m_map()
{
  unsigned int casenum=0;
  for(int i=0;i<_w;++i){
    for(int j=0;j<_h;++j){
      m_map.insert( std::pair<unsigned int, Case*>(casenum++,new Case()) );
    }
  }
}*/

Map::~Map()
{

}
