#ifndef RAT_H
#define RAT_H


#include "Enemy.h"

namespace DT
{
class Rat;
}

class DT::Rat : public Enemy
{
private:

public:

    Rat(QPointF pos);

    // implemented abstract methods
    virtual std::string name() override { return "Rat[" + std::to_string(_id) + "]"; }

    // reimplemented abstract methods
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual void advance() override;
    virtual bool animate() override;

};




#endif // RAT_H
