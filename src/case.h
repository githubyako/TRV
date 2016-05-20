/*
 * <TRV pathfinding solution using genetic algorithm>
 * Copyright (C) 2016  <copyright Roux Nicolas, Voillemin Théo, Talarmain Corentin>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/*!
 *\file case.h
 *\author Nicolas Roux, Théo Voillemin, Corentin Talarmain
 *\brief  Case's file
 * 
 */

#ifndef CASE_H
#define CASE_H

#include <map>
#include "terrain.h"
#include "contrainte.h"
#include <vector>

/*! \class Case
 * \brief Class representing a square on the map.
 * This class handle the squares on the map.
 */

class Case{
  
private:
  unsigned int m_x; /*!< The absciss of the Case */
  unsigned int m_y; /*!< The ordinate of the Case */
  std::vector<std::pair<Contrainte*,float> >m_contraintes; /*!< The list of Contrainte for the Case*/
  std::vector<Case*> m_cases_vois; /*!< Vector of the neighboors of the Case*/
  bool m_obstacle; /*!< Boolean defining if the Case is an obstacle or not*/
  unsigned int m_somm; /*!< The int corresponding to the vertice of the Case*/
  Terrain * m_terrain; /*!< Pointer to the Terrain corresponding to the Case*/
  
  static unsigned int id_somm; /*!< Static attribute used to give vertices a number*/
  
  // Private Constructors
  
  /*!
   * \brief Default constructor
   * 
   */
  Case();
  
  /*!
   * \brief Copy constructor
   * 
   */
  Case(Case const & _case);
  
public:

  // Constructor
  
  /*!
   * \brief Constructor
   * 
   * \param _x : The absciss of the Case.
   * \param _y : The ordinate of the Case.
   * \param _somm : The integer corresponding to the vertice of the Case.
   * \param terrain : A pointer to the Terrain corresponding to the Case.
   * 
   * Construct the object from the absciss, the ordinate, the vertice and the Terrain.
   * 
   */
  Case(int _x, int _y, int _somm, Terrain * _terrain);
  
  // Getters
  
  /*!
   * \brief Getter of the absciss attribute.
   * 
   * \return The absciss of the Case.
   * 
   * Return the absciss.
   * 
   */
  unsigned int getX() const;
  
  /*!
   * \brief Getter of the ordonate attribute.
   * 
   * \return The ordonate of the Case.
   * 
   * Return the ordonate of the Case.
   * 
   */
  unsigned int getY() const;
  
  /*!
   * \brief Getter of the vertice attribute.
   * 
   * \return The vertice corresponding to the Case.
   * 
   * Return the vertice corresponding to the Case.
   * 
   */
  unsigned int get_sommet() const;
  
  /*!
   * \brief Getter of the Contrainte attribute.
   * 
   * \return The Contrainte value for the Case.
   * 
   * Return the Contrainte value of the Case.
   * 
   */
  float getContrainte(Contrainte* _contrainte) const;
  
  /*!
   * \brief Getter of the Terrain attribute.
   * 
   * \return The Terrain corresponding to the Case.
   * 
   * Return the Terrain corresponding to the Case.
   * 
   */
  const Terrain & getTerrain() const;
  
  /*!
   * \brief Getter of the obstacle boolean
   * 
   * \return true if the Case is an obstacle, false otherwise
   * 
   * 
   */
  bool isObstacle() const;
  
  /*!
   * \brief Getter of the vector of the neighboors
   * 
   * \return The vector containing all the neighboors of the Case
   * 
   */
  const std::vector<Case*>& getVois() const;
  
  // Setteurs
  
  /*!
   * \brief Setter for the obstacle boolean
   * 
   * \param _b : True if the Case become an obstacle, false otherwise.
   * 
   */
  void setObstacle(bool _b);
  
  /*!
   * \brief Setter for the Terrain attribute.
   * 
   * \param _terrain : The new Terrain type for the Case
   * 
   */
  void setTerrain(Terrain* _terrain);
  
  /*!
   * \brief Setter for the Contrainte attribute with a vector
   * 
   * \param _contr : The new vector of Contrainte
   * 
   */
  void setContrainte(std::vector<std::pair<Contrainte*,float> > _contr);
  
  /*!
   * \brief Setter for a Contrainte attribute.
   * 
   * \param _contrainte : A pointer to the new Contrainte.
   * \param _qte : The value for the Contrainte corresponding to the Case.
   * 
   */
  void setContrainte(Contrainte* _contrainte,float _qte);
  
  /*!
   * \brief Setter for the neighboors
   * 
   * \return _case : A new neighboor to add.
   * 
   */
  void add_case_vois(Case* _case);
};
#endif
