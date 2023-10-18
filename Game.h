#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
#include "GameConfig.h"
#include "Loader.h"
#include "Scrooge.h"
#include "Hud.h"

namespace DT
{
    class Game;
    class Scrooge;
    enum class GameState{READY, TITLE_SCREEN, RUNNING, PAUSED, GAME_OVER, GAME_CLEAR};
}

class DT::Game:public QGraphicsView
{
    Q_OBJECT
    enum game_state{READY, RUNNING, PAUSE, GAME_OVER};
private:
    GameState _state;
    Scrooge* _player;
    QGraphicsScene* _world;
    Loader* _builder;
    QTimer _engine;
    HUD*			_hud;
    bool _left_pressed;
    bool _right_pressed;
    bool _up_pressed;
    bool _down_pressed;
    bool _jump_pressed;
    bool _grab_pressed;
    bool _crouch_pressed;
    bool _pogo_pressed;
    bool _jump_released;
    bool _pogo_released;
    bool beagleActive;

    int startingX = 0;
    int startingY = 64;

    // singleton
    static Game* _uniqueInstance;
    Game(QGraphicsView *parent=0);
public:
    static Game* instance();
    bool grabStatus(){return _grab_pressed;}
    void setBeagleStatus(bool on){beagleActive = on;}
    QGraphicsScene* world(){return _world;}
    Scrooge* player(){return _player;}
    double aspectRatio() { return 16 * 1.14 / 15; }
    // event handlers
    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void keyReleaseEvent(QKeyEvent* e) override;
    virtual void wheelEvent(QWheelEvent* e) override;
    virtual void resizeEvent(QResizeEvent* event) override;
    void gameOver()  { _state = GameState::GAME_OVER; }

public slots:
    void reset();
    void start();
    void nextFrame();
    void gameEnd();
};
#endif

