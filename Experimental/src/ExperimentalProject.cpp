#include <iostream>

#include "EPBase.h"
#include "EPGameMap.h"
#include "EPMapLoader.h"
#include "EPPlayerObject.h"

#include <usefullib/json/json.h>
#include <usefullib/encoding.h>
#include <usefullib/utility.h>

#include <UGUI.h>
#include <UGUI_Base.hpp>
#include <UGUILabel.h>
#include <UGUIButton.h>

#include "EPGameMenu.h"


#include <stdlib.h>

using namespace std;
/*
*
*/
sf::Texture uiTextures[128];
/*
*
*/
EPGameMenu* epMenu = nullptr;
/*
* Game menu components
*/
/*
 *
 */
void draw_ui(sf::RenderWindow* handle)
{
    ExperimentalProject::G_Player->draw_ui(handle);
}
/*
 *@formatter:off
 */
void preinit(const std::string& root)
{
    //sf::err().rdbuf(0);
    // Load the main font.
    if( ! ExperimentalProject::G_UIFont.loadFromFile(root + "resources/VarelaRound-Regular.ttf") ) throw std::logic_error("preinit(): Unable to load primary font file.");
    if( ! ExperimentalProject::G_UIFont2.loadFromFile(root + "resources/BalooThambi-Regular.ttf") ) throw std::logic_error("preinit(): Unable to load secondary font file.");
    // UI fonts
    UGUI::Config::SetFontFaces("default", &ExperimentalProject::G_UIFont);
    UGUI::Config::SetFontFaces("title", &ExperimentalProject::G_UIFont2);
    //
    epMenu = new EPGameMenu();
    //
    epMenu->initialize_menu();
}
/*
 *@formatter:on
 */
