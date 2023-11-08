#include "Scrooge.h"
#include "Game.h"
#include "Block.h"
#include "Enemy.h"
#include "Launchpad.h"
#include <QDebug>
#include "GameConfig.h"
#include <QPainter>
#include <QPixmap>
#include "Sprites.h"
#include "StaticObject.h"
#include "Sounds.h"

using namespace DT;
Scrooge::Scrooge(QPointF pos): Entity(pos, 26, 27) {
  //setZValue(1);

  //_collider.adjust(3, 3, -3, -1);
  _swinging = false;
  _dying = false;
  _dead = false;
  _pogoing = false;
  _crouch = false;
  _climbing = false;
  _invincible = false;
  _grab = false;
  _climbingStill = false;
  _prev_x_dir = Direction::RIGHT;
  _mirror_x_dir = Direction::LEFT;

  _hp = 3;
  _recentlyHit = 0;
  _key = true;
  _remote = true;

  _scripted = false;
  _jumping = false;
  _gliding = false;
  _scr00ge = true;
  _launchpadAttached = false;
  _duckburg = false;
  _gizmoCinematic = false;
  _sitting = true;


  _sprite = Sprites::instance() -> getSprite("scrooge");
  Sprites::instance() -> get("scrooge-stand", & _texture_stand[0]);
  Sprites::instance() -> get("scrooge-walk-0", & _texture_walk[0]);
  Sprites::instance() -> get("scrooge-walk-1", & _texture_walk[1]);
  Sprites::instance() -> get("scrooge-walk-2", & _texture_walk[2]);
  Sprites::instance() -> get("scrooge-jump-fall", & _texture_jump[0]);
  Sprites::instance() -> get("scrooge-bounce-0", & _texture_bounce[0]);
  Sprites::instance() -> get("scrooge-bounce-1", & _texture_bounce[1]);
  Sprites::instance() -> get("scrooge-crouch-0", & _texture_crouch[0]);
  Sprites::instance() -> get("scrooge-crouch-1", & _texture_crouch[1]);
  Sprites::instance() -> get("scrooge-stuck", & _texture_stuck[0]);
  Sprites::instance() -> get("scrooge-climb-0", & _texture_climb[0]);
  Sprites::instance() -> get("scrooge-climb-1", & _texture_climb[1]);
  Sprites::instance() -> get("scrooge-putt-0", & _texture_putt[0]);
  Sprites::instance() -> get("scrooge-putt-1", & _texture_putt[1]);
  Sprites::instance() -> get("scrooge-putt-2", & _texture_putt[2]);
  Sprites::instance() -> get("scrooge-putt-3", & _texture_putt[3]);
  Sprites::instance() -> get("scrooge-putt-4", & _texture_putt[4]);
  Sprites::instance() -> get("scrooge-putt-5", & _texture_putt[5]);
  Sprites::instance() -> get("scrooge-putt-fail-0", & _texture_puttfail[0]);
  Sprites::instance() -> get("scrooge-putt-fail-1", & _texture_puttfail[1]);
  Sprites::instance() -> get("scrooge-dying", & _texture_dying[0]);
  Sprites::instance() -> get("scrooge-sit", & _texture_sitting[0]);

  // this->setPixmap(_texture_stand[0]);

}

void Scrooge::setClimbing(bool on) {
  _climbing = on;
  if (on) {
    std::cout << "Climbing\n";
    std::cout.flush();
    climbingPhysics();
  } else {
    defaultPhysics();
  }
}

void Scrooge::advance() {
  if (grounded())
    _y_vel_max = 3;
  if (falling() && !_climbing) {
    _y_gravity = 0.18;
  }
  if (!falling()) {
    _jumping = false; //when not falling, jumping is over
  }
  if(_sitting){
    _boundingRect = QRectF(0, 0, 20, 20);
    _collider = _boundingRect;
  }

  Entity::advance();
}

bool Scrooge::midair() const {
  return (Entity::midair() && !_climbing);
}
void Scrooge::jump(bool on) {
  if (_scripted)
    return;

  if (on) {
    if (!midair() && !_pogoing && !_swinging) {
      if (std::abs(_vel.x) <= 2) {
        velAdd(Vec2Df(0, -4));
        _y_gravity = 0.078;
      } else {
        velAdd(Vec2Df(0, -5));
        _y_gravity = 0.1;
      }

      _jumping = true;
      // Sounds::instance()->play("ScroogeHit");
      //Sounds::instance()->play(std::string("jump-") + (_big ? "big" : "small"));
    }
  } else
    _y_gravity = 0.8;
}

