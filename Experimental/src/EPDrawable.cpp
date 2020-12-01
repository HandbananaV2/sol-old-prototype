/*
 * EPDrawable.cpp
 *
 *  Created on: Jun. 23, 2020
 *      Author: Michel
 */

#include "EPDrawable.h"
#include "EPBase.h"

#include <iostream>
/*
 *
 */
EPDrawable::EPDrawable(const std::string &allocator) :
    EPBasicObject(allocator)
{

    this->mDebugSprite.setTexture(ExperimentalProject::G_DebugTextureR);
}
/*
 *
 */
EPDrawable::~EPDrawable()
{
}
/*
 *
 */
void EPDrawable::draw()
{
    //
    // These boxes are only present if the debugger is enabled.
    //

    ExperimentalProject::G_MainWindow->draw(mSprite);

    if(ExperimentalProject::G_DebuggerEnabled)
        ExperimentalProject::G_MainWindow->draw(mDebugSprite);
}
/*
 *
 */
void EPDrawable::update(float float1)
{
}
/*
 *
 */
const std::string EPDrawable::getType() const
{
    return EPBasicObject::getType() + ".EPDrawable";
}
/*
 *
 */
void EPDrawable::move(float x, float y)
{
    this->mBounadries.left += x;
    this->mBounadries.top += y;
    this->mDebugSprite.move(sf::Vector2f(x,y));
    this->mSprite.move(sf::Vector2f(x, y));
}
/*
 *
 */
void EPDrawable::setPosition(float x, float y)
{
    this->mBounadries.left = x;
    this->mBounadries.top = y;

    this->mDebugSprite.setPosition(sf::Vector2f(this->mBounadries.left, this->mBounadries.top));
    this->mSprite.setPosition(sf::Vector2f(this->mBounadries.left, this->mBounadries.top));
}
/*
 *
 */
void EPDrawable::setSize(float x, float y)
{
    this->mBounadries.width = x;
    this->mBounadries.height = y;

    if (!mSprite.getTexture())
    {
        std::cout << "EPDrawable::setSize(): Change size of object w/o sprite is not permitted." << std::endl;
        return;
    }

    this->mDebugSprite.setScale(sf::Vector2f(x / mSprite.getLocalBounds().width, y / mSprite.getLocalBounds().height));
    this->mSprite.setScale(sf::Vector2f(x / mSprite.getLocalBounds().width, y / mSprite.getLocalBounds().height));
}
/*
 *
 */
sf::Vector2f EPDrawable::getSize() const
{
    return sf::Vector2f(this->mBounadries.width, this->mBounadries.height);
}
/*
 *
 */
sf::Vector2f EPDrawable::getPosition() const
{
    return sf::Vector2f(this->mBounadries.left, this->mBounadries.top);
}
/*
*
*/
void EPDrawable::setDebugScheme(unsigned char d)
{
    switch(d)
    {
    default:
    case 'r':
        this->mDebugSprite.setTexture(ExperimentalProject::G_DebugTextureR);
        break;

    case 'g':
        this->mDebugSprite.setTexture(ExperimentalProject::G_DebugTextureG);
        break;

    case 'b':
        this->mDebugSprite.setTexture(ExperimentalProject::G_DebugTextureB);
        break;


    case 'p':
        this->mDebugSprite.setTexture(ExperimentalProject::G_DebugTextureP);
        break;

    case 'y':
        this->mDebugSprite.setTexture(ExperimentalProject::G_DebugTextureY);
        break;


    case 'o':
        this->mDebugSprite.setTexture(ExperimentalProject::G_DebugTextureO);
        break;

    case 'c':
        this->mDebugSprite.setTexture(ExperimentalProject::G_DebugTextureC);
        break;
    }
}
