#include "EPGameMenu.h"
#include "EPBase.h"
#include <iostream>
//
EPGameMenu::EPGameMenu() : UGUI_Component(GUI_DEFAULT, "#menu"), mMenuState(""), mIndex(MI_INDEX_MAIN)
{

}
//
EPGameMenu::~EPGameMenu()
{
    std::cout << "Destroyed menu " << std::endl;
}
//
void EPGameMenu::initialize_menu()
{
    // Application root
    const std::string& root = ExperimentalProject::G_ApplicationRoot;
    // Menu backdrop image
    this->mMenuBackdrop.loadFromFile(root + "resources/sprites/UI/menu/background.png");
    // -- UI Textures
    // Button Textures
    //
    this->mUiTextures[0].loadFromFile(root + "resources/sprites/UI/Dialog/button_face_0.png");
    this->mUiTextures[1].loadFromFile(root + "resources/sprites/UI/Dialog/button_face_1.png");
    this->mUiTextures[2].loadFromFile(root + "resources/sprites/UI/Dialog/button_face_1.png");
    //
    int indexOffset = 0;
    // ========================================================================
    // START MAIN MENU PANEL
    // ========================================================================
    mPanels[MI_INDEX_MAIN] = new UGUI_Panel(GUI_DEFAULT, "#main-menu-panel");
    mPanels[MI_INDEX_MAIN]->bindSurface(0, this->mMenuBackdrop);
    mPanels[MI_INDEX_MAIN]->bindSurface(0);
    mPanels[MI_INDEX_MAIN]->setSize(1280, 1024, true);
    mPanels[MI_INDEX_MAIN]->setPosition(0,0);
    // Start button
    mControlButtons[MI_INDEX_MAIN][0] = new UGUI_Button("#start-button", sf::Mouse::Button::Left, "title", "Start Game", 0.75);
    // Options button
    mControlButtons[MI_INDEX_MAIN][1] = new UGUI_Button("#option-button", sf::Mouse::Button::Left, "title", "Options", 0.75);
    // Exit button
    mControlButtons[MI_INDEX_MAIN][2] = new UGUI_Button("#exit-button", sf::Mouse::Button::Left, "title", "Exit Game", 0.75);
    //
    for(unsigned int i = 0; i < 3; i++)
    {
        // Bind the surfaces to each button.
        for(unsigned int p = 0; p < 3; p++)
            mControlButtons[MI_INDEX_MAIN][i]->bindSurface(p, mUiTextures[p]);
        // Bind the surface and set the position.
        mControlButtons[MI_INDEX_MAIN][i]->bindSurface(0);
        mControlButtons[MI_INDEX_MAIN][i]->setSize(512, 64, true);
        mControlButtons[MI_INDEX_MAIN][i]->setPosition(512 - 128, 300 + ( 190 * i ) ) ;
        mControlButtons[MI_INDEX_MAIN][i]->bindEvent(UGUI::UGUI_EventId::EVENT_BUTTON_PRESSED, this);
        mControlButtons[MI_INDEX_MAIN][i]->bindEvent(UGUI::UGUI_EventId::EVENT_BUTTON_RELEASED, this);
        // Append the button
        mPanels[MI_INDEX_MAIN] ->appendChild(mControlButtons[MI_INDEX_MAIN][i]);
        //
        indexOffset ++;
    }
    // ========================================================================
    // END MAIN MENU PANEL
    // ========================================================================

}
//
void EPGameMenu::event(const UGUI::UGUI_EventId& id, const UGUI::EventObject& o)
{
    //
    if( o.eventTrigger && id == UGUI::UGUI_EventId::EVENT_BUTTON_RELEASED )
    {
        //
        UGUI_Button* btn = dynamic_cast<UGUI_Button*>(o.eventTrigger);
        //
        if( btn != nullptr )
        {
            if( btn->getName() == "#exit-button" )
            {
                this->mMenuState = "exit";
                ExperimentalProject::G_MainWindow->close();
                return;
            }
            if( btn->getName() == "#start-button" )
            {
                this->mMenuState = "start";

                return;
            }
        }

    }
    //
    UGUI_Component::event(id, o);
}
//
void EPGameMenu::display()
{
    //
    if( this->mIndex == MI_INDEX_MAIN )
    {
        mPanels[MI_INDEX_MAIN]->display();

    }

}
//
void EPGameMenu::update(float)
{
    mPanels[MI_INDEX_MAIN]->update(0);
}
//
void EPGameMenu::reset()
{
    this->mMenuState = "";
}
