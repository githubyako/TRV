#ifndef DEPLACEMENT
#define DEPLACEMENT
#include <vector>
class deplacement {
private:
  std::vector<std::pair<bool,bool>> m_chemin;
public:
  deplacement(std::vector< std::pair< bool, bool > > chemin);
};
#endif