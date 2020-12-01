/*
 * UGUIButton.h
 *
 *  Created on: Aug. 15, 2020
 *      Author: Michel
 */

#ifndef INCLUDE_UGUIBUTTON_H_
#define INCLUDE_UGUIBUTTON_H_

#include <SFML/Graphics.hpp>

#include "UGUIComponent.h"
#include "UGUI_Displayable_I.hpp"
#include "UGUI_Positionable.hpp"

class UGUI_Button: public UGUI_Component, public UGUI_Displayable_I, public UGUI_Positionable {
	public:
		enum ButtonState {
			BUTTON_STATE_DEFAULT = 0, BUTTON_STATE_HOVER = 1, BUTTON_STATE_CLICK = 2
		};
		/*
        *
        */
		UGUI_Button(const std::string&, sf::Mouse::Button = sf::Mouse::Button::Left);
		UGUI_Button(const std::string&, sf::Mouse::Button, const std::string& fontId,
                    const std::string& btnText = "button", const float& fontScale = 1.0,  const sf::Color& fillColor = sf::Color::White);
		/*
        *
        */
		virtual ~UGUI_Button();
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
		virtual void setSize(float, float, bool logical);
        /*
        *
        */
		virtual sf::Vector2f getSize(bool);
        /*
        *
        */
		virtual void bindSurface(int, const sf::Texture&);
        /*
        *
        */
		virtual void bindSurface(int, int = 0);
        /*
        *
        */
		virtual const sf::Texture* getTexture(unsigned int index = 0);
        /*
        *
        */
		virtual void changeState(int);
        /*
        *
        */
		virtual void update(float);
        /*
        *
        */
		virtual void display();
        /*
        *
        */
		const sf::Text& getTextObject() const { return mText; }
	private:
		sf::Mouse::Button mType;
		ButtonState mState;
		bool mWaitState;
		sf::Text mText;
		float mFontSize;

};

#endif /* INCLUDE_UGUIBUTTON_H_ */
