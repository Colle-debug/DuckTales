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
    bool _invincible;
    bool _dead;
    QPixmap _scrooge;
    QRect _texture_stand[1];
    QRect _texture_walk[3];
    QRect _texture_jump[1];
    QRect _texture_climb[2];
    QRect _texture_crouch[2];
    QRect _texture_stuck[1];
    QRect _texture_putt[6];
    QRect _texture_puttfail[2];
    QRect _texture_bounce[2];
    QRect _texture_dying[1];

    bool _scripted;
    bool _jumping;
    bool _gliding;
    bool _crouch;
    bool _grab;
    bool _climbing;
    bool _key;
    bool _remote;
    bool _launchpadAttached;

    bool _recentlyHit;
    int _hp;
    double _score = 0;
    friend class Launchpad;


public:
    Scrooge(QPointF pos);
    // Utilities per "_score"
    void scoreAdd(double amount) { _score += amount; }
    double score() { return _score; }

    // Utilities per "_hp"
    void hpAdd(int amount) { _hp += amount; }

    // Utilities per "_climbing"
    void setClimbing(bool on) { _climbing = on; }
    bool climbing() { return _climbing; }

    // Utilities per "_invincible"
    void setInvincible(bool on) { _invincible = on; }
    bool invincibile() { return _invincible; }

    // Utilities per "_key"
    void setKeyStatus(bool on) { _key = on; }
    bool hasTheKey() { return _key; }

    // Utilities per "_remote"
    void setRemoteStatus(bool on) { _remote = on; }
    bool hasTheRemote() { return _remote; }


    // Altri metodi
    bool swinging() { return _swinging; }
    bool dying() { return _dying; }
    bool dead() { return _dead; }
    bool pogoing() { return _pogoing; }
    void recentlyHit(bool on);
    void climbingPhysics();
    void gizmoduckCinematic();
    bool launchpadAttachment(){return _launchpadAttached;}


    virtual void lifeDown();
    //virtual void lifeUp();

    // implemented abstract methods
    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Player"; }
    //bool midair()  override const;
    // reimplemented methods
    virtual void advance() override;
    virtual bool midair() const override;

    // player actions
    virtual void pogo(bool on);
    virtual void grab(bool on = true);
    virtual void jump(bool on = true) override;
    virtual void die();
    virtual void crouch(bool on = true);
    virtual void swing(bool on = true);
};

#endif // SCROOGE_H
