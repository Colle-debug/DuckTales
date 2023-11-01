#pragma once

#include "Object.h"

namespace DT
{
class Title;
class FlashingText;
class Arrow;
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
    void move(int newPos);

    // implemented abstract methods
    virtual void advance() override;
    virtual bool animate() override {}
    virtual bool hit(Object* what, Direction fromDir) override { return true; }
    virtual std::string name() override { return "Title"; }
};




class DT::Arrow : public Object
{
private:

    QRect _anim[1];
    int _animCounter;
    int _pos = 0;

public:

    Arrow();

    // implemented abstract methods
    virtual void advance() override;
    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override { return true; }
    virtual std::string name() override { return "Arrow"; }
    friend class Title;
};


class DT::FlashingText : public Object
{
private:

    QPixmap _pixText;
    QRect _animText;

public:

    FlashingText();

    // implemented abstract methods
    virtual void advance() override {}
    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override { return true; }
    virtual std::string name() override { return "FlashingText"; }
};




