/*
 * UGUILabel.h
 *
 *  Created on: Aug. 11, 2020
 *      Author: Michel
 */

#ifndef INCLUDE_UGUILABEL_H_
#define INCLUDE_UGUILABEL_H_

#include "UGUI_Positionable.hpp"
#include "UGUIComponent.h"

#include <SFML/Graphics/Text.hpp>

class UGUI_Label: public UGUI_Component, public UGUI_Positionable {
	public:
		/*
		 *
		 */
		UGUI_Label(int ruleSet, const std::string &name = "UI Panel", const std::string& = "default");
		/*
		 *
		 */
		virtual ~UGUI_Label();
		/*
		 *
		 */
		virtual void display();
		/*
		 *
		 */
		virtual void update(float);
		/*
		 * Sets the text of this object.
		 */
		virtual void setText(const std::string&);
		/*
		 * Sets the maximum length in characters between line splits. This must be set BEFORE using setText.
		 */
		virtual void setMaxlen(unsigned int maxLength);
		/*
		 *
		 */
		virtual void setCharacterSize(float);
		/*
		 *
		 */
		virtual unsigned int getMaxLen() const {
			return this->mLen;
		}
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
		virtual sf::Text& getTextObject() {
			return this->mString;
		}
	private:
		/*
		 *
		 */
		virtual void setSize(float, float, bool logical);
		/*
		 *
		 */
		virtual sf::Vector2f getSize(bool);
	protected:
		sf::Text mString;
		unsigned int mLen;
};

#endif /* INCLUDE_UGUILABEL_H_ */
