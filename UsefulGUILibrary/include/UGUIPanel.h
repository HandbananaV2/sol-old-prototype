/*
 * UGUIPanel.h
 *
 *  Created on: Aug. 5, 2020
 *      Author: Michel
 */

#ifndef INCLUDE_UGUIPANEL_H_
#define INCLUDE_UGUIPANEL_H_

#include "UGUI_Positionable.hpp"
#include "UGUIComponent.h"
#include "UGUI_Displayable_I.hpp"

class UGUI_Panel: public UGUI_Component, public UGUI_Positionable, public UGUI_Displayable_I {
	public:
        /*
        *
        */
		UGUI_Panel(int ruleSet, const std::string &name = "UI Panel");
        /*
        *
        */
		virtual ~UGUI_Panel();
        /*
        *
        */
		virtual std::string getType() const;
        /*
        *
        */
		virtual const sf::Texture* getTexture(unsigned int index = 0);
        /*
        *
        */
		virtual void bindSurface(int surface, const sf::Texture&);
        /*
        *
        */
		virtual void bindSurface(int, int = 0);
        /*
        *
        */
		virtual void display();
        /*
        *
        */
		virtual void update(float);
        /*
        *
        */
		virtual void setPosition(float, float);
        /*
        *
        */
		virtual sf::Vector2f getPosition();
        /*
        *
        */
		virtual void setSize(float, float, bool);
        /*
        *
        */
		virtual sf::Vector2f getSize(bool);
};

#endif /* INCLUDE_UGUIPANEL_H_ */
