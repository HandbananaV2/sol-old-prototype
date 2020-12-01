/*
 * EPInteractableSwitchType.h
 *
 *  Created on: Jun. 25, 2020
 *      Author: Michel
 */

#ifndef INTERACTABLE_EPINTERACTABLESWITCHTYPE_H_
#define INTERACTABLE_EPINTERACTABLESWITCHTYPE_H_

#include "../EPInteractable.h"

class EPInteractable_SwitchType: public EPInteractable
{
public:
    enum class SwitchType
    {
        ST_LEVER_TYPE, ST_BUTTON_TYPE, ST_SWITCH_TYPE, ST_FLOOR_TYPE,

        ST_CNT
    };
    /*
     *
     */
    EPInteractable_SwitchType(const std::string&);
    /*
     *
     */
    virtual ~EPInteractable_SwitchType();
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
    SwitchType mSwitchModeType;
};

#endif /* INTERACTABLE_EPINTERACTABLESWITCHTYPE_H_ */
