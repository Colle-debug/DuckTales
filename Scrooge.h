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
    bool _dead;
    QPixmap _scrooge;
    QRect _texture_stand[1];
    QRect _texture_walk[3];
    QRect _texture_jump[1];
    QRect _texture_climb[2];
    QRect _texture_crouch[2];
    QRect _texture_stuck[1];
    QRect _texture_putt[2];
    QRect _texture_preputt[2];
    QRect _texture_puttsuccess[2];
    QRect _texture_puttfail[2];
    QRect _texture_bounce[2];
    


    bool _scripted;
    bool _jumping;
    bool _gliding;
    bool _crouch;

    bool _recentlyHit;
    int _hp;


public:
    Scrooge(QPointF pos);

    bool swinging(){ return _swinging; }
    bool dying(){ return _dying; }
    bool dead(){ return _dead; }
    bool pogoing(){ return _pogoing; }
    bool climbing(){ return _climbing; }
    bool invincibile(){ return _invincible; }
    void recentlyHit(bool on);

    virtual void lifeDown();
    //virtual void lifeUp();

    // implemented abstract methods
    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Player"; }

    // reimplemented methods
    virtual void advance() override;

    // player actions
    //virtual void pogo();
    virtual void jump(bool on = true) override;
    virtual void die();
    virtual void crouch(bool on = true);
};

#endif // SCROOGE_H
