/*
 * UGUILabel.cpp
 *
 *  Created on: Aug. 11, 2020
 *      Author: Michel
 */

#include "UGUILabel.h"
#include "UGUIExceptions.h"
#include "UGUI.h"
#include <iostream>

/*
 *
 */
UGUI_Label::UGUI_Label(int ruleSet, const std::string &name, const std::string &fontId) :
		UGUI_Component(ruleSet, name), mLen(64) {
	//
	this->mString.setFont(*UGUI::Config::GetFontFace(fontId));
}
/*
 *
 */
UGUI_Label::~UGUI_Label() {
}
/*
 *
 */
void UGUI_Label::display() {
	if (!this->isVisible())
		return;

	UGUI::Config::RenderHandle->draw(mString);
}
/*
 *
 */
void UGUI_Label::update(float float1) {

}
/*
 *
 */
void UGUI_Label::setText(const std::string &allocator) {
	std::string tmp = allocator;
	unsigned int cnt = allocator.size() / mLen;

	for (unsigned int x = 0; x < cnt; x++) {
		tmp = tmp.insert(x * mLen, "\n");
	}

	if (allocator.size() % mLen) {
		tmp = tmp.insert( mLen * cnt, "\n" );
	}

	mString.setString(tmp);
}
/*
 *
 */
void UGUI_Label::setMaxlen(unsigned int maxLength) {
	mLen = maxLength;
}
/*
 *
 */
void UGUI_Label::setCharacterSize(float f1) {
	mString.setCharacterSize(f1);
}
/*
 *
 */
void UGUI_Label::setPosition(float float1, float float2) {
	this->mString.setPosition(float1, float2);
}
/*
 *
 */
sf::Vector2f UGUI_Label::getPosition() {
	return sf::Vector2f(this->m_boundaries.left, this->m_boundaries.top);
}
/*
 *
 */
void UGUI_Label::setSize(float float1, float float2, bool logical) {
	throw UGUI_UnimplementedFunctionCall("UGUI_Label::setSize(f,f,b): Unimplemented function call.");
}
/*
 *
 */
sf::Vector2f UGUI_Label::getSize(bool bool1) {
	throw UGUI_UnimplementedFunctionCall("UGUI_Label::getSize(): Unimplemented function call.");
}
