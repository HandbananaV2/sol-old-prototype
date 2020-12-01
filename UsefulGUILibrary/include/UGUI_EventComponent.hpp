/*
 * UGUI_EventComponent.hpp
 *
 *  Created on: Aug. 16, 2020
 *      Author: Michel
 */

#ifndef INCLUDE_UGUI_EVENTCOMPONENT_HPP_
#define INCLUDE_UGUI_EVENTCOMPONENT_HPP_

#include <string>

#include "UGUI.h"

class UGUI_EventComponent {
	public:

		/*
        *
        */
		virtual ~UGUI_EventComponent() {
		}
		/*
         *
         */
		virtual void event(const UGUI::UGUI_EventId&, const UGUI::EventObject&) = 0;
		/*
        *
        */
		virtual void bindEvent(const UGUI::UGUI_EventId&, UGUI_EventComponent *) = 0;
		/*
        *
        */
};

#endif /* INCLUDE_UGUI_EVENTCOMPONENT_HPP_ */
