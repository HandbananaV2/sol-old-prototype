/*
 * EPPlayerObject.h
 *
 *  Created on: Jun. 19, 2020
 *      Author: Michel
 */

#ifndef EPPLAYEROBJECT_H_
#define EPPLAYEROBJECT_H_

#include "EPBasicObject.h"
#include "EPAIDoll.h"

#include <SFML/Graphics.hpp>

#define ANIMUP    0
#define ANIMLEFT  1
#define ANIMRIGHT 2
#define ANIMDOWN  3


class UGUI_StaticImage ;

class EPPlayerObject: public EPAIDoll
{
public:
    struct Hotbar {
        uint32_t index;
    };
    /*
     *
     */
    EPPlayerObject();
    /*
     *
     */
    virtual ~EPPlayerObject();
    /*
     *
     */
    virtual void initialise();
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
    virtual void perform_action(const unsigned long &mode, const unsigned int &moveDirection);
    /*
    *
    */
    virtual void draw_ui(sf::RenderWindow*);
    /*
    *
    */
    virtual void setHealth(double) ;
    /*
    *
    */
    virtual void damage(double) ;
    /*
    *
    */
    virtual void heal(double) ;
    /*
    *
    */
    virtual void destroy() ;
private:
    /*
    *
    */
    void _update_hearts();
    /*
    *
    */
    bool internal_check_movement(int dir), m_immobile;
    float m_useRange;
    bool keyStates[255];

    sf::Texture mTexutres[4][3];
    sf::Texture mHearts[10];
    sf::Texture mBars[8];

    Hotbar mHotbarInfo;

    UGUI_StaticImage* mHeartOverlay, *mHotBar, *mHotbarSelect;
};

#endif /* EPPLAYEROBJECT_H_ */
