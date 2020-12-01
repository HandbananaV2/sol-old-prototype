/*
 * UGUI_Displayable.hpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: Michel
 */

#ifndef INCLUDE_UGUI_POSITIONABLE_HPP_
#define INCLUDE_UGUI_POSITIONABLE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "UGUI.h"

class UGUI_Positionable {
	public:
		virtual ~UGUI_Positionable() {
		}
		/*
		*
		*/
		virtual void setPosition(float, float) = 0;
		/*
		*
		*/
		virtual sf::Vector2f getPosition() = 0;
		/*
		*
		*/
		virtual void setSize(float, float, bool logical) = 0;
		/*
		*
		*/
		virtual sf::Vector2f getSize(bool) = 0;
	protected:
		/*
		*
		*/
		sf::FloatRect m_boundaries;
};

#endif /* INCLUDE_UGUI_POSITIONABLE_HPP_ */
