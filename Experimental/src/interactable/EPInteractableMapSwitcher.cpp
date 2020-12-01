/*
 * EPInteractableMapSwitcher.cpp
 *
 *  Created on: Jun. 27, 2020
 *      Author: Michel
 */

#include <usefullib/json/json.h>
#include "EPInteractableMapSwitcher.h"

#include "../EPBase.h"
#include "../EPGameMap.h"
#include "../EPMapLoader.h"

#include <iostream>
/*
 *
 */
EPInteractable_MapSwitcher::EPInteractable_MapSwitcher(const std::string &allocator) :
    EPInteractable(allocator), m_spawnOrigin(sf::Vector2f(0, 0)), m_target(""), m_loaded(false), m_spawnOrigin_b(false)
{
}
/*
 *
 */
EPInteractable_MapSwitcher::~EPInteractable_MapSwitcher()
{
}
/*
 *
 */
void EPInteractable_MapSwitcher::initialize(const Json::Value *params)
{
    // Initialize the base
    EPInteractable::initialize(params);
    //
    const Json::Value &value = (*params)["parameters"];
    //
    for (unsigned int in = 0; in < value.size(); in++)
    {
        //
        const Json::Value &key = value[in]["key"];
        const Json::Value &kval = value[in]["value"];
        //
        const std::string &keyName = key.asString();
        const std::string &keyVal = kval.asString();
        // Map name
        if (keyName == "map")
            this->m_target = keyVal;
        /*
         * Spawn point options.
         *
         * If defined we will use this point. If not we will use the point the
         * map has defined in its configuration file.
         */
        else if (keyName == "spawn_x")
        {
            this->m_spawnOrigin.x = kval.asFloat();
            this->m_spawnOrigin_b = true;

            std::cout << "Map switcher has independent spawn point defined. " << std::endl;
        }
        else if (keyName == "spawn_y")
        {
            this->m_spawnOrigin.y = kval.asFloat();
            this->m_spawnOrigin_b = true;
            std::cout << "Map switcher has independent spawn point defined. " << std::endl;
        }
    }
}
/*
 *
 */
const std::string EPInteractable_MapSwitcher::getType() const
{
    return EPInteractable::getType() + "EPIteractable_MapSwitcher";
}
/*
 *
 */
int EPInteractable_MapSwitcher::sendCommand(const std::string &command, EPCommandObject *object)
{
    // Use action
    if (command == ACTION_USE)
    {

        std::cout << this->getSize().x << std::endl;
        std::cout << this->getSize().y << std::endl;

        ExperimentalProject::G_LoadingState = true;

        ExperimentalProject::ActiveMap()->sleep();
        // Return to primary means
        if (m_target == "return_to_primary")
        {
            // Reset the active map to the primary map ID.
            ExperimentalProject::G_ActiveMapID = ExperimentalProject::G_PrimaryMapId;
            // Return to the previous view state before we switched to this map.
            ExperimentalProject::World::PopViewState(ExperimentalProject::ViewType::VT_MAIN_VIEW);
            // Set her back to where she should be before the transition.
            ExperimentalProject::PopPlayerPosition();
        }
        // We're not returning to primary, we're going to another map section. This is a little different!
        else
        {
            ExperimentalProject::G_ActiveMapID = this->m_target;
            ExperimentalProject::G_PlayerTrasitions.push(ExperimentalProject::G_Player->getPosition());
            // If this object has a spawn position defined.
            if (this->m_spawnOrigin_b)
                ExperimentalProject::G_Player->setPosition(this->m_spawnOrigin.x * 32, this->m_spawnOrigin.y * 32);
            else
                ExperimentalProject::ActiveMap()->spawnPlayer(nullptr);
            // Push the original view position
            ExperimentalProject::World::PushViewState(ExperimentalProject::ViewType::VT_MAIN_VIEW);
            // Change the view target to the first block. If this object has its own spawn position
            // we'll use it. If not, we will use the one defined by the map itself.
            if (this->m_spawnOrigin_b)
            {
                ExperimentalProject::G_MainView = sf::View( sf::Vector2f(((this->m_spawnOrigin.x * 32)), ((this->m_spawnOrigin.y * 32))), sf::Vector2f(1280, 1024));
            }
            else
            {
                const sf::Vector2i spawnPointMap(ExperimentalProject::ActiveMap()->m_start_x,
                                                 ExperimentalProject::ActiveMap()->m_start_y);

                ExperimentalProject::G_MainView = sf::View(
                                                      sf::Vector2f(((spawnPointMap.x * 32)), ((spawnPointMap.y * 32))),
                                                      sf::Vector2f(1280, 1024));
            }
        }

        //
        ExperimentalProject::ActiveMap()->wakeup();

        ExperimentalProject::G_LoadingState = false;
    }
    //
    return 0;
}
/*
 *
 */
void EPInteractable_MapSwitcher::process_event(const std::string &allocator)
{
}
