/*
 * UGUIButton.cpp
 *
 *  Created on: Aug. 15, 2020
 *      Author: Michel
 */

#include "UGUIButton.h"
#include "UGUI.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include <math.h>

/*
*
*/
UGUI_Button::UGUI_Button(const std::string &allocator, sf::Mouse::Button type) :
		UGUI_Component(GUI_DEFAULT, allocator), mType(type), mState(BUTTON_STATE_DEFAULT), mWaitState(false), mFontSize(0) {
}
/*
*
*/
UGUI_Button::UGUI_Button(const std::string& allocator, sf::Mouse::Button type,
                         const std::string& fontId,
                         const std::string& btnText,  const float& fontScale, const sf::Color& fillColor) :
        UGUI_Component(GUI_DEFAULT, allocator), mType(type), mState(BUTTON_STATE_DEFAULT), mWaitState(false), mFontSize(fontScale) {

    this->mText.setFillColor(fillColor);
    this->mText.setFont(*UGUI::Config::GetFontFace(fontId));
    this->mText.setString(btnText);

}
/*
*
*/
UGUI_Button::~UGUI_Button() {

}
/*
*
*/
void UGUI_Button::setPosition(float float1, float float2) {
	m_boundaries.left = float1;
	m_boundaries.top = float2;

	for (unsigned int x = 0; x < UGUI_TEXTURE_COUNT; x++) {
		this->m_sprites[x].setPosition(float1, float2);
	}
}
/*
*
*/
sf::Vector2f UGUI_Button::getPosition() {
	return sf::Vector2f(m_boundaries.left, m_boundaries.top);
}
/*
*
*/
void UGUI_Button::setSize(float float1, float float2, bool logicalOnly) {
	if (logicalOnly) {
		this->m_boundaries.width = float1;
		this->m_boundaries.height = float2;
		return;
	}

	this->m_boundaries.width = float1;
	this->m_boundaries.height = float2;

	for (unsigned int x = 0; x < UGUI_TEXTURE_COUNT; x++) {
		this->m_sprites[x].setScale(this->m_sprites[x].getGlobalBounds().width / float1, this->m_sprites[x].getGlobalBounds().height / float2);
	}

}
/*
*
*/
sf::Vector2f UGUI_Button::getSize(bool logical) {
	// Logical
	if (logical) {
		return sf::Vector2f(this->m_boundaries.left, this->m_boundaries.top);
	}

	return this->m_sprites[0].getScale();
}
/*
*
*/
void UGUI_Button::bindSurface(int int1, const sf::Texture &t) {
	this->m_surfaces[int1] = t;
}
/*
*
*/
void UGUI_Button::bindSurface(int int1, int index) {
	this->m_sprites[index].setTexture(this->m_surfaces[int1]);
}
/*
*
*/
const sf::Texture* UGUI_Button::getTexture(unsigned int index) {
	return &this->m_surfaces[index];
}
/*
*
*/
void UGUI_Button::changeState(int int1) {
	this->m_sprites[0].setTexture(this->m_surfaces[int1]);
}
/*
*
*/
void UGUI_Button::update(float float1) {
    if( ! this->isEnabled() ) return;
    // Text is optional
    if ( this->mFontSize != 0 ) {
        // Set the font scale
        this->mText.setCharacterSize((this->m_boundaries.height / 2) * mFontSize);
        // The position the button(centre).
        float tBoundsL = this->m_boundaries.left + this->m_boundaries.width / 2;
        float tBoundsT = this->m_boundaries.top + this->m_boundaries.height / 2;
        // The formula to correct the positioning.
        float tWidth  =  (this->mFontSize * 2) + (this->mText.getGlobalBounds().width)  / 2;
        float tHeight =  (this->mFontSize * 4) + (this->mText.getGlobalBounds().height) / 2;
        // Centre the font size.
        this->mText.setPosition( tBoundsL - tWidth , tBoundsT - tHeight );
    }
	//
	if (sf::Mouse::isButtonPressed(this->mType) && !mWaitState) {
		//
		const sf::Vector2i mx = sf::Mouse::getPosition(*UGUI::Config::RenderHandle);
		const sf::FloatRect mp(mx.x, mx.y, 16, 16);

		if (mp.intersects(this->m_boundaries)) {
			mWaitState = true;
			this->event(UGUI::UGUI_EventId::EVENT_BUTTON_PRESSED, { UGUI::UGUI_EventId::EVENT_BUTTON_PRESSED, 1, this });
			this->changeState(BUTTON_STATE_CLICK);
		}
	}
	//
	if (!sf::Mouse::isButtonPressed(this->mType) && mWaitState) {
		mWaitState = false;
		this->event(UGUI::UGUI_EventId::EVENT_BUTTON_RELEASED, { UGUI::UGUI_EventId::EVENT_BUTTON_RELEASED, 0, this });
		this->changeState(BUTTON_STATE_DEFAULT);
	}
}
/*
*
*/
void UGUI_Button::display() {
    if( !this->isVisible()) return;

    UGUI::Config::RenderHandle->draw(this->m_sprites[0]);
    UGUI::Config::RenderHandle->draw(this->mText);
}
