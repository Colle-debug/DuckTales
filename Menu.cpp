#include "Menu.h"
#include "Game.h"
#include "GameConfig.h"
#include "Sprites.h"
#include <QPainter>

using namespace DT;

Title::Title() : Object(QPoint(0, 0), TILE * 30, TILE * 30)
{
    Game::instance()->world()->addPixmap(QPixmap(":/sprites/difficulty.png"));
    Game::instance()->centerOn(0, 0);
    _arrow = new Arrow();
    setZValue(1);
}

void Title::advance()
{
    return;
}


Level::Level():Object(QPoint(0, 0), TILE * 30, TILE * 30)
{
    QPixmap fullPixmap(":/sprites/levelSelection.png");
    QPixmap croppedPixmap = fullPixmap.copy(0, 0, 256, 224);
    Game::instance()->world()->addPixmap(croppedPixmap);
}

void Level::advance()
{
    return;
}

Arrow::Arrow() : Object(QPoint(32, 129), 5, 8)
{
    _pos = 0;
    prev_pos = 0;
    _sprite = Sprites::instance()->getSprite("titleArrow");
    Sprites::instance()->get("title-arrow", &_anim[0]);
    _animRect = &_anim[0];
}


void Arrow::advance()
{
    int newPos = Game::instance()->arrowPos();
    if(prev_pos == newPos){
        return;
    }else{
    if(newPos == 2 || _pos == 2){
            setPos((x() + (newPos - _pos) * TILE * 4), y());}
    else{
        setPos((x() + (newPos - _pos) * TILE * 3), y());}
    prev_pos = _pos;
    _pos = newPos;
    }
}

bool Arrow::animate()
{
    return true;
}





