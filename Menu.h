#pragma once

#include "Object.h"

namespace DT
{
class Title;
class FlashingText;
class Arrow;
class Level;
}

class DT::Title : public Object
{
private:

    QRect _animTitle;
    bool _moving;
    Arrow* _arrow;

public:

    Title();
    Arrow* arrow(){return _arrow;}

    // implemented abstract methods
    virtual void advance() override;
    virtual bool animate() override {}
    virtual bool hit(Object* what, Direction fromDir) override { return true; }
    virtual std::string name() override { return "Title"; }
};



class DT::Level : public Object
{
public:
    Level();

    virtual void advance() override;
    virtual bool animate() override {}
    virtual bool hit(Object* what, Direction fromDir) override { return true; }
    virtual std::string name() override { return "Level"; }

};


class DT::Arrow : public Object
{
private:
    friend class Title;

    QRect _anim[1];
    int _animCounter;
    int _pos;
    int prev_pos;

public:

    Arrow();

    // implemented abstract methods
    virtual void advance() override;
    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override { return true; }
    virtual std::string name() override { return "Arrow"; }
};








