#ifndef OCTOPUS_H
#define OCTOPUS_H

#include "Enemy.h"

namespace DT
{
    class Octopus;
}

class DT::Octopus : public Enemy
{
    private:

    public:

        Octopus(QPointF pos);

        // implemented abstract methods
        virtual std::string name() override { return "Octopus [" + std::to_string(_id) + "]"; }

        // reimplemented abstract methods
        virtual bool hit(Object* what, Direction fromDir) override;
        virtual void advance() override;
};

#endif // OCTOPUS_H
