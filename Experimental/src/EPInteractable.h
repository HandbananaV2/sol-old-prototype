/*
 * EPInteractable.h
 *
 *  Created on: Jun. 25, 2020
 *      Author: Michel
 */

#ifndef EPINTERACTABLE_H_
#define EPINTERACTABLE_H_

#include "EPDrawable.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include <map>
namespace Json
{
class Value;
}

struct EPEventStore
{
    std::string event_name, event_target_name, event_value;
    int event_value_i;
    EPBasicObject *target_ptr;
};

class EPInteractable: public EPDrawable
{
public:
    /*
     *
     */
    EPInteractable(const std::string&);
    /*
     *
     */
    virtual ~EPInteractable();
    /*
     *
     */
    virtual void draw();
    /*
     *
     */
    virtual void update(float);
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
    virtual void initialize(const Json::Value*);
    /*
     *
     */
    virtual void process_event(const std::string&) = 0;
    /*
    *
    */
    virtual void setSize_L(float, float, bool);
protected:
    bool mDisabled;
    int mState;

    sf::Texture mTextures[8];
    std::map<std::string, std::stack<EPEventStore>> mEvents;

    typedef std::map<std::string, std::stack<EPEventStore>>::iterator EventStoreIterator;
};

#endif /* EPINTERACTABLE_H_ */
