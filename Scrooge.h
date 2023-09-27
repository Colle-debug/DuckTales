#ifndef SCROOGE_H
#define SCROOGE_H
#include <QPointF>
#include "Entity.h"
#include <QPixmap>

namespace DT{
    class Scrooge;
}

class DT::Scrooge : public Entity
{
protected:
    bool _swinging;
    bool _dying;
    bool _pogoing;
    bool _climbing;
    bool _invincible;
    QPixmap _scrooge;
    QPixmap _texture_stand[1];
    QRect _animStand[1];

    bool _scripted;
    bool _jumping;
    bool _gliding;

public:
    Scrooge(QPointF pos);

    bool swinging(){ return _swinging; }
    bool dying(){ return _dying; }
    bool pogoing(){ return _pogoing; }
    bool climbing(){ return _climbing; }
    bool invincibile(){ return _invincible; }


    // implemented abstract methods
    virtual void animate() override;
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Player"; }

    // reimplemented methods
    virtual void advance() override;

    // player actions
    //virtual void pogo();
    virtual void jump(bool on = true) override;
    //virtual void die();
};

#endif // SCROOGE_H
