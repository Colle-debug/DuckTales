#include "Rat.h"
#include "Sprites.h"
#include "GameConfig.h"
using namespace DT;


Rat::Rat(QPointF pos) : Enemy(pos, 39, 27)
{
    _sprite = Sprites::instance()->getSprite("rat");
    Sprites::instance()->get("rat-default", &_texture_walk[0]);
    _jumping = false;
    _floored = true;
    _reset = true;
    _y_vel_max = 3;

}

void Rat::jump(bool on, Direction dir)
{
    if (on) {
        if (!midair()) {
            if(!_floored){
                _y_vel_max = 3;
                _y_gravity = 0.05;
                std::cout<<"Salto 1\n";
                std::cout.flush();
                velAdd(Vec2Df(dir2speed(dir)*0.7, -2.5));}
            else{
                _y_vel_max = 5;
                _y_gravity = 0.15;
                std::cout<<"Salto 2\n";
                std::cout.flush();
                velAdd(Vec2Df(dir2speed(dir)*0.2, -3.5));}
            _x_dir = dir;
            _jumping = true;
            if(!_floored){
                schedule("stop", 60, [this](){_x_dir = Direction::NONE; _jumping = false; _floored = true;});
                schedule("down", 80, [this, dir](){jump(true, inverse(dir));});
            }else{
                schedule("stop", 61, [this](){_x_dir = Direction::NONE; _jumping = false; _reset = true;});
            }
        }
}

}
void Rat::advance()
{
    /*if(x() == 70*TILE){
    std::cout<<x()<<"\n"; // Debugging serve per capire se resetta bene la posizione --> Bisogna controllare i parametri del primo salto
        std::cout.flush();}*/
    if(_reset && !midair()){
        _reset = false;
        _floored = false;
        std::cout<<"Inizio salto\n";
        std::cout.flush();
         if(chanceCalculator(0.5)){
            schedule("wait", 10, [this](){jump(true, Direction::RIGHT);});
         }
         else{

            schedule("wait", 10, [this](){jump(true, Direction::LEFT);});

        }

    }
    //Scrooge* player = Game::instance()->player();
    /*srand(time(0) + _id);

    if (grounded() || _x_dir == Direction::NONE)
    {
        if(std::abs(player->x() - x()) < 10)	// align with player before jump
            move(Direction::NONE);
        else if (player->x() < x())				// chase player with 80% probability
            move(rand()%10 > 2 ? Direction::LEFT : Direction::RIGHT);
        else if (player->x() > x())				// chase player with 80% probability
            move(rand() % 10 > 2 ? Direction::RIGHT : Direction::LEFT);
    }*/

    Enemy::advance();
}

bool Rat::animate()
{
    _animRect = &_texture_walk[0];
    return true;
}

bool Rat::hit(Object* what, Direction fromDir)
{

    if (Enemy::hit(what, fromDir))
        return true;

    return false;
}

int Rat::dir2speed(Direction dir) { // Funziona per fare il fighetto e togliere un paio di if, ma si può benissimo farne a meno
    if (dir == Direction::RIGHT) {
        return 1;
    } else if (dir == Direction::LEFT) {
        return -1;
    } else {
        return 0;
    }
}
