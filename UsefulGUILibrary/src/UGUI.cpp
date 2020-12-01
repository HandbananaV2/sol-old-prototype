/*
 * UGUI.cpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: Michel
 */
#include "UGUI.h"
#include <exception>
#include <stdexcept>
#include <SFML/Graphics.hpp>

using namespace UGUI;
using namespace UGUI::Config;
/*
*
*/
std::map<std::string, sf::Font*> UGUI::Config::UiFonts;
/*
*
*/
sf::RenderWindow *UGUI::Config::RenderHandle = nullptr;
/*
*
*/
void UGUI::Config::SetRenderTarget(sf::RenderWindow *hndle) {
	UGUI::Config::RenderHandle = hndle;
}
/*
*
*/
void UGUI::Config::SetFontFaces(const std::string &allocator, sf::Font *uiFont) {
	UiFonts[allocator] = uiFont;
}
/*
*
*/
const sf::Font* UGUI::Config::GetFontFace(const std::string &identifier) {
	try {
		return UiFonts[identifier];
	} catch (std::out_of_range &e) {
		throw std::logic_error("UGUI::Config::GetFontFace(): Unable to locate font pointer : " + identifier);
	}
}
