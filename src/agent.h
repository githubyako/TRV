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
 *\file agent.h
 *\author Nicolas Roux, Théo Voillemin, Corentin Talarmain
 *\brief  Agent's file
 * 
 */

#ifndef AGENT_H
#define AGENT_H

#include "unite.h"
#include "case.h"

/*! \class Agent
 * \brief Class representing an Agent moving on the map.
 * This class handle the Agents moving on the map.
 */

class Agent{
  
private:
  int m_id; /*!< Identifier of an agent.*/
  float m_multiplicateur_v; /*!< Speed multiplier of the agent(exhaust, moral, ...).*/
  Unite *m_unite; /*!< Pointer to the unit he belongs to.*/
  Case *m_case; /*!< Pointer to the Case corresponding to his position.*/

  
public:

  /*!
   * \brief Constructor
   * 
   * Construct an Agent with an identifier, a pointer to a Case and a pointer to a Unite.
   * 
   * \param _iden : The identifier of the Agent.
   * \param _c : The Case corresponding to the Agent's position.
   * \param _u : The Unite corresponding to the Agent's type.
   */
  Agent(int _iden, Case* _c, Unite* _u);
  

    /*!
   * \brief Getter of the ID attribute.
   *
   * \return The Agent's ID.
   * 
   * Return the ID of the Agent.
   *
   */
   
  int getId() const;
  
  
    /*!
   * \brief Getter of the Agent's speed multiplier attribute.
   * 
   * \return the Agent's speed multiplier.
   * 
   * Return the Agent's speed multiplier.
   * 
   */
   
  float getMultiplicateurV() const;
  
  
    /*!
   * \brief Getter of the Case attribute.
   * 
   * \return A constant pointer to the Case corresponding to the Agent's position.
   * 
   * Return a constant pointer to the Case corresponding to the Agent's position.
   * 
   */
   
  const Case* getCase() const;
  
  
    /*!
   * \brief Getter of the Agent's Unite attribute.
   * 
   * \return  the Agent's Unite.
   * 
   * Return the Agent's Unite.
   * 
   */
  
  const Unite* getUnite() const;
  
  
 /*!
   * \brief Setter of the Case attribute.
   * 
   * \param _c : A pointer to the new Case for the Agent.
   * 
   * Modify the Agent's Case.
   * 
   */
 
  void setCase(Case* _c);
  
  
    /*!
   * \brief Setter of the Unite attribute
   * 
   * \param _u : A pointer to the new Unite for the Agent.
   * 
   * Modify the Agent's Unite.
   * 
   */
   
  void setUnite(Unite* _u);  
  
};
#endif
