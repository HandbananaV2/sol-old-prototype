#ifndef EPAIDOLL_H
#define EPAIDOLL_H

#include "EPDrawable.h"
#include "interfaces/EPHealthObject.hpp"

class EPAIController;

/*
*
*/
class EPAIDoll : public EPDrawable, public EPHealthObject
{
public:
    enum Hostility
    {
        H_FRIENDLY = 0,
        H_NEUTRAL,
        H_PASSIVE,
        H_HOSTILE,

        H_CNT
    };
    /*
    *
    */
    EPAIDoll(EPAIController* ctrl, const std::string&);
    /*
    *
    */
    virtual ~EPAIDoll();
    /*
    *
    */
    virtual const double& getHealth() const ;
    /*
    *
    */
    virtual void setHealth(double) ;
    /*
    *
    */
    virtual void damage(double) ;
    /*
    *
    */
    virtual void heal(double) ;
    /*
    *
    */
    virtual void destroy() ;
    /*
    *
    */
    virtual const EPAIController* getController() const
    {
        return mController;
    }
    /*
    *
    */
    virtual bool isHostile() const
    {
        return mDem == EPAIDoll::H_HOSTILE;
    }
    /*
    *
    */
    virtual bool isFriend() const
    {
        return mDem == EPAIDoll::H_FRIENDLY;
    }
    /*
    *
    */
    virtual bool isNeutral() const
    {
        return mDem == EPAIDoll::H_NEUTRAL;
    }
    /*
    *
    */
    virtual bool isPassive() const
    {
        return mDem == EPAIDoll::H_PASSIVE;
    }
    /*
    *
    */
    virtual void setDemMode(const Hostility& e)
    {
        this->mDem = mDem;
    }
    /*
    *
    */
    const Hostility& getDemMode() const
    {
        return mDem;
    }
private:
    EPAIController* mController;
    Hostility mDem;
};

#endif // EPAIDOLL_H
