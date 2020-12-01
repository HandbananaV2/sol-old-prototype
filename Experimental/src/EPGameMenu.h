#ifndef EPGAMEMENU_H
#define EPGAMEMENU_H

#include <UGUIPanel.h>
#include <UGUIComponent.h>
#include <UGUIButton.h>
#include <UGUI.h>

class EPGameMenu : private UGUI_Component
{
public:
    //
    EPGameMenu();
    //
    ~EPGameMenu();
    //
    void initialize_menu();
    //
    void event(const UGUI::UGUI_EventId&, const UGUI::EventObject&);
    //
    void display();
    //
    void update(float);
    //
    const std::string& getMenuState() const
    {
        return mMenuState;
    }
    //
    void reset();
protected:

private:
    enum MenuIndex
    {
        MI_INDEX_MAIN = 0,
        MI_INDEX_SETTINGS,
        MI_INDEX_LOAD_SCREEN,
        MI_INDEX_SAVE_SCREEN,

        MI_INDEX_COUNT
    };

    std::string mMenuState;

    sf::Texture mMenuBackdrop;
    sf::Texture mUiTextures[64];

    MenuIndex mIndex;

    UGUI_Panel* mPanels[16];
    UGUI_Button* mControlButtons[16][16];
};

#endif // EPGAMEMENU_H
