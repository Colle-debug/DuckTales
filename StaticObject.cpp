#include "StaticObject.h"
#include "Game.h"
#include "Scrooge.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

using namespace DT;
StaticObject::StaticObject(QPointF pos, double width, double height, StaticObject::Type type) : Object(pos, width, height){
    _type = type;
    _hit = false;
    if(_type == Type::ROPE){
        _compenetrable = true;
        _rope = 1;
    }
    else if(_type == Type::BUMPER){
        _compenetrable = true;
        _bumper = 1;
    }


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
    Scrooge* scrooge = dynamic_cast<Scrooge*>(what);
    if(scrooge && scrooge->hasTheKey() && this->_type == Type::GATE){
        _compenetrable = true;
        return true;
    }
    _hit = true;
    return false;
}



