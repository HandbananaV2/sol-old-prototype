/*
 * UGUIPanel.cpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: Michel
 */
#include "UGUI.h"
#include "UGUIPanel.h"
#include <iostream>
#include <SFML/Graphics.hpp>

/*
 *
 */
UGUI_Panel::UGUI_Panel(int ruleSet, const std::string &name) :
		UGUI_Component(ruleSet, name) {
}
/*
 *
 */
UGUI_Panel::~UGUI_Panel() {
}
/*
 *
 */
std::string UGUI_Panel::getType() const {
	return UGUI_Component::getType() + ".UGUI_Panel";
}
/*
 *
 */
void UGUI_Panel::display() {
	if (!this->isVisible())
		return;

	if ((m_rules & GUI_DRAW_CHILDREN_BEFORE) || m_rules == GUI_DEFAULT)
		this->display_children();

	UGUI::Config::RenderHandle->draw(this->m_sprites[0]);

	if (!(m_rules & GUI_DRAW_CHILDREN_BEFORE) || m_rules == GUI_DEFAULT)
		this->display_children();
}

/*
 *
 */
const sf::Texture* UGUI_Panel::getTexture(unsigned int index) {
	return &m_surfaces[index];
}
/*
 *
 */
void UGUI_Panel::bindSurface(int surface, const sf::Texture &index) {
	this->m_surfaces[surface] = index;
}
/*
 *
 */
void UGUI_Panel::bindSurface(int t, int) {
	this->m_sprites[0].setTexture(m_surfaces[t]);
}
/*
 *
 */
void UGUI_Panel::update(float float1) {
	if (!this->isEnabled())
		return;

	if (m_rules & GUI_UPDATE_CHILDREN_BEFORE)
		this->update_children(float1);

	if (!(m_rules & GUI_UPDATE_CHILDREN_BEFORE))
		this->update_children(float1);
}
/*
 *
 */
void UGUI_Panel::setPosition(float float1, float float2) {
	this->m_boundaries.left = float1;
	this->m_boundaries.top = float2;

	this->m_sprites[0].setPosition(float1, float2);
}
/*
 *
 */
sf::Vector2f UGUI_Panel::getPosition() {
	return sf::Vector2f(this->m_boundaries.left, this->m_boundaries.top);
}
/*
 *
 */
void UGUI_Panel::setSize(float float1, float float2, bool logical) {
	// Logical means we're not actually changing the render size.
	if (!logical) {
		if (!this->m_sprites[0].getTexture())
			std::cout << "UGUI_Panel::setSize(): The physical size of this object's texture cannot be set because a texture has yet to be defined." << std::endl;
		else {
			this->m_sprites[0].setScale(this->m_sprites[0].getGlobalBounds().left / float1, this->m_sprites[0].getGlobalBounds().left / float2);
		}
	}
	// Set the logical size for the object. This is not always the same as the
	// physical size of the texture.
	this->m_boundaries.width = float1;
	this->m_boundaries.height = float2;
}
/*
 *
 */
sf::Vector2f UGUI_Panel::getSize(bool logical) {
	if (logical)
		return sf::Vector2f(this->m_sprites[0].getLocalBounds().width, this->m_sprites[1].getLocalBounds().height);
	else
		return sf::Vector2f(this->m_boundaries.left, this->m_boundaries.height);
}
