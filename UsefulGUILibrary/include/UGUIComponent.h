/*
 * UGUIComponent.h
 *
 *  Created on: Aug. 5, 2020
 *      Author: Michel
 */

#ifndef INCLUDE_UGUICOMPONENT_H_
#define INCLUDE_UGUICOMPONENT_H_

#include <string>
#include <vector>
#include <stdlib.h>
#include <memory.h>

#include <SFML/Graphics.hpp>

#include "UGUI.h"
#include "UGUI_EventComponent.hpp"
//
enum Rules {
	GUI_DELETE_CHILDREN = 1, GUI_PERMIT_DUPLICATE_NAME = 2, GUI_DRAW_CHILDREN_BEFORE = 4, GUI_UPDATE_CHILDREN_BEFORE = 6, GUI_DEFAULT = 8
};
//
class UGUI_Component: public UGUI_EventComponent {
	public:
		typedef std::vector<std::string>::const_iterator TagIterator;
		typedef std::vector<UGUI_Component*>::const_iterator ChildIterator;
		/*
		*
		*/
		UGUI_Component(int ruleSet, const std::string &name = "UI Object");
		/*
		*
		*/
		virtual ~UGUI_Component();
		/*
		*
		*/
		virtual void display();
		/*
		*
		*/
		virtual void update(float);
		/*
		*
		*/
		virtual std::string getType() const;
		/*
		*
		*/
		UGUI_Component* findChildByName(const std::string &name) const;
		/*
		*
		*/
		ChildIterator findChildByName_T(const std::string &name) const;
		/*
		*
		*/
		void findChildrenByTag(const std::string &tag, std::vector<UGUI_Component*>&) const;
		/*
		*
		*/
		const std::vector<UGUI_Component*>& getChildren() const {
			return mChildren;
		}
		/*
		*
		*/
		void appendChild(UGUI_Component *component_ptr);
		/*
		*
		*/
		void disjoinChild(const std::string&);
		/*
		*
		*/
		const std::string& getName() const {
			return m_name;
		}
		/*
		*
		*/
		bool isEnabled() const {
			return m_enabled;
		}
		/*
		*
		*/
		void setEnabled(bool mEnabled) {
			m_enabled = mEnabled;
		}
		/*
		*
		*/
		bool isVisible() const {
			return m_visible;
		}
		/*
		*
		*/
		void setVisible(bool mVisible) {
			m_visible = mVisible;
		}
		/*
		*
		*/
		virtual void event(const UGUI::UGUI_EventId&, const UGUI::EventObject&);
		/*
		*
		*/
		virtual void bindEvent(const UGUI::UGUI_EventId&, UGUI_EventComponent*);
	protected:
		void update_children(float);
		void display_children();

		int m_rules;

		bool m_enabled, m_visible;

		std::string m_name;
		std::vector<UGUI_Component*> mChildren;
		std::vector<std::string> mTags;
		std::map<UGUI::UGUI_EventId, std::vector<UGUI_EventComponent*>> mEvents;
};

#endif /* INCLUDE_UGUICOMPONENT_H_ */
