/*
 * UGUI_Displayable_I.hpp
 *
 *  Created on: Aug. 11, 2020
 *      Author: Michel
 */

#ifndef INCLUDE_UGUI_DISPLAYABLE_I_HPP_
#define INCLUDE_UGUI_DISPLAYABLE_I_HPP_

#include <SFML/Graphics.hpp>
#include "UGUI.h"

class UGUI_Displayable_I {
	public:
		virtual ~UGUI_Displayable_I() {
		}
		/*
		*
		*/
		virtual void bindSurface(int, const sf::Texture&) = 0;
		/*
		*
		*/
		virtual void bindSurface(int, int = 0) = 0;
		/*
		*
		*/
		virtual const sf::Texture* getTexture(unsigned int index = 0) = 0;
	protected:
		/*
		*
		*/
		sf::Sprite m_sprites[UGUI_TEXTURE_COUNT];
		/*
		*
		*/
		sf::Texture m_surfaces[UGUI_TEXTURE_COUNT];
};

#endif /* INCLUDE_UGUI_DISPLAYABLE_I_HPP_ */
