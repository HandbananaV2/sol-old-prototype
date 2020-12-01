/*
 * EPInteractableMapSwitcher.h
 *
 *  Created on: Jun. 27, 2020
 *      Author: Michel
 */

#ifndef INTERACTABLE_EPINTERACTABLEMAPSWITCHER_H_
#define INTERACTABLE_EPINTERACTABLEMAPSWITCHER_H_

#include <SFML/Graphics.hpp>
#include "../EPInteractable.h"

class EPInteractable_MapSwitcher: public EPInteractable
{
public:
    /*
     *
     */
    EPInteractable_MapSwitcher(const std::string&);
    /*
     *
     */
    virtual ~EPInteractable_MapSwitcher();
    /*
     *
     */
    virtual void initialize(const Json::Value*);
    /*
     *
     */
    virtual const std::string getType() const;
    /*
     *
     */
    virtual int sendCommand(const std::string &command, EPCommandObject *object = nullptr);
    /*
     *
     */
    virtual void process_event(const std::string&);
private:
    sf::Vector2f m_spawnOrigin;
    std::string m_target;
    bool m_loaded;
    bool m_spawnOrigin_b;
};

#endif /* INTERACTABLE_EPINTERACTABLEMAPSWITCHER_H_ */