void start_game(const Json::Value& root)
{
    ExperimentalProject::G_LoadingState = true;
    ExperimentalProject::G_GameState = ExperimentalProject::GameState::GS_GAME_STAT;
    //
    const Json::Value &dependRoot = root["maps"];
    const Json::Value &primaryMap = root["primary"];
    //
    ExperimentalProject::G_PrimaryMapId = primaryMap.asString();
    ExperimentalProject::G_ActiveMapID = primaryMap.asString();
    //
    for (unsigned int x = 0; x < dependRoot.size(); x++)
    {
        EPMapLoader loader(ExperimentalProject::G_ApplicationRoot + "resources/world/" + root["maps"][x].asString());
        loader.load();
        loader.load_base();
        loader.load_solids();
        loader.load_dynamics();
        loader.load_useables();
        loader.finialize();
    }
    // The map loader changes it so it can work
    ExperimentalProject::G_ActiveMapID = ExperimentalProject::G_PrimaryMapId;
    //
    ExperimentalProject::G_Player = new EPPlayerObject();
    ExperimentalProject::G_Player->initialise();
    //
    ExperimentalProject::GetMap(primaryMap.asString())->spawnPlayer();
    ExperimentalProject::G_LoadingState = false;
    //
    ExperimentalProject::G_GameState = ExperimentalProject::GameState::GS_GAME_STAT;
}
/*
*
*/
int main(int cnt, char *args[])
{
    std::map<std::string, std::string> params;
    //  Parse any startup arguments.
    UsefulLibrary::Utility::ParseEntryArguments(args, cnt, params);
    // The root path of the binary with an ending slash.
    const std::string& applicationRoot = ExperimentalProject::G_ApplicationRoot = params[".__root"];
    // booleans for the debugger
    bool F1_Pressed = false;
    bool F2_Pressed = false;
    //
    std::string err = "";
    //
    Json::Value root;
    //
    try
    {
        //
        unsigned int winStartX = 0, winStartY = 0;
        // Redirect all log outut for debugging.
        freopen("last_log.txt", "w", stdout);
        freopen("last_err_log.txt", "w", stderr);
        //
        // These parameters define where the window will be opened on the desktop. It is used to fix some XOrg/Window manager
        // issues regarding window placement. By default it's the far left.. but we may want it different.
        //
        if( params.find("--posx") != params.end() )
            winStartX = std::atoi(params["--posx"].c_str());
        if( params.find("--posy") != params.end() )
            winStartY = std::atoi(params["--posy"].c_str());
        //
        //
        //
        std::cout << "Starting game version " << GAME_VERSION << std::endl;
        std::cout << "Start path is: " << ExperimentalProject::G_ApplicationRoot << std::endl;
        std::cout << "Startup window placement was overridden:  X = " << winStartX << ", Y = " << winStartY << std::endl;
        //
        sf::RenderWindow *window = (ExperimentalProject::G_MainWindow = new sf::RenderWindow(sf::VideoMode(1280, 1024, 32), "" GAME_VERSION, sf::Style::Close | sf::Style::Titlebar));
        //
        window->setPosition(sf::Vector2i(winStartX, winStartY));
        //
        window->setFramerateLimit(60);
        //
        ExperimentalProject::G_CView = sf::View(sf::Vector2f(1280 / 2, 1024 / 2), sf::Vector2f(1280, 1024));
        ExperimentalProject::G_MainView = sf::View(sf::Vector2f(1280 / 2, 1024 / 2), sf::Vector2f(1280, 1024));
        //
        // Set the render window.
        //
        UGUI::Config::SetRenderTarget(window);
        //
        // Initialize the engine core
        //
        ExperimentalProject::InitializeCore();
        //
        preinit(applicationRoot);
        //
        if (!Json::LoadJson(applicationRoot + "resources/world/maplist.json", &root, &err))
            throw std::logic_error("EPMapLoader::load_base(): Unable to load base resource file for the active map.\n" + err);
        //
        while (window->isOpen())
        {
            sf::Event _event;
            //
            while (window->pollEvent(_event))
            {
                if (_event.type == sf::Event::Closed)
                    return 1;

                if (_event.type == sf::Event::KeyPressed)
                {
                    /*
                    * Enables/disables the boxes around objects.
                    */
                    if( _event.key.code == sf::Keyboard::F2 && !F2_Pressed && ( ExperimentalProject::G_GameState == ExperimentalProject::GameState::GS_GAME_STAT) )
                    {
                        F2_Pressed=true;
                        ExperimentalProject::G_DebuggerEnabled=true;
                        std::cout << "Advanced debugger has been toggled." << std::endl;
                    }
                    /*
                    * Used to output world information.
                    */
                    if (_event.key.code == sf::Keyboard::F1 && !F1_Pressed && ( ExperimentalProject::G_GameState == ExperimentalProject::GameState::GS_GAME_STAT) )
                    {
                        F1_Pressed = true;
                        std::cout << "================================================================" << std::endl;
                        std::cout << "======================= ENGINE INFORMATION =====================" << std::endl;
                        std::cout << "================================================================" << std::endl;
                        std::cout << std::endl;
                        std::cout << "Game version: " << GAME_VERSION << std::endl;
                        std::cout << "Origin path is: " << ExperimentalProject::G_ApplicationRoot << std::endl;
                        std::cout << "Startup overrides: Window Correction { " << winStartX << "," << winStartY << " }" << std::endl;
                        std::cout << std::endl;
                        std::cout << "Player X -- (Real) " << ExperimentalProject::G_Player->getPosition().x << std::endl;
                        std::cout << "Player Y -- (Real) " << ExperimentalProject::G_Player->getPosition().y << std::endl;
                        std::cout << "Player X -- (Snap) " << ExperimentalProject::G_Player->getPosition().x / 32 << std::endl;
                        std::cout << "Player Y -- (Snap) " << ExperimentalProject::G_Player->getPosition().y / 32 << std::endl;
                        std::cout << "Player W -- (Real) " << ExperimentalProject::G_Player->getBoundaries().width << std::endl;
                        std::cout << "Player H -- (Real) " << ExperimentalProject::G_Player->getBoundaries().height << std::endl;
                        std::cout << "-------------" << std::endl;
                        std::cout << "View X Centre -- " << ExperimentalProject::G_MainView.getCenter().x << std::endl;
                        std::cout << "View Y Centre -- " << ExperimentalProject::G_MainView.getCenter().y << std::endl;
                        std::cout << "View Width    -- " << ExperimentalProject::G_MainView.getViewport().width * 1280 << std::endl;
                        std::cout << "View Height   -- " << ExperimentalProject::G_MainView.getViewport().height * 1024 << std::endl;
                        std::cout << "-------------" << std::endl;
                        std::cout << "Map Dynamic Count: " << ExperimentalProject::ActiveMap()->mDynamics.size() << std::endl;
                        std::cout << "Map Useable Count: " << ExperimentalProject::ActiveMap()->mUseables.size() << std::endl;
                        std::cout << "Map Width(Pixels): " << ExperimentalProject::ActiveMap()->m_width << std::endl;
                        std::cout << "Map Height(Pixels): " << ExperimentalProject::ActiveMap()->m_height << std::endl;
                        std::cout << "Map Width(Blocks): " << ExperimentalProject::ActiveMap()->m_width / 32 << std::endl;
                        std::cout << "Map Height(Blocks): " << ExperimentalProject::ActiveMap()->m_height / 32 << std::endl;
                        std::cout << "Map Name: " << ExperimentalProject::ActiveMap()->m_name << std::endl;
                        std::cout << "Total number of maps loaded: " << ExperimentalProject::G_WorldMaps.size() << std::endl;
                        std::cout << "================================================================" << std::endl;
                    }
                }
                else if (_event.type == sf::Event::KeyReleased)
                {
                    if (_event.key.code == sf::Keyboard::F1)
                    {
                        F1_Pressed = false;
                    }
                }
            }
            // This game state signifies the game is active and we're not at a menu.
            if( ExperimentalProject::G_GameState == ExperimentalProject::GameState::GS_GAME_STAT)
            {
                //
                // Update loop
                //
                if (!ExperimentalProject::G_LoadingState)
                {
                    ExperimentalProject::G_Player->update(0);
                }
                //
                window->setView(ExperimentalProject::G_MainView);
                //
                window->clear(sf::Color::Black);
                //
                if (!ExperimentalProject::G_LoadingState)
                {
                    // This must be drawn before everything else.
                    ExperimentalProject::ActiveMap()->draw(window);
                    // The player is drawn last.
                    ExperimentalProject::G_Player->draw();
                    // Set the UI view
                    window->setView(ExperimentalProject::G_CView);
                    // Draw the UI
                    draw_ui(window);
                    // Set the game back to primary view.
                    window->setView(ExperimentalProject::G_MainView);
                }
                //
                window->display();
            }
            else
            {
                // Change the active view to the UI view.
                window->setView(ExperimentalProject::G_CView);
                // This game state tells us we're at the inventory screen.
                if( ExperimentalProject::G_GameState == ExperimentalProject::GameState::GS_INVT_MENU)
                {

                }
                // This game state tells us we're at the weapon/skill screen.
                else if( ExperimentalProject::G_GameState == ExperimentalProject::GameState::GS_WEPN_MENU)
                {

                }
                // This game state tells us we're at the main menu.
                else if( ExperimentalProject::G_GameState == ExperimentalProject::GameState::GS_MAIN_MENU)
                {
                    //
                    epMenu->update(0);
                    //
                    window->clear(sf::Color::Black);
                    epMenu->display();
                    window->display();
                    //
                    if( epMenu->getMenuState() == "start" )
                    {
                        epMenu->reset();
                        start_game(root);
                    }
                }
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Fatal Exception: " << e.what() << std::endl;
    }
    catch (const char *e)
    {
        std::cout << "Fatal Exception: " << e << std::endl;
    }
    return 0;
}

