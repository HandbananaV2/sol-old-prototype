#include "EPAIDoll.h"
#include "EPAIController.h"


EPAIDoll::EPAIDoll(EPAIController* ctrl, const std::string& name) : EPDrawable(name), mController(ctrl)
{

}

EPAIDoll::~EPAIDoll()
{

}
/*
*
*/
const double& EPAIDoll::getHealth() const
{
    return this->m_health;

}
/*
*
*/
void EPAIDoll::setHealth(double h)
{
    this->m_health = h;
}
/*
*
*/
void EPAIDoll::damage(double f)
{
    this->m_health = std::max(0.0, this->m_health - f);
}
/*
*
*/
void EPAIDoll::destroy()
{
    this->damage(m_health);
}
/*
*
*/
void EPAIDoll::heal(double h)
{
    this->m_health = std::min(m_max_health, this->m_health + h);
}
