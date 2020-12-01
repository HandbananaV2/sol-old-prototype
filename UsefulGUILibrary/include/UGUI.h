/*
 * UGUI.h
 *
 *  Created on: Aug. 5, 2020
 *      Author: Michel
 */

#ifndef INCLUDE_UGUI_H_
#define INCLUDE_UGUI_H_

#include <string>
#include <SFML/Graphics.hpp>

namespace sf {
	class RenderWindow;
	class Font;
}

class UGUI_EventComponent;

// Defines the limit of textures allowed per UGUI_Displayable
#define UGUI_TEXTURE_COUNT 4

namespace UGUI {
	// ================================================================================
	enum class UGUI_EventId {
		EVENT_BUTTON_PRESSED = 0, EVENT_BUTTON_RELEASED = 1, EVENT_CONTROL_EN_STATE_CHANGED = 2, EVENT_CONTROL_VI_STATE_CHANGED = 3
	};
	// ================================================================================
	struct EventObject {
			UGUI_EventId eventId;
			int eventVal;
			UGUI_EventComponent* eventTrigger;
	};
	// ================================================================================
	namespace Config {
		// The UI Font list
		// This is just a list containing fonts by name to use with the UI library.
		//
		// They are not deleted at any point within this library. The main application
		// is responsible for disposing of these resources.
		extern std::map<std::string, sf::Font*> UiFonts;
		// The render window used by the application/game.
		extern sf::RenderWindow *RenderHandle;
		// Sets the display window for the UI library
		void SetRenderTarget(sf::RenderWindow*);
		// Bind a font pointer to an identifier.
		void SetFontFaces(const std::string&, sf::Font *uiFont);
		// Returns the font pointer by ID. If the font cannot be found an exception will be raised.
		const sf::Font* GetFontFace(const std::string&);
	}
}

#endif /* INCLUDE_UGUI_H_ */
