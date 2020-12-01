/*
 * EPDynamicObject.cpp
 *
 *  Created on: Jul. 25, 2020
 *      Author: Michel
 */

#include "EPDynamicObject.h"
/*
 *
 */
EPDynamicObject::EPDynamicObject(const std::string &allocator) :
    EPInteractable(allocator)
{
}
/*
 *
 */
EPDynamicObject::~EPDynamicObject()
{
}
/*
 *
 */
const std::string EPDynamicObject::getType() const
{
    return EPDrawable::getType() + ".EPDynamicObject";
}
/*
 *
 */
int EPDynamicObject::sendCommand(const std::string &command, EPCommandObject *object)
{
    return 0;
}
/*
 *
 */
void EPDynamicObject::initialize(const Json::Value *v)
{
    EPInteractable::initialize(v);
}
/*
 *
 */
void EPDynamicObject::process_event(const std::string &allocator)
{
}
