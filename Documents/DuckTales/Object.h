#ifndef OBJECT_H
#define OBJECT_H
#include <QGraphicsItem>
#include "Direction.h"
#include "Vec2D.h"
#include "Scheduler.h"
#include <QGraphicsPixmapItem>

namespace DT
{
    class Object;
}

class DT::Object : public QGraphicsPixmapItem
{
protected:

    QRectF _boundingRect;
    QRectF _collider;
    QColor _collider_color;

    int _id;					// for debugging
    bool _colliderVisible;		// for debugging
    bool _collidable;
    bool _compenetrable;

    QPixmap* _sprite;
    QRect* _animRect;

    std::map<std::string, Scheduler> _schedulers;

public:

    Object(QPointF pos, double width, double height);

    // getters
    int id() const { return _id; }
    QRectF boundingRect() const override { return _boundingRect; }
    QRectF collider() const { return _collider; }
    virtual bool collidable() const { return _collidable; }
    bool compenetrable() const { return _compenetrable; }

           // advanced getters for collision detection
    QRectF qsceneCollider() const;
    RectF sceneCollider() const;
    double dist(Object* obj) const;
    /*virtual Vec2Df posv() { return Vec2Df(sceneCollider().x(), sceneCollider().y()); }
    virtual Vec2Df sizev() { return Vec2Df(collider().width(), collider().height()); }
    virtual double distX(Object* obj) { return std::abs(sceneCollider().center().x() - obj->sceneCollider().center().x()); }*/
           // compute next location
    virtual void advance() = 0;

           // compute next animation
    virtual void animate() = 0;

           // hit by another object, return true if hit is resolved
    virtual bool hit(Object* what, Direction fromDir) = 0;

           // action scheduling
    virtual void schedule(const std::string& id, int delay, std::function<void()> action, bool overwrite=true);
    virtual void updateSchedulers();

           // name for debug purposes
    virtual std::string name() = 0;

           // conversion
    template <class T>
    T to() { return dynamic_cast<T>(this); }

           // show / hide collider
    void toggleCollider();

};

#endif // OBJECT_H
