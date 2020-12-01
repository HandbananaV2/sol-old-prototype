/*
 * EPDynamicObject.h
 *
 *  Created on: Jul. 25, 2020
 *      Author: Michel
 */

#ifndef EPDYNAMICOBJECT_H_
#define EPDYNAMICOBJECT_H_

#include "EPInteractable.h"

class EPDynamicObject: public EPInteractable
{
public:
    /*
     *
     */
    EPDynamicObject(const std::string&);
    /*
     *
     */
    virtual ~EPDynamicObject();
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
     *
     */
    virtual void process_event(const std::string&);
};

#endif /* EPDYNAMICOBJECT_H_ */
