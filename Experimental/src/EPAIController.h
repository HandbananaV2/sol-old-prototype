#ifndef EPAICONTROLLER_H
#define EPAICONTROLLER_H

#include <string>
#include <vector>

class EPAIDoll;

typedef uint32_t EPAIControlId;

struct EPAIControllerData
{
    EPAIControlId itemName;
    EPAIDoll* objectPtr;
    uint32_t hosility;
};


class EPAIController
{
public:
    /*
    *
    */
    EPAIController();
    /*
    *
    */
    virtual ~EPAIController();
    /*
    *
    */
    void addChild(const EPAIControllerData&);
    /*
    *
    */
    void removeChild(const EPAIControlId&, const uint32_t& = 4);
    /*
    *
    */
    void update(float);
protected:
    void onChildRemoved(const EPAIControllerData* c);
    void onChildAdded(const EPAIControllerData* c);

private:
    std::vector<EPAIControllerData> m_hostiles;
    std::vector<EPAIControllerData> m_passives;
    std::vector<EPAIControllerData> m_neutral;
    std::vector<EPAIControllerData> m_friendlies;
};

#endif // EPAICONTROLLER_H
