#ifndef BOXER_H
#define BOXER_H

#include "Enemy.h"

namespace DT {
class Boxer;
}

class DT::Boxer: public Enemy {
protected:
    bool _jumping;
    bool _activated;
    bool _punching;
    bool _flying;
    QRect _texture_punch[2];
    QRect _texture_jump[2];


public:

    Boxer(QPointF pos);
    // implemented abstract methods
    virtual std::string name() override {
        return "Boxer[" + std::to_string(_id) + "]";
    }

    void groundPhysics();

    // reimplemented abstract methods
    virtual bool hit(Object * what, Direction fromDir) override;
    virtual void advance() override;
    virtual bool animate() override;
    virtual void jump(bool on = true) override;
    virtual void die() override;

};

#endif // BOXER_H
