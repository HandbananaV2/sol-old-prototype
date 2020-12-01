/*
 * EPInteractable.cpp
 *
 *  Created on: Jun. 25, 2020
 *      Author: Michel
 */

#include "EPInteractable.h"
#include "EPGameMap.h"
#include "EPBase.h"
#include <usefullib/json/json.h>

#include <iostream>

/*
 *
 */
EPInteractable::EPInteractable(const std::string &s) :
    EPDrawable(s)
{
    mDisabled = false;
    mState = 0;
    mBounadries.width = 32;
    mBounadries.height = 32;
}
/*
 *
 */
EPInteractable::~EPInteractable()
{
}
/*
 *
 */
void EPInteractable::draw()
{
    EPDrawable::draw();
}
/*
 *
 */
void EPInteractable::update(float float1)
{
}
/*
 *
 */
const std::string EPInteractable::getType() const
{
    return EPDrawable::getType() + ".EPInteractable";
}
/*
 *
 */
int EPInteractable::sendCommand(const std::string &command, EPCommandObject *object)
{

    return 0;
}
/*
 *
 */
void EPInteractable::initialize(const Json::Value *parameters)
{
    /*
     *
     */
    this->mState = (*parameters)["state"].asInt();
    this->m_name = (*parameters)["name"].asString();
    /*
     *
     */
    Json::Value events = (*parameters)["events"];
    /*
     *
     */
    for (unsigned int event_index = 0; event_index < events.size(); event_index++)
    {
        const Json::Value element = events[event_index];
        const std::string &eventName = element["event_name"].asString();
        const std::string &eventTarget = element["event_target_name"].asString();
        const std::string &eventValue = element["event_value"].asString();
        //
        EventStoreIterator position = mEvents.begin();
        //
        if ((position = this->mEvents.find(eventName)) == this->mEvents.end())
        {
            this->mEvents[eventName] = std::stack<EPEventStore>();
            position = mEvents.find(eventName);
        }
        //
        (&position->second)->push(EPEventStore { eventName, eventTarget, eventValue, 0, nullptr });
        // Bind this object so we can connect all the events later on.
        ExperimentalProject::World::RegisterEventLookup(&((&position->second)->top()));
    }

    ExperimentalProject::ActiveMap()->mUseables.push_back(this);
}

/*
*
*/
void EPInteractable::setSize_L(float x, float y, bool d)
{
    this->mBounadries.width = x;
    this->mBounadries.height = y;

    if( d )
    {
        this->mDebugSprite.setScale(sf::Vector2f(x / mDebugSprite.getLocalBounds().width, y / mDebugSprite.getLocalBounds().height));
    }
}
