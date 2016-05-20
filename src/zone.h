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
 *\file zone.h
 *\author Nicolas Roux, Théo Voillemin, Corentin Talarmain
 *\brief Zone's file
 * 
 */

#ifndef ZONE_H
#define ZONE_H

#include "minion.h"
#include "surminion.h"


/*! \class Zone
 * \brief Class representing a Zone, group of tiles and a leader to follow
 * This class permit to reduice number of agent to treat in the genetic algorithm if a group of near agent had the same goal.
 */

class Zone {
private:
  static unsigned int m_incrID; /*!< Auto increment value for all ID.*/
  unsigned int m_numero; /*!< ID of the Zone.*/
  unsigned int m_caseOrig; /*!< Value of the beginning tiles of the leader.*/
  unsigned int m_caseFin; /*!< Value of the ending tiles of the leader.*/
  unsigned int m_leader; /*!< ID of the leader.*/
  std::vector<unsigned int> m_cases; /*!< Vector with all tiles of the Zone*/
  
public:
  
  /*! \brief Constructor
   * 
   * Construct a Zone
   * 
   * \param _caseOrig : Value of the beginning tiles of the leader.
   * \param _leader : Value of the ending tiles of the leader.
   * \param _cases : Vector with all tiles of the Zone.
   * \param _caseFin : Value of the endeing tiles of the leader.
   */
  
  Zone(unsigned int _caseOrig, unsigned int _leader, const std::vector<unsigned int> _cases, unsigned int _caseFin);
  
  
  /*! \brief Getter of m_caseOrig
   * 
   * \return The value of m_caseOrig
   */

  unsigned int get_orig() const;
  
  
  /*! \brief Getter of m_caseFin
   * 
   * \return The value of m_caseFin
   */
    
  unsigned int get_fin() const;
  
  
  /*! \brief Getter of m_leader
   * 
   * \return The value of m_leader
   */
  
  unsigned int get_leader() const;
  
  
  /*! \brief Getter of m_cases
   * 
   * \return The vector m_cases
   */
  
  const std::vector<unsigned int> &  get_cases() const;
  
  
  /*! \brief Destructor
   * 
   * Destruct the instance of Zone
   */
  
  ~Zone();
};

#endif
