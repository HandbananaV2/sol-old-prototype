//
// Task List
//
// Can be completed in any order. Make sure the first three are done in order.
//
// TODO: Add more map segments
// TODO: Implement scrolling and scroll locking.
// TODO: Complete implementation of map switcher.
//
// TODO: Complete player animations.
// TODO: Implement weapon and damage system including effects and imobilization.
// TODO: Implement player inventory.
// TODO: Implement AI and NPCs
// TODO: Implement and design UI elements
// TODO: Implement currency and health display
// TODO: Implement splash screens & game menu
//
#ifndef EPBASE_H_
#define EPBASE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "EPPlayerObject.h"

class EPGameMap;
class EPBasicObject;
class EPEventStore;

#include <ostream>
#include <stack>

#if defined(_WIN64) || defined(_WIN32)
// MinGW's version of dirent is different.. the version we're using is from
// the github page.
#include <dirent-vs.h>
#else
#include <dirent.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
#define OS_VERSION "Microsoft Windows x86_64"
#else
#define OS_VERSION "GNU+Linux"
#endif

#define GAME_BUILD_DATE __DATE__ " @ " __TIME__
#define GAME_VERSION  "PROTOTYPE - 0.0.2 " OS_VERSION " / " GAME_BUILD_DATE
#define GAME_TITLE "Survival Of Luna(OLD RELEASE)"

namespace ExperimentalProject
{
static constexpr long DisplayWidth = 1280;
static constexpr long DisplayHeight = 1024;

enum class GameState
{
    GS_MAIN_MENU = 0,
    GS_INVT_MENU = 1,
    GS_WEPN_MENU = 2,
    GS_GAME_STAT = 3,

    GS_MENU_CNT
};
enum class ViewType
{
    VT_MAIN_VIEW, VT_SECONDARY_VIEW
};

extern sf::Texture G_DebugTextureR, G_DebugTextureG, G_DebugTextureB, G_DebugTextureP, G_DebugTextureY, G_DebugTextureO, G_DebugTextureC;

extern std::string G_ApplicationRoot;
extern std::string G_PrimaryMapId; // Primary map ID
extern std::string G_ActiveMapID; // The active map ID.

extern bool G_DebuggerEnabled;

extern EPPlayerObject *G_Player; // Player Object
extern sf::View G_MainView, G_CView; // Views
extern sf::Font G_UIFont, G_UIFont2; // UI Font
extern sf::RenderWindow *G_MainWindow; // The UI Window
extern bool G_LoadingState; // Defines whether the game is in loading state.
extern GameState G_GameState;

extern std::stack<sf::View> G_MainViewStack;
extern std::stack<sf::View> G_SecondaryViewStack;

extern std::map<std::string, EPGameMap*> G_WorldMaps; // List of world maps
extern std::stack<sf::Vector2f> G_PlayerTrasitions; // List of player positions.

void InitializeCore();

// Get the map in the front of the container.
EPGameMap* GetMap(const std::string &name = "");
EPGameMap* ActiveMap();
//
void PopPlayerPosition();
// Push a new map into the vector.
void PushMap(EPGameMap*);
//
//
//
void PopLastMap();

namespace World
{
void PushViewState(ViewType);
void PopViewState(ViewType);

void RegisterEventLookup(EPEventStore*);
void ProcessEventLookups(EPGameMap*);

extern std::stack<EPEventStore*> lookup_targets;
}
}
/*
 *
 */
extern std::ostream& operator <<(std::ostream &in, const sf::Vector2f i);
extern std::ostream& operator <<(std::ostream &in, const sf::Vector2i i);
extern std::ostream& operator <<(std::ostream &in, const sf::FloatRect i);
extern std::ostream& operator <<(std::ostream &in, const sf::IntRect i);
/*
 *
 */
#define ACTION_USE "USE_KEY"

#endif /* EPBASE_H_ */