bool Scrooge::animate() {
  if (!_gizmoCinematic) { // Nel gioco, non appena viene attivata l'animazione di Gizmo che rompe il cancello, Scrooge rimane "freezzato" nell'animazione del frame in cui ha iniziato la cinematic.
    if (midair() && !_pogoing)
      _animRect = & _texture_jump[0];
    if (_pogoing)
      _animRect = & _texture_bounce[0];
    if (!midair() && _pogoing && _vel.y == 0)
      _animRect = & _texture_bounce[1];

    if (_vel.y == 0 && !_pogoing)
      _animRect = & _texture_stand[0];
    if ((_vel.x > 0 || _vel.x < 0) && !midair() && !_pogoing)
      _animRect = & _texture_walk[(FRAME_COUNT / 9) % 4];
    if (_vel.x == 0 && _crouch && !_pogoing && !midair())
      //_animRect = &_texture_crouch[0];
      _animRect = & _texture_crouch[1];
    if (_dead || _dying) {
      _animRect = & _texture_dying[0];
    }
    if (_climbing) {
      if (!_climbingStill) {
        _animRect = & _texture_climb[(FRAME_COUNT / 9) % 2];
      } else {
        _animRect = & _texture_climb[0];
      }
    }
    if (_swinging && !_jumping && !_pogoing && _vel.x == 0) {
      _animRect = & _texture_putt[(FRAME_COUNT / 9) % 5];
      // _animRect = &_texture_putt[2];
      /* _animRect = &_texture_putt[0];
        _animRect = &_texture_putt[1];
    */
    }
    if (_launchpadAttached) {
      _animRect = & _texture_climb[0];
    }

    if(_sitting){
      _animRect = & _texture_sitting[0];
    }
  }
  return 1;
}
/*else if (_vel.x == 0 && !_crouch)
            _animRect = &_texture_stand[0];
     else if  (_vel.x == 0 &&  _crouch)

            _animRect = &_texture_crouch[0;

    */

bool Scrooge::hit(Object * what, Direction fromDir) {
  StaticObject * sobj = what -> to < StaticObject * > ();
  Enemy * enemy = what -> to < Enemy * > ();
  Block * block = what -> to < Block * > ();
  Spawnable * spawnable = what -> to < Spawnable * > ();

  if (_grab) {
    if (sobj && sobj -> _type == StaticObject::Type::ROPE) {
      setClimbing(true);
      setX(sobj -> pos().x() - 0.66 * TILE);
    }
  }
  if (sobj && sobj -> _type == StaticObject::Type::SPIKE && !_pogoing) {
    lifeDown();
    Sounds::instance() -> play("hit");
  }

  if (sobj && sobj -> _type == StaticObject::Type::DEATHLINE) {
    die();
    Sounds::instance() -> play("hit");
  }

  /*if(enemy  && !_pogoing){
         velAdd(Vec2Df(0, -15.5));
         _y_gravity = 0.065;
          Sounds::instance()->play("hit");

  }*/

  if (enemy && ((fromDir == Direction::DOWN && _pogoing) || _invincible)) {
    if(!_invincible){
    velAdd(Vec2Df(0, -15.5));
      _y_gravity = 0.065;
    }
    enemy -> die();

    if (chanceCalculator(1)) { // 100% probabilità per testing
      new Spawnable(enemy -> pos(), TILE, TILE, Spawnable::Type::ICE_CREAM);
    }
  }

  if (block && fromDir == Direction::DOWN && _pogoing) {
    velAdd(Vec2Df(0, -15.5));
    _y_gravity = 0.065;
    Sounds::instance() -> play("hit");
  }

  return false;
}

void Scrooge::crouch(bool on) {
  if (!_jumping && !_scripted)
    _crouch = on;

}

void Scrooge::grab(bool on) {
  //Vedi quale if ci andrebbe
  _grab = on;
  schedule("grab", 100, [this]() {
    _grab = false;
  });
}

void Scrooge::die() {
  if (_dying)
    return;
  _dying = true;
  _collidable = false;
  _vel.x = 0;
  _x_dir = Direction::NONE;
  _vel.y = -3;
  schedule("die", 50, [this]() {
    _dying = false;
    _dead = true;
  });
}

void Scrooge::lifeDown() {
  if (_recentlyHit)
    return;

  if (_hp > 1) {
    _hp--;
    recentlyHit(true);
  } else
    die();
}

void Scrooge::recentlyHit(bool on) {
  _recentlyHit = on;

  if (on)
    schedule("flash", 10, [this]() {
      _recentlyHit = false;
    });
}

void Scrooge::climbingPhysics() {
  _vel.x = 0;
  _x_dir = Direction::NONE;
  _y_dir = Direction::NONE;
  _y_gravity = 0;
  _y_acc_up = 0;
}



void Scrooge::setGizmoCinematicStatus(bool on) {
  _gizmoCinematic = on;

  if (on) {
    _x_dir = Direction::NONE;
    _vel = {
      0,
      0
    };
    _y_gravity = 0;

    schedule("playable", 200, [this]() {
      _gizmoCinematic = false;
      defaultPhysics();
    });
  }
}

void Scrooge::pogo(bool on) {

  if (on) {
    if (!midair() && !_jumping) {
      if (std::abs(_vel.x) <= 2) {
        velAdd(Vec2Df(0, -3.5));
        _y_gravity = 0.065;
      } else {
        velAdd(Vec2Df(0, -5));
        _y_gravity = 0.1;
      }

      _pogoing = true;
      Sounds::instance() -> play("pogoing");
    } else if (midair())
      _pogoing = true;

  } else {
    _y_gravity = 0.8;
    _pogoing = false;

  }
}

void Scrooge::swing(bool on) {
  if (on) {
    if (!_jumping && !_pogoing && _vel.x == 0) {
      _swinging = true;

    }
  } else _swinging = false;
}

