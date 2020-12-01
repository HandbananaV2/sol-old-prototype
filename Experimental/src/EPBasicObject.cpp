/*
 * EPBasicObject.cpp
 *
 *  Created on: Jun. 19, 2020
 *      Author: Michel
 */

#include "EPBasicObject.h"
#include <stdexcept>
/*
 *
 */
EPBasicObject::EPBasicObject(const std::string &allocator) :
    m_name(allocator)
{
}
/*
 *
 */
EPBasicObject::~EPBasicObject()
{

}

/*
 *
 */
const std::string EPBasicObject::getType() const
{
    return "EPBasicObject";
}
/*
 *
 */
int EPBasicObject::sendCommand(const std::string &command, EPCommandObject *object)
{
    return 0x0;
}
