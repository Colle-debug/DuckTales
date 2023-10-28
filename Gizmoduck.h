#ifndef GIZMODUCK_H
#define GIZMODUCK_H
#include <QPointF>
#include "Entity.h"
#include <QPixmap>

namespace DT{
    class Gizmoduck;
}

class DT::Gizmoduck : public Entity
{
protected:
    QRect _texture_gizmoduck[2];
    bool _firing;
    bool _activated;
public:

    Gizmoduck(QPointF pos, double width, double height);

    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Gizmoduck"; }

};

#endif // GIZMODUCK_H
