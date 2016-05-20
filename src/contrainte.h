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
 *\file contrainte.h
 *\author Nicolas Roux, Théo Voillemin, Corentin Talarmain
 *\brief  Contrainte's file
 * 
 */

#ifndef CONTRAINTE_H
#define CONTRAINTE_H
#include <string>

/*! \class Contrainte
 * \brief Class representing a Contrainte
 * This class handle the Contrainte
 */

class Contrainte{
private:
  std::string m_nom; /*!< Name of the Contrainte */
  
  // Constructeurs : private pour rendre inaccessible
  
  /*!
   * \brief Default constructor
   * 
   */
  Contrainte();
  
  /*!
   * \brief Copy constructor
   * 
   */
  Contrainte(Contrainte const & _contrainte); 
public:
  
  // Constructor
  /*!
   * \brief Constructor.
   * 
   * \param _nom : Name of the Contrainte.
   */
  Contrainte(std::string const & _nom); // seul constructeur qui servira
  
  // Destructor
  
  /*!
   * \brief Destructor
   */
  ~Contrainte();
  
  // Getter
  /*!
   * \brief Getter of the Contrainte's name attribute.
   */
  std::string const & getNom() const;
  
};
#endif
