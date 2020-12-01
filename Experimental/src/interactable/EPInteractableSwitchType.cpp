/*
 * EPInteractableSwitchType.cpp
 *
 *  Created on: Jun. 25, 2020
 *      Author: Michel
 */
#include <usefullib/json/json.h>
#include "../EPBase.h"
#include "../EPGameMap.h"

#include <iostream>
#include "EPInteractableSwitchType.h"
/*
 *
 */
EPInteractable_SwitchType::EPInteractable_SwitchType(const std::string &allocator) :
    EPInteractable(allocator)
{

    mSwitchModeType = SwitchType::ST_BUTTON_TYPE;
}
/*
 *
 */
EPInteractable_SwitchType::~EPInteractable_SwitchType()
{
}
/*
 *
 */
const std::string EPInteractable_SwitchType::getType() const
{
    if (mSwitchModeType == SwitchType::ST_LEVER_TYPE)
        return EPInteractable::getType() + ".EPInteractable_SwitchType#lever";
    else if (mSwitchModeType == SwitchType::ST_SWITCH_TYPE)
        return EPInteractable::getType() + ".EPInteractable_SwitchType#switch";
    else if (mSwitchModeType == SwitchType::ST_FLOOR_TYPE)
        return EPInteractable::getType() + ".EPInteractable_SwitchType#floortype";
    else
        return EPInteractable::getType() + ".EPInteractable_SwitchType#button";
}
/*
 *
 */
int EPInteractable_SwitchType::sendCommand(const std::string &command, EPCommandObject *object)
{
    if (command == ACTION_USE)
    {
        if (!this->mDisabled)
        {
            this->mState = !this->mState;
            /*
             * Off state
             */
            if (this->mState == 0)
            {
                this->mSprite.setTexture(mTextures[2]);
            }
            /*
             * On state
             */
            if (this->mState == 1)
            {
                this->mSprite.setTexture(mTextures[0]);
            }

            this->process_event(ACTION_USE);
        }
    }
    return 0;
}
/*
 *
 */
void EPInteractable_SwitchType::initialize(const Json::Value *parameters)
{
    // Initialize the base parameters
    EPInteractable::initialize(parameters);
    //
    {
        /*
         * Sub-class
         */
        if ((*parameters)["subclass"] == "lever")
        {
            this->mSwitchModeType = SwitchType::ST_LEVER_TYPE;
            if (!this->mTextures[0].loadFromFile("resources/sprites/Objects/Switches/lever_01.png")
                    || !this->mTextures[1].loadFromFile("resources/sprites/Objects/Switches/lever_02.png")
                    || !this->mTextures[2].loadFromFile("resources/sprites/Objects/Switches/lever_03.png"))
            {
                throw std::logic_error("EPInteractable_SwitchType: Unable to load textures for switch type 'lever'.");
            }
        }
        else if ((*parameters)["subclass"] == "switch")
        {
            this->mSwitchModeType = SwitchType::ST_SWITCH_TYPE;
            if (!this->mTextures[0].loadFromFile("resources/sprites/Objects/Switches/switch_01.png")
                    || !this->mTextures[1].loadFromFile("resources/sprites/Objects/Switches/switch_02.png")
                    || !this->mTextures[2].loadFromFile("resources/sprites/Objects/Switches/switch_03.png"))
            {
                throw std::logic_error("EPInteractable_SwitchType: Unable to load textures for switch type 'switch'.");
            }
        }
        else if ((*parameters)["subclass"] == "floortype")
        {
            this->mSwitchModeType = SwitchType::ST_FLOOR_TYPE;
            if (!this->mTextures[0].loadFromFile("resources/sprites/Objects/Switches/floorplate_01.png")
                    || !this->mTextures[1].loadFromFile("resources/sprites/Objects/Switches/floorplate_02.png")
                    || !this->mTextures[2].loadFromFile("resources/sprites/Objects/Switches/floorplate_03.png"))
            {
                throw std::logic_error("EPInteractable_SwitchType: Unable to load textures for switch type 'floortype'.");
            }
        }
        else
        {
            this->mSwitchModeType = SwitchType::ST_BUTTON_TYPE;
            if (!this->mTextures[0].loadFromFile("resources/sprites/Objects/Switches/button_01.png")
                    || !this->mTextures[1].loadFromFile("resources/sprites/Objects/Switches/button_02.png")
                    || !this->mTextures[2].loadFromFile("resources/sprites/Objects/Switches/button_03.png"))
            {
                throw std::logic_error("EPInteractable_SwitchType: Unable to load textures for switch type 'button'.");
            }
        }
    }
    //
    this->mSprite.setTexture((mState > 0) ? mTextures[2] : mTextures[0]);
    this->setSize(21, 21);
}
/*
 *
 */
void EPInteractable_SwitchType::process_event(const std::string &allocator)
{
    if (this->mEvents.find(allocator) == this->mEvents.end())
        return;

    std::stack<EPEventStore> *storePtr = &this->mEvents[allocator];

    while (!storePtr->empty())
    {
        EPCommandObject objectPtr;
        objectPtr.m_str = storePtr->top().event_name;
        objectPtr.m_str2 = storePtr->top().event_value;
        objectPtr.m_int = storePtr->top().event_value_i;
        objectPtr.m_target = this;

        storePtr->top().target_ptr->sendCommand(allocator, &objectPtr);
        storePtr->pop();
    }
}
