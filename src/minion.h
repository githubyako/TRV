#ifndef MINION_H
#define MINION_H
#include <vector>
#include <iostream>
#include <math.h>
#include "case.h"
#include "unite.h"

class Minion{
private:
  int m_idAgent, m_caseCible;
  static unsigned int m_incrID;
  std::vector<std::pair<bool,bool> *> m_genome;
  const Unite* m_unite;
  float m_fitness;
  bool m_vaChemin;
  unsigned int m_manhattan, m_id,m_sommetfinal;
  
public:
  Minion(std::vector<std::pair<bool,bool> *> const & _genome, const Unite* _unite, int _idAgent, int _caseCible);
  Minion(Minion const & _minion);
  ~Minion();
  
  void mutate(unsigned int _nbAjouts, float _ratioSupprs,float _ratioModifs);
  void mutateElite(unsigned int _nbAjouts,float _ratioModifs);
  
  unsigned int getManhattan() const;
  bool getVaChemin() const;
  float const & getFitness() const;
  std::vector<std::pair<bool,bool> *> const & getGenome() const;
  unsigned int getGenomeSize() const;
  std::pair< bool, bool > * getChromosome(unsigned int _pairNumber) const;
  unsigned int getID() const;
  unsigned int getSF() const;
  int getIDAgent() const;
  int getCaseCible() const;
  const Unite* getUnite() const;

  void setFitness(float _fitness);
  void setVaChemin(bool _vaChemin);
  void setManhattan(unsigned int _manhattan);
  void setGenome( std::vector<std::pair<bool,bool> *> const & _genome);
  void setSommetFinal(unsigned int _sommet);
  void popfront();
};

#endif