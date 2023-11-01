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
    if (_moving)
        setY(y());
}



Arrow::Arrow() : Object(QPoint(32, 129), 5, 8)
{
    _sprite = Sprites::instance()->getSprite("titleArrow");
    Sprites::instance()->get("title-arrow", &_anim[0]);
    _animRect = &_anim[0];
}


void Arrow::advance()
{
    return;
}

bool Arrow::animate()
{
    return true;
}

void Title::move(int newPos)
{
    _arrow->_pos = newPos;
    _arrow->setX(x() + 15);
}


FlashingText::FlashingText() : Object(QPoint(4*TILE, 14*TILE), TILE * 8, TILE)
{
    //_pixText = Sprites::instance()->getText("PRESS S TO START", 0, QColor(255, 110, 204));
    _sprite = &_pixText;
    _animText = QRect(0, 0, TILE * 8, TILE);
    _animRect = &_animText;

    setZValue(1);
}

bool FlashingText::animate()
{
    setVisible((FRAME_COUNT / 17) % 2);
}
