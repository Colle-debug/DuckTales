#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
#include "GameConfig.h"
#include "Gizmoduck.h"
#include "Loader.h"
#include "Scrooge.h"
#include "Hud.h"
#include "Menu.h"

namespace DT
{
    class Game;
    class Scrooge;
}

class DT::Game:public QGraphicsView
{
    Q_OBJECT
    enum class GameState{READY, TITLE_SCREEN, RUNNING, PAUSED, GAME_OVER, GAME_CLEAR, LIFT_TO_DUCKBURG};
private:
    GameState _state;
    Scrooge* _player;
    QGraphicsScene* _world;
    Loader* _builder;
    QTimer _engine;
    HUD*			_hud;
    Title* _title;

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
    bool _swing_pressed;
    bool _swing_released;
    std::string		_level_music_loop;
		std::string		_current_music_loop;

    int _arrowPos = 0;
    int startingX = 0;
    int startingY = 64;

    // singleton
    static Game* _uniqueInstance;
    Game(QGraphicsView *parent=0);

public:
    static Game* instance();
    bool grabStatus(){return _grab_pressed;}
    void setBeagleStatus(bool on){beagleActive = on;}
    int arrowPos(){return _arrowPos;}
    void setArrowPos(int on){_arrowPos = on;}
    QGraphicsScene* world(){return _world;}
    void setTitle(Title* on){_title = on;}

    Scrooge* player(){return _player;}
    HUD* hud() { return _hud; }
    double aspectRatio() { return 16 * 1.14 / 15; }
    // event handlers
    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void keyReleaseEvent(QKeyEvent* e) override;
    virtual void wheelEvent(QWheelEvent* e) override;
    virtual void resizeEvent(QResizeEvent* event) override;
    void gameOver()  { _state = GameState::GAME_OVER; }
    void welcome();
    void liftToDuckburg() { _state = GameState::LIFT_TO_DUCKBURG;}
    
    void spawningPoint();

public slots:
    void reset();
    void start();
    void nextFrame();
    void gameEnd();
    void playMusic(const std::string& name);
		void stopMusic(bool resumable = false);
		void resumeMusic();
		void restoreLevelMusic();
   
};
#endif

