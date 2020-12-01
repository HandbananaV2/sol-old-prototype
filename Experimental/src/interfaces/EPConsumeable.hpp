#ifndef EPCONSUMABLE_HPP_INCLUDED
#define EPCONSUMABLE_HPP_INCLUDED
//
class EPConsumeable
{
public:
    //
    enum class ConsumableType
    {
        CT_HEALTH = 0,
        CT_DAMAGE = 1,
        CT_BOOST = 2,
        CT_EFFECT = 3,

        CT_CNT
    };
    //
    virtual ~EPConsumeable() {}
    //
    virtual void use() = 0;
    //
    const std::string& getName() const = 0;
    //
    ConsumableType getConsumeType() const = 0;
    //
private:
    std::string m_name;
    ConsumableType m_consume_type;
};


#endif // EPCONSUMABLE_HPP_INCLUDED
