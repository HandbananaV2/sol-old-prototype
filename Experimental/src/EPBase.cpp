/*
 * EPBase.cpp
 *
 *  Created on: Jun. 7, 2020
 *      Author: Michel
 */

#include "EPBase.h"
#include "EPInteractable.h"
#include "EPGameMap.h"
#include <math.h>
#include <algorithm>
#include <iterator>
#include <iostream>

class EPPlayerObject;

namespace ExperimentalProject
{
/*
*
*/
sf::Texture G_DebugTextureR, G_DebugTextureG, G_DebugTextureB, G_DebugTextureP, G_DebugTextureY, G_DebugTextureO, G_DebugTextureC;
/*
*
*/
std::string G_ApplicationRoot; // The application's root folder.
std::string G_PrimaryMapId; // Primary map ID
std::string G_ActiveMapID; // The active map ID.
/*
*
*/
GameState G_GameState = GameState::GS_MAIN_MENU;
/*
*
*/
EPPlayerObject *G_Player;
/*
*
*/
bool G_DebuggerEnabled = false;
/*
 *
 */
sf::Font G_UIFont, G_UIFont2;
sf::RenderWindow *G_MainWindow = nullptr;
std::map<std::string, EPGameMap*> G_WorldMaps;
/*
 *
 */
sf::View G_MainView, G_CView;
std::stack<sf::View> G_MainViewStack;
std::stack<sf::View> G_SecondaryViewStack;
std::stack<sf::Vector2f> G_PlayerTrasitions;
/*
*
*/
void InitializeCore()
{
    G_DebugTextureR.loadFromFile(ExperimentalProject::G_ApplicationRoot + "resources/opt/r.png");
    G_DebugTextureG.loadFromFile(ExperimentalProject::G_ApplicationRoot + "resources/opt/g.png");
    G_DebugTextureB.loadFromFile(ExperimentalProject::G_ApplicationRoot + "resources/opt/b.png");
    G_DebugTextureP.loadFromFile(ExperimentalProject::G_ApplicationRoot + "resources/opt/r.png");
    G_DebugTextureY.loadFromFile(ExperimentalProject::G_ApplicationRoot + "resources/opt/g.png");
    G_DebugTextureO.loadFromFile(ExperimentalProject::G_ApplicationRoot + "resources/opt/b.png");
    G_DebugTextureC.loadFromFile(ExperimentalProject::G_ApplicationRoot + "resources/opt/b.png");
}
/*
*
*/
bool G_LoadingState = false;

EPGameMap* GetMap(const std::string &name)
{
    if (name.empty())
        return G_WorldMaps[G_ActiveMapID];
    else
        return G_WorldMaps[name];
}

void PopPlayerPosition()
{
    if (G_PlayerTrasitions.empty())
        throw std::logic_error("PopPlayerPosition(): No position has been assigned!");

    const sf::Vector2f &target = G_PlayerTrasitions.top();
    ExperimentalProject::G_Player->setPosition(target.x, target.y);
    G_PlayerTrasitions.pop();
}

void PushMap(EPGameMap *map)
{
    if (G_WorldMaps.find(map->m_name) != G_WorldMaps.end())
        throw std::logic_error("PushMap: Duplicate map dependencies");

    std::cout << "Registering map (" << map << ") " << map->m_name << std::endl;

    G_WorldMaps[map->m_name] = map;
}


EPGameMap* ActiveMap()
{
    return G_WorldMaps[G_ActiveMapID];
}

namespace World
{
/*
 *
 */
void PushViewState(ViewType t)
{
    switch (t)
    {
    default:
    case ViewType::VT_MAIN_VIEW:
        G_MainViewStack.push(G_MainView);
        break;

    case ViewType::VT_SECONDARY_VIEW:
        G_SecondaryViewStack.push(G_CView);
        break;
    }
}
/*
 *
 */
void PopViewState(ViewType t)
{
    switch (t)
    {
    case ViewType::VT_SECONDARY_VIEW:
        G_CView = G_SecondaryViewStack.top();
        G_SecondaryViewStack.pop();
        break;
    default:
    case ViewType::VT_MAIN_VIEW:
    {
        G_MainView = G_MainViewStack.top();
        G_MainViewStack.pop();
    }
    }
}
std::stack<EPEventStore*> lookup_targets;
/*
 * Add an object here for event linking once the map has finished loading.
 */
void RegisterEventLookup(EPEventStore *target)
{
    lookup_targets.push(target);
}
/*
 * Call this at the end of each map load so we can link everything
 * together.
 */
void ProcessEventLookups(EPGameMap* map)
{
    while (!lookup_targets.empty())
    {
        // The event item
        EPEventStore *item = lookup_targets.top();
        lookup_targets.pop();
        //
        EPGameMap::UsableIterator iterator = map->mUseables.begin();
        // Look for the object in the target's name and bind it.
        while (iterator != map->mUseables.end())
        {
            // If the name matches, then bind the object to the event.
            if ((*iterator)->getName() == item->event_target_name)
            {
                std::cout << "Discovered target '" << item->event_target_name << '"' << std::endl;
                std::cout << "	Event Name '" << item->event_name << '"' << std::endl;
                std::cout << "	Event Value '" << item->event_value << '"' << std::endl;
                item->target_ptr = (*iterator);
            }
            ++iterator;
        }

        if (item->target_ptr == nullptr)
        {
            std::cout << "ProcessEventLookups(): Couldn't find object with the name '" << item->event_target_name
                      << "' in world. Event(s) '" << item->event_name << "' was not bound but dropped. " << std::endl;
        }
    }
}
}
}

std::ostream& operator <<(std::ostream &in, const sf::Vector2i i)
{
    return in << " sf::Vector2f { X=" << i.x << ", Y=" << i.y << " }";
}

std::ostream& operator <<(std::ostream &in, const sf::Vector2f i)
{
    return in << " sf::Vector2f { X=" << i.x << ", Y=" << i.y << " }";
}

std::ostream& operator <<(std::ostream &in, const sf::FloatRect i)
{
    return in << " sf::FloatRect { X=" << i.left << ", Y=" << i.top << ", W=" << i.width << ", H=" << i.height << " }";
}

std::ostream& operator <<(std::ostream &in, const sf::IntRect i)
{
    return in << " sf::IntRect { X=" << i.left << ", Y=" << i.top << ", W=" << i.width << ", H=" << i.height << " }";
}

