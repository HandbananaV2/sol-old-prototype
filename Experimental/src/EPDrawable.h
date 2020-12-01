/*
 * EPDrawable.h
 *
 *  Created on: Jun. 23, 2020
 *      Author: Michel
 */

#ifndef EPDRAWABLE_H_
#define EPDRAWABLE_H_

#include "EPBasicObject.h"
#include <SFML/Graphics.hpp>

class EPDrawable: public EPBasicObject
{
public:
    EPDrawable(const std::string&);
    virtual ~EPDrawable();
    /*
     *
     */
    virtual void draw();
    /*
     *
     */
    virtual void update(float);
    /*
     *
     */
    virtual const std::string getType() const;
    /*
     *
     */
    virtual void move(float x, float y);
    virtual void setPosition(float x, float y);
    virtual void setSize(float x, float y);
    virtual sf::Vector2f getSize() const;
    virtual sf::Vector2f getPosition() const;
    /*
     *
     */
    virtual const sf::FloatRect& getBoundaries() const
    {
        return mBounadries;
    }
    /*
    *
    */
    virtual void setDebugScheme(unsigned char);
protected:
    sf::Sprite mSprite;
    sf::Sprite mDebugSprite;
    sf::FloatRect mBounadries;
};

#endif /* EPDRAWABLE_H_ */
