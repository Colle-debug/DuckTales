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
    bool _reset;
    bool _jumping;
    bool _floored;
    bool _running;
    bool _starting;
    bool _angry;
    QRect _texture_angry[1];

public:

    Rat(QPointF pos);

    void jump(bool on, Direction dir);


    // implemented abstract methods
    virtual std::string name() override { return "Rat[" + std::to_string(_id) + "]"; }

    // reimplemented abstract methods
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual void advance() override;
    virtual bool animate() override;

    int dir2speed(Direction dir);
};




#endif // RAT_H
