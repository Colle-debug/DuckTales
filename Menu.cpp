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
    _arrow = new Arrow(QPoint(32, 129), 5, 8);
    setZValue(1);
}

void Title::advance()
{
    return;
}


Level::Level():Object(QPoint(0, 0), TILE * 30, TILE * 30)
{
    QPixmap fullPixmap = *Sprites::instance()->getSprite("level");
    QPixmap croppedPixmap = fullPixmap.copy(0, 0, 256, 224);

    QGraphicsPixmapItem* Louie = new QGraphicsPixmapItem(fullPixmap.copy(25, 226, 17, 22));
    QGraphicsPixmapItem* Hewey = new QGraphicsPixmapItem(fullPixmap.copy(45, 226, 17, 22));
    QGraphicsPixmapItem* Dewey = new QGraphicsPixmapItem(fullPixmap.copy(65, 226, 17, 22));
    QGraphicsPixmapItem* iconLeft = new QGraphicsPixmapItem(fullPixmap.copy(262, 154, 14, 10));
    QGraphicsPixmapItem* iconRight = new QGraphicsPixmapItem(fullPixmap.copy(262, 154, 14, 10));

    Louie->setPos(QPoint(9*TILE, 12.3*TILE));
    Hewey->setPos(QPoint(10*TILE + 1, 12.3*TILE));
    Dewey->setPos(QPoint(12.5*TILE, 11.3*TILE)); // nel gioco originale questo non c'è, ci sono 2 Louie: non si può guardare dai

    iconLeft->setPos(QPoint(42, 139));
    iconRight->setPos(QPoint(202, 139));


    Game::instance()->world()->addPixmap(croppedPixmap);
    Game::instance()->world()->addItem(Louie);
    Game::instance()->world()->addItem(Hewey);
    Game::instance()->world()->addItem(Dewey);
    Game::instance()->world()->addItem(iconLeft);
    Game::instance()->world()->addItem(iconRight);




    _arrow = new Arrow(QPoint(4.5*TILE + 1, 8.5*TILE + 1), 5, 8);

}

void Level::advance()
{
    return;
}
//Arrow::Arrow() : Object(QPoint(32, 129), 5, 8)
Arrow::Arrow(QPointF pos, double width, double height) : Object(pos, width, height)
{
    _pos = 0;
    prev_pos = 0;
    _sprite = Sprites::instance()->getSprite("titleArrow");
    Sprites::instance()->get("title-arrow", &_anim[0]);
    _animRect = &_anim[0];
}


void Arrow::advance()
{
    if(Game::instance()->state() == Game::GameState::TITLE_SCREEN){
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
}

bool Arrow::animate()
{
    return true;
}





