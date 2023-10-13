#pragma once

#include "Entity.h"
#include <map>

namespace DT
{
    class DynamicPlatform;
}

class DT::DynamicPlatform : public Entity
{
    protected:

        std::map<Entity*, Direction> _attached;

    public:

        DynamicPlatform(QPointF pos, double width, double height);

        // implemented abstract methods
        virtual void advance() override;
        virtual bool hit(Object* what, Direction fromDir) override;

        // nonimplemented
        virtual bool animate() override = 0;
        virtual std::string name() override = 0;
};
