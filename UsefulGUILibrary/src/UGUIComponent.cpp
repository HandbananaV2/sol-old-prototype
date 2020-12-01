/*
 * UGUIComponent.cpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: Michel
 */

#include "UGUIComponent.h"
#include <type_traits>
#include <iterator>
#include <algorithm>
#include <iostream>
/*
 *
 */
UGUI_Component::UGUI_Component(int ruleSet, const std::string &name) :
		m_rules(ruleSet), m_enabled(true), m_visible(true), m_name(name) {
}
/*
 *
 */
UGUI_Component::~UGUI_Component() {
	// If the delete rule is applied delete the children.
	if (m_rules & GUI_DELETE_CHILDREN) {
		ChildIterator it = mChildren.begin();
		while (it != mChildren.end()) {
			delete (*it);
			++it;
		}
	}
}
/*
 *
 */
void UGUI_Component::display() {

}
/*
 *
 */
void UGUI_Component::update(float float1) {
	if (m_rules & GUI_UPDATE_CHILDREN_BEFORE)
		this->update_children(float1);

	// ...

	if (!(m_rules & GUI_UPDATE_CHILDREN_BEFORE))
		this->update_children(float1);
}
/*
 *
 */
std::string UGUI_Component::getType() const {
	return "UGUI_Component";
}
/*
 *
 */
void UGUI_Component::update_children(float float1) {
	for (ChildIterator it = this->mChildren.begin(); it != this->mChildren.end(); ++it)
		(*it)->update(float1);
}
/*
 *
 */
void UGUI_Component::display_children() {
	for (ChildIterator it = this->mChildren.begin(); it != this->mChildren.end(); ++it)
		(*it)->display();
}
/*
 *
 */
UGUI_Component* UGUI_Component::findChildByName(const std::string &name) const {

	ChildIterator iterator = std::find_if(mChildren.begin(), mChildren.end(), [&](UGUI_Component *vPtr) {
		return (vPtr && vPtr->getName() == name);
	});

	return (iterator == this->mChildren.end()) ? nullptr : (*iterator);
}

//
UGUI_Component::ChildIterator UGUI_Component::findChildByName_T(const std::string &name) const {
	return std::find_if(mChildren.begin(), mChildren.end(), [&](UGUI_Component *vPtr) {
		return (vPtr && vPtr->getName() == name);
	});
}
/*
 *
 */
void UGUI_Component::findChildrenByTag(const std::string &tagStr, std::vector<UGUI_Component*> &allocator) const {
	ChildIterator iterator = mChildren.begin();

	while (iterator != mChildren.end()) {

		TagIterator tag = std::find_if((*iterator)->mTags.begin(), (*iterator)->mTags.end(), [&](const std::string &vPtr) {
			return (vPtr == tagStr);
		});

		if (tag != (*iterator)->mTags.end())
			allocator.push_back(*iterator);

		++iterator;
	}
}
/*
 *
 */
void UGUI_Component::appendChild(UGUI_Component *component_ptr) {

	if (this->findChildByName_T(component_ptr->getName()) != this->mChildren.end()) {
		if (!(m_rules & GUI_PERMIT_DUPLICATE_NAME))
			throw std::logic_error("UGUI_Component::appendChild(): Duplicate children are not permitted on this UI object.");
	}

	this->mChildren.push_back(component_ptr);
}
/*
 *
 */
void UGUI_Component::disjoinChild(const std::string &s) {
	ChildIterator object = this->mChildren.end();

	if ((object = this->findChildByName_T(s)) != this->mChildren.end()) {
		// Duplicate children rule?
		if (m_rules & GUI_PERMIT_DUPLICATE_NAME)
			std::cout << "UGUI_Component::disjoinChild(): Rules permit duplicate children! Removing only one child named '" << s << "'" << std::endl;

		// Delete children rule when detached?
		if (m_rules & GUI_DELETE_CHILDREN)
			delete (*object);

		object = this->mChildren.erase(object);
	}

}
/*
 *
 */
void UGUI_Component::event(const UGUI::UGUI_EventId &i, const UGUI::EventObject &t) {
	try {
		std::vector<UGUI_EventComponent*> &arr = mEvents[i];

		for (unsigned int x = 0; x < arr.size(); x++) {
			arr[x]->event(i, t);
		}
	} catch (std::out_of_range &e) {
		std::cout << "UGUI_Component::event(): Unable to locate event ID code " << (int) i << " in this object." << std::endl;
	}
}
/*
 *
 */
void UGUI_Component::bindEvent(const UGUI::UGUI_EventId &i, UGUI_EventComponent *t) {
	if (mEvents.find(i) == mEvents.end())
		mEvents[i] = std::vector<UGUI_EventComponent*>();

	mEvents[i].push_back(t);
}
