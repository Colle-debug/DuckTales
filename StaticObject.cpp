
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

bool StaticObject::animate()
{
    if (_colliderVisible)
        return false;

    /*if (_hit)
    {
            if (childItems().empty())
            {
                    QGraphicsRectItem* r = new QGraphicsRectItem(collider(), this);
                    r->setPen(Qt::NoPen);
                    r->setBrush(QColor(255, 255, 0));
            }
            _hit = false;
    }
    else
    {
            for (auto& i : childItems())
                    delete i;
            childItems().clear();
    }*/

    return false;
}

bool StaticObject::hit(Object* what, Direction fromDir)
{
    _hit = true;

    return false;
}
