#include "StaticObject.h"
#include "Game.h"
#include "Scrooge.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

using namespace DT;
StaticObject::StaticObject(QPointF pos, double width, double height) : Object(pos, width, height){
    _collider_color = Qt::yellow;
    _hit = false;
}

bool StaticObject::hit(Object* what, Direction fromDir)
{
    _hit = true;
    return true;
}
