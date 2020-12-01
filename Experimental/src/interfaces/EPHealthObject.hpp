#ifndef __EPHEALTHOBJ_HHP
#define __EPHEALTHOBJ_HHP
/*
* Used for objects that can receive damage.
*/
class EPHealthObject
{
public:
    virtual ~EPHealthObject() {}
    /*
    *
    */
    virtual const double& getHealth() const = 0;
    /*
    *
    */
    virtual void setHealth(double) = 0;
    /*
    *
    */
    virtual void damage(double) = 0;
    /*
    *
    */
    virtual void destroy() = 0;
    /*
    *
    */
    virtual void heal(double) = 0;
    //
protected:
    double m_health, m_max_health;
};

#endif // __EPHEALTHOBJ_HHP
