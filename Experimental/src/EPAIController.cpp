#include "EPAIController.h"
#include "EPAIDoll.h"
#include <iostream>
/*
*
*/
EPAIController::EPAIController()
{

}
/*
*
*/
EPAIController::~EPAIController()
{

}
/*
*
*/
void EPAIController::addChild(const EPAIControllerData& c)
{
    switch(c.hosility)
    {

    case 0: // Friendly
        this->m_friendlies.emplace(m_friendlies.begin(), c);
        break;

    case 1: // Neutral
        this->m_neutral.emplace(m_neutral.begin(), c);
        break;

    case 2: // Passive
        this->m_passives.emplace(m_passives.begin(), c);
        break;

    default:
    case 3: // Hostile
        this->m_hostiles.emplace(m_hostiles.begin(), c);
        break;

    }

    this->onChildAdded(&c);
}
/*
*
*/
void EPAIController::removeChild(const EPAIControlId& cid, const uint32_t& o)
{
    //
    std::vector<EPAIControllerData>::iterator targetIterator = this->m_friendlies.end();
    //
    switch(o)
    {
    case 0:
        if( (targetIterator= std::find_if(this->m_friendlies.begin(), this->m_friendlies.end(), [cid]( const EPAIControllerData& A ) -> bool { return (A.itemName == cid); }) ) != m_friendlies.end())
        {
            this->onChildRemoved(&(*targetIterator));
            this->m_friendlies.erase(targetIterator);
        }
        break;

    case 1:
        if( (targetIterator= std::find_if(this->m_neutral.begin(), this->m_neutral.end(), [cid]( const EPAIControllerData& A ) -> bool { return (A.itemName == cid); }) ) != m_neutral.end())
        {
            this->onChildRemoved(&(*targetIterator));
            this->m_neutral.erase(targetIterator);
        }
        break;

    case 2:
        if( (targetIterator= std::find_if(this->m_passives.begin(), this->m_passives.end(), [cid]( const EPAIControllerData& A ) -> bool { return (A.itemName == cid); }) ) != m_passives.end())
        {
            this->onChildRemoved(&(*targetIterator));
            this->m_passives.erase(targetIterator);
        }
        break;

    case 3:
        if( (targetIterator= std::find_if(this->m_hostiles.begin(), this->m_hostiles.end(), [cid]( const EPAIControllerData& A ) -> bool { return (A.itemName == cid); }) ) != m_hostiles.end())
        {
            this->onChildRemoved(&(*targetIterator));
            this->m_hostiles.erase(targetIterator);
        }
        break;

    default:
        throw std::logic_error("EPAIController::removeChild(): The selected mode for AI removal is not valid. Value modes are between 0 - 3.");
    }

}
/*
*
*/
void EPAIController::onChildRemoved(const EPAIControllerData* c)
{
    std::cout << "Removing entity (" << (const void*)c->objectPtr << "): " << c->itemName << " from AI control. Entity hostility mode: " << c->hosility;
}
/*
*
*/
void EPAIController::onChildAdded(const EPAIControllerData* c)
{
    std::cout << "Adding entity (" << (const void*)c->objectPtr << "): " << c->itemName << " to AI control. Entity hostility mode: " << c->hosility;
}
