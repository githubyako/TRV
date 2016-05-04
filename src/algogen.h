#ifndef ALGOGEN_H
#define ALGOGEN_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <ctime>
#include <cstdlib>
#include <math.h>

#include "sousminion.h"
#include "surminion.h"
#include "str_exception.h"
#include "map.h"

class Algogen{

private:
	int m_mapW, m_mapH;
	std::map<int, Case*> const * m_sommets;
	std::vector<Case *>m_orig,m_cible;
	std::vector<SurMinion*> m_pop;
	std::vector<SousMinion*> m_sousMinions;
	std::vector<const Unite*> m_unite;
	std::vector<std::vector<Case*> > m_zones;
	SurMinion* m_president, *m_superman;
	unsigned int m_popsize, m_taillemax;
	unsigned int m_nbkids;
	unsigned int m_lowestElite;
	unsigned int m_nbkidstotal, m_nbIterations;
	float m_manhattanImportance; // importance relative de la distance de manhattan 
	float m_mutationRatio; // ratio de mutation par individu et par génération
	float m_popToMutate; // ratio de population sujette à mutation à chaque génération
	unsigned int m_nbAjouts;
	float m_ratioSupprs, m_ratioModifs; // ratios INITIAUX (par mutation et par rapport au genome total de l'indivudu) d'ajouts de chromosomes, de suppr de chromosomes, d'altérations de chromosomes
	float m_ratioElitism; // ratio de meilleurs individus dont le génome n'est ni modifié ni amputé de chromosomes
	float m_cullRatio; // ratio d'individus éliminés en dehors des élites par génération
	std::vector<float> m_generationTotalFitness;
	
	void initPop(int _caseSource, int _caseCible,const Unite * _typeAgent);
	
	
public:
	Algogen(int map_w, int map_h,std::map<int, Case*> const * _sommets, unsigned int _popsize, float _manhattanImportance, float _mutationRatio, 
		  float _popToMutate, unsigned int _nbAjouts, float _ratioSupprs,float _ratioModifs, float _ratioElitism, float _cullRatio, unsigned int _nbkids);
	~Algogen();


	
	void addDeplacement(int _idAgent, int _caseSource, int _caseCible, const Unite * _typeAgent);
	void iterate();

	void crossover(SurMinion* _parent0, SurMinion* _parent1, SurMinion* _parent2);
	void mutatePop();
	void cull();
	void evaluate(SurMinion* _minion);
// 	void show() const;
// 	unsigned int get_nb_goodResults();
// 	unsigned int get_pres_nbdeplace();
};

#endif
