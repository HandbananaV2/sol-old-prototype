/*
 * EPGameMap.cpp
 *
 *  Created on: Jun. 16, 2020
 *      Author: Michel
 */

#include "EPGameMap.h"
#include "EPDrawable.h"
#include "EPInteractable.h"
#include "EPPlayerObject.h"
#include "EPBase.h"
#include <math.h>
#include <iostream>
/*
 *
 */
EPGameMap::EPGameMap() :
    m_offset_x(0), m_offset_y(0), m_width(0), m_height(0), m_start_x(0), m_start_y(0), m_name("Map")
{

}
/*
 *
 */
EPGameMap::~EPGameMap()
{
    for (DyanicIterator it = this->mDynamics.begin(); it != this->mDynamics.end(); it++)
    {
        delete *it;
    }

    for (UsableIterator it = this->mUseables.begin(); it != this->mUseables.end(); it++)
    {
        delete *it;
    }
}
/*
 *
 */
void EPGameMap::bind_segment()
{
}
/*
 *
 */
bool EPGameMap::isOverlappingSolid(const sf::FloatRect &A)
{
    /*
     * The position snapped to the nearest block.
     */
    float snapped_x = (A.left > 0) ? std::round(A.left / 1024) : 0;
    float snapped_y = (A.top > 0) ? std::round(A.top / 768) : 0;
    /*
     * The bottom right corner snapped to the nearest block
     */
    float snapped_x_r = std::round(A.left + A.width / 1024);
    float snapped_y_r = std::round(A.top + A.height / 768);
    /*
     *
     */
    return (snapped_x != snapped_x_r || snapped_y != snapped_y_r);
}

/*
 *
 */
void EPGameMap::spawnPlayer(EPPlayerObject *player)
{
    EPPlayerObject* obj = (player) ? player : ExperimentalProject::G_Player;

    obj->setPosition(this->m_start_x, this->m_start_y);
}

/*
 * Is called when the map is set to inactive.
 */
void EPGameMap::sleep()
{

}
/*
 * Is called when the map when the map is transitioned into.
 */
void EPGameMap::wakeup()
{

}
/*
 *
 */
EPGameMap::SegmentData* EPGameMap::allocateSegment(int int1, int int2)
{
    this->mSegments[int1][int2] = SegmentData();
    this->mSegments[int1][int2].origin_x = int1 * 1024;
    this->mSegments[int1][int2].origin_y = int2 * 768;

    return &this->mSegments[int1][int2];

}

void EPGameMap::assignInteractable(EPDrawable *d)
{
    mUseables.push_back(d);
}

/*
 *
 */
std::vector<EPGameMap::SolidData>* EPGameMap::allocateSolid(int int1, int int2)
{
    return &(this->mSolids[int1][int2] = std::vector<SolidData>());
}
/*
 *
 */
void EPGameMap::update(float float1)
{
}
/*
 *
 */
void EPGameMap::draw(sf::RenderWindow *win)
{
    win->draw(mSkybox); // Draw the skybox(if any).

    for (unsigned int x = 0; x < SegmentCount; x++)
    {
        for (unsigned int y = 0; y < SegmentCount; y++)
        {
            this->mSegments[x][y]._block.setPosition(
                sf::Vector2f(this->mSegments[x][y].origin_x, this->mSegments[x][y].origin_y));

            win->draw(this->mSegments[x][y]._block);
        }
    }
    // Usable objects
    for (unsigned int x = 0; x < mUseables.size(); x++)
    {
        mUseables[x]->draw();
    }
    // Dynamics
    for (unsigned int x = 0; x < mDynamics.size(); x++)
    {
        mDynamics[x]->draw();
    }
}
/*
 *
 */
EPDrawable* EPGameMap::lookupUseObject(const sf::FloatRect &rect, int aimDir, float range)
{
    //
    int useRange = rect.height * range;
    // The ray used to look for useable objects.
    sf::FloatRect target_ray;
    // Object to return
    EPDrawable *object_ptr = nullptr;
    //
    std::vector<EPDrawable*>::iterator drawableIndex = mUseables.begin();
    //
    while (drawableIndex != mUseables.end())
    {
        // Up
        if (aimDir == 0)
        {
            target_ray = sf::FloatRect(rect.left + 8, rect.top - useRange, 16, useRange);
        }
        // Right
        else if (aimDir == 1)
        {
            target_ray = sf::FloatRect(rect.left + rect.width, rect.top + 8, useRange, 16);
        }
        // Down
        else if (aimDir == 2)
        {
            target_ray = sf::FloatRect(rect.left + 8, rect.top + rect.height, 16, useRange);
        }
        // Left
        else if (aimDir == 3)
        {
            target_ray = sf::FloatRect(rect.left - useRange, rect.top + 8, useRange, 16);
        }
        //
        if ((*drawableIndex)->getBoundaries().intersects(target_ray))
        {
            return (*drawableIndex);
        }

        ++drawableIndex;
    }
    //
    return object_ptr;

}
