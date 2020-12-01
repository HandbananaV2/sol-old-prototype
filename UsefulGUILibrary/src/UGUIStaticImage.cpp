#include "UGUIStaticImage.h"
/*
*
*/
UGUI_StaticImage::UGUI_StaticImage(const std::string& n) : UGUI_Component(GUI_DEFAULT, n){

}
/*
*
*/
UGUI_StaticImage::~UGUI_StaticImage(){

}
/*
*
*/
void UGUI_StaticImage::setPosition(float float1, float float2) {
	m_boundaries.left = float1;
	m_boundaries.top = float2;

	for (unsigned int x = 0; x < UGUI_TEXTURE_COUNT; x++) {
		this->m_sprites[x].setPosition(float1, float2);
	}
}
/*
*
*/
sf::Vector2f UGUI_StaticImage::getPosition() {
	return sf::Vector2f(m_boundaries.left, m_boundaries.top);
}
/*
*
*/
void UGUI_StaticImage::setSize(float float1, float float2, bool logicalOnly) {
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
sf::Vector2f UGUI_StaticImage::getSize(bool logical) {
	// Logical
	if (logical) {
		return sf::Vector2f(this->m_boundaries.left, this->m_boundaries.top);
	}

	return this->m_sprites[0].getScale();
}
/*
*
*/
void UGUI_StaticImage::bindSurface(int int1, const sf::Texture &t) {
	this->m_surfaces[int1]=t;
}
/*
*
*/
void UGUI_StaticImage::bindSurface(int int1, int index) {
	this->m_sprites[0].setTexture(this->m_surfaces[int1]);
}
/*
*
*/
const sf::Texture* UGUI_StaticImage::getTexture(unsigned int index) {
	return &this->m_surfaces[index];
}
/*
*
*/
void UGUI_StaticImage::display()
{
	if (!this->isVisible())
		return;

	UGUI::Config::RenderHandle->draw(m_sprites[0]);
}
/*
*
*/
void UGUI_StaticImage::update(float)
{

}
/*
*
*/
std::string UGUI_StaticImage::getType() const
{
    return UGUI_Component::getType() + ".UGUIStaticImage";
}
