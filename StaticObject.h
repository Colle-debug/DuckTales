#ifndef STATICOBJECT_H_
#define STATICOBJECT_H_

#include "Object.h"


namespace DT
{
    class StaticObject;
}

class DT::StaticObject : public Object
{
    public:

    StaticObject(QPointF pos, double width, double height) : Object(pos,width,height){}
        // implemented abstract methods
        virtual void advance() override {}
        virtual void animate() override {}

        // nonimplemented abstract methods
        virtual bool hit(Object* what, Direction fromDir) override =0;
        virtual std::string name() override = 0;
};

#endif
