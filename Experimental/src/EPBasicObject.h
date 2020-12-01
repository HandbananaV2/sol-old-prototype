/*
 * EPBasicObject.h
 *
 *  Created on: Jun. 19, 2020
 *      Author: Michel
 */

#ifndef EPBASICOBJECT_H_
#define EPBASICOBJECT_H_

#include <string>

namespace sf
{
class RenderWindow;
}

class EPBasicObject;

struct EPCommandObject
{
    std::string m_str, m_str2;
    int m_int;
    EPBasicObject *m_target;
};

class EPBasicObject
{
public:
    /*
     *
     */
    EPBasicObject(const std::string&);
    /*
     *
     */
    virtual ~EPBasicObject();
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
    const std::string getName() const
    {
        return this->m_name;
    }
protected:
    std::string m_name;

};

#endif /* EPBASICOBJECT_H_ */
