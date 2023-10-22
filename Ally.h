#ifndef ALLY_H
#define ALLY_H
#include <QPointF>
#include "Entity.h"
#include <QPixmap>

namespace DT{
    class Ally;
}

class DT::Ally : public Entity
{
public:
    enum class Type { GIZMODUCK, LAUNCHPAD, WOMAN};
protected:
    Ally::Type _type;
    QRect _texture_ally[3];
public:

    Ally(QPointF pos, double width, double height, Ally::Type type);

    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Ally"; }
};

#endif // ALLY_H
