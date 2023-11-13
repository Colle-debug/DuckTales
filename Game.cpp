#include "Game.h"
#include "BBoy.h"
#include "GameConfig.h"
#include "Loader.h"
#include "Scheduler.h"
#include "Object.h"
#include "Scrooge.h"
#include "Hud.h"
#include "BBoy.h"
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QApplication>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QMediaPlayer>
#include "Sounds.h"
#include "Menu.h"
using namespace DT;

Game* Game::_uniqueInstance = 0;
Game* Game::instance()
{
    if (_uniqueInstance == 0)
        _uniqueInstance = new Game();
    return _uniqueInstance;
}


Game::Game(QGraphicsView *parent) : QGraphicsView(parent)
{
    _world = new QGraphicsScene();
    _world->setSceneRect(0, 0, TILE * 128, TILE * 86.5); // Vista di default è 0 56.5
    setScene(_world);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setInteractive(false);
    //Game::instance()->world()->setBackgroundBrush(QBrush(QImage(":/background/theMoon.png")));

    QObject::connect(&_engine, SIGNAL(timeout()), this, SLOT(nextFrame()));
    _engine.setInterval(1000 / 60);
    _engine.setTimerType(Qt::PreciseTimer);

    _builder = new Loader();
    _player = 0;
    beagleActive = 1;

    /*
    QOpenGLWidget* gl = new QOpenGLWidget();
    setViewport(gl);
    */
    _hud = new HUD(width(), height(), this);

    connect(_hud, SIGNAL(timeExpired()), this, SLOT(timeExpired()));
    reset();
}

void Game::reset()
{
    _state = GameState::READY;
    _engine.stop();
    _world->clear();
    //_world->setSceneRect(0, 0, TILE * 30, TILE * 30);
    _hud->setVisible(false);
    _hud->reset();
    _player = 0;
    beagleActive = 1;
    _arrowPos = 0;
    _bossFight = 0;
    _bossFightAnimation = 0;
    _left_pressed = false;
    _right_pressed = false;
    _up_pressed = false;
    _down_pressed = false;
    _jump_pressed = false;
    _jump_released = false;
    _crouch_pressed = false;
    _grab_pressed = false;
    _swing_pressed = false;
    _swing_released = false;


    _current_music_loop = _level_music_loop ="";

    QTimer::singleShot(0, this, &Game::welcome);
}


void Game::welcome()
{
    if (_state == GameState::READY)
    {
        _state = GameState::TITLE_SCREEN;
        _world->clear();
        _engine.setInterval(1000 / (FPS/2)); // 30 FPS per avere l'occhiolino nel menù iniziale come nel gioco originale
        _engine.start();
        //Sounds::instance()->stopMusic(_music);
        Loader::load("Title");
        //Sounds::instance()->playMusic(_music, false);
    }
}

void Game::levelSelection()
{
    _state = GameState::LEVEL_SELECTION;
    _world->clear();
    Loader::load("Level");
    _player = _builder->load("levelSelection");
}

void Game::gizmo()
{
    for (auto item: _world -> items()) {
        Gizmoduck * gizmo = dynamic_cast < Gizmoduck * > (item);
        if(gizmo){
            gizmo->activate();
            _player->setGizmoCinematicStatus(true);
        }
    }
}

void Game::bossFight()
{
    _bossFight = true;
    _bossFightAnimation = true;
    _player->startBossFightAnimation();
}

void Game::start()
{
    std::cout<<"Start\n";
    std::cout.flush();
    if (_state == GameState::LEVEL_SELECTION){
        FRAME_COUNT = 0;
        _state = GameState::RUNNING;
        _world->clear();
        //_world->setSceneRect(64*TILE, 75*TILE, TILE * 64, TILE * 11.5);
        _engine.setInterval(1000 / FPS);
        _engine.start();
        _hud->setVisible(true);
        _hud->start();
        _player = _builder->load("theMoon");
        _player->setSitting(false);
        //QMediaPlayer * music= new QMediaPlayer();
        playMusic("themoontheme");

    }
}

void Game::nextFrame() {
    FRAME_COUNT++;
    if (_state == GameState::TITLE_SCREEN || _state == GameState::LEVEL_SELECTION){ // era if (_state != GameState::RUNNING && _state != GameState::TITLE_SCREEN), non ne capisco il senso, da vedere

        /*std::cout<<_arrowPos<<"\n";
            std::cout.flush();
            */
        for (auto item: _world -> items()) {
            Object * obj = dynamic_cast < Object * > (item);

            if (obj && (obj -> isVisible())) {
                obj -> advance(); // physics, collision detection and resolution, game logic
                obj -> animate(); // animation
                //obj -> updateSchedulers(); // game logic
                //obj->paint();			 // graphics, automatically called by Qt
            }
        }

        return;

    }





    // process inputs	 (PLAYER CONTROLS)

    if(!_player->gizmoduckCinematic() && !_player->launchpadAttachment() && !_bossFightAnimation && !_player->respawningGF()){ // Commandi di movimento accessibili solo se nessuna delle due è True
        if (!_player -> climbing()) {
            if (_left_pressed && _right_pressed)
                _player -> move(Direction::NONE);
            else if (_left_pressed || _player -> launchpadAttachment())
                _player -> move(Direction::LEFT);
            else if (_right_pressed)
                _player -> move(Direction::RIGHT);
            else
                _player -> move(Direction::NONE);

            if (_grab_pressed) {
                _player -> grab(true);
                _grab_pressed = false;
            }

            if (_pogo_pressed) // Qui va aggiunta una condizione che non consente di attivare il pogo se si è a terra ma che non impedisca di rimbalzare quando si è in pogoing
            {
                _player -> pogo(true);
            } else if (_pogo_released) {
                _player -> pogo(false);
                _pogo_released = false;
            }
            if (_crouch_pressed && !_pogo_pressed) {
                _player -> crouch(true);
                _player -> move(Direction::NONE);

            } else
                _player -> crouch(false);

        } else {
            if (_down_pressed && _up_pressed) {
                std::cout << "if(_down_pressed && _up_pressed)\n";
                std::cout.flush();
                _player -> move(Direction::NONE);
            } else if (_up_pressed) {
                std::cout << "else if(_up_pressed)\n";
                std::cout.flush();
                _player -> move(Direction::UP);
            } else if (_down_pressed) {
                std::cout << "else if(_down_pressed)\n";
                std::cout.flush();
                _player -> move(Direction::DOWN);
            } else
                _player -> move(Direction::NONE);
            if (_jump_pressed) {
                _player -> setClimbing(false);
            }

        }
        if (_swing_pressed) {
            _player -> swing(true);
            _swing_pressed = false;

        } else if (_swing_released) {
            _player -> swing(false);
            _swing_released = false;

        }

        if (_jump_pressed) {
            _player -> jump(true);
            _jump_pressed = false;
        } else if (_jump_released) {
            _player -> jump(false);
            _jump_released = false;
        }
    }
    if (!beagleActive && !_bossFight && _player->x() > 90*TILE && _player->y() > 70 * TILE) {
        std::cout<<"Respawning\n";
        std::cout.flush();
        // Meglio schedulare il respawn dopo un paio di FRAME
        beagleActive = true;
        _player -> schedule("restore", 100, [this]() {
            spawningPoint();
        });
        /*spawningPoint(); // Respawing naive, funzione per valutare il primo blocco utile su cui potersi poggiare
            beagleActive = true; // C'è unironically un memory leak...
*/
    }

    for (auto item: _world -> items()) {
        Object * obj = dynamic_cast < Object * > (item);

        if (obj && (obj -> isVisible() || (dynamic_cast < Enemy * > (item) && !dynamic_cast < BBoy * >(item) && !dynamic_cast < Enemy * > (item)->isVisible()))) { // Enemy: ho bisogno che updati anche se invisibili per il respawning, MA NON PER BBOY
            obj -> advance(); // physics, collision detection and resolution, game logic
            obj -> animate(); // animation
            obj -> updateSchedulers(); // game logic
            //obj->paint();			 // graphics, automatically called by Qt
        }
    }

    // @TODO update game state (game over, level cleared, etc.)
    centerOn(_player);
    update();

    if (_player -> dead()) {
        gameOver();
    }else if(_player->duckburg()){
        liftToDuckburg();
    }


    if (_state == GameState::GAME_OVER || _state == GameState::GAME_CLEAR || _state == GameState::LIFT_TO_DUCKBURG) {
        gameEnd();
    }
}

void Game::keyPressEvent(QKeyEvent * e) {
    if (e -> isAutoRepeat())
        return;
    // Game controls
    if (e -> key() == Qt::Key_S){
        if(_state == GameState::TITLE_SCREEN){
            levelSelection();}
        else if(_state == GameState::LEVEL_SELECTION){
            start();
        }
    }
    else if (e -> key() == Qt::Key_R)
        reset();
    /*
    else if (e->key() == Qt::Key_P)
        togglePause();
    */
    else if (e -> key() == Qt::Key_C) {
        for (auto item: _world -> items()) {
            if (dynamic_cast < Object * > (item)) {
                dynamic_cast < Object * > (item) -> toggleCollider();
            }
        }
    } else if (e -> key() == Qt::Key_Minus) {
        _engine.setInterval(250);
    } else if (e -> key() == Qt::Key_Plus) {
        _engine.setInterval(1000 / FPS);
    }

    // Player controls
    if ((_state == GameState::RUNNING && _player)) // if (_state == GameState::RUNNING && _player)
    {
        if (e -> key() == Qt::Key_Left) {

            _left_pressed = true;

        } else if (e -> key() == Qt::Key_Right) {

            _right_pressed = true;

        } else if (e -> key() == Qt::Key_Down) {
            if (!_player -> climbing()) {
                _crouch_pressed = true;
            } else {
                _down_pressed = true;
            }
        } else if (e -> key() == Qt::Key_Space) {
            _jump_pressed = true;
            _jump_released = false;
        } else if (e -> key() == Qt::Key_X) {
            _swing_pressed = true;
            _swing_released = false;

        } else if (e -> key() == Qt::Key_Up) {
            if (_player -> climbing()) {
                _up_pressed = true;
            } else {
                _grab_pressed = true;
            }
        } else if (e -> key() == Qt::Key_Z) {
            _pogo_pressed = true;
        }

        // Cheats
        /*
        else if (e->key() == Qt::Key_I)
        {
            // invincibility
        }
        */
        else if (e -> key() == Qt::Key_K) {
            startingX++;
            setSceneRect(TILE * startingX, TILE * startingY, TILE * 128, TILE * 15);
        } else if (e -> key() == Qt::Key_H) {
            startingX--;
            setSceneRect(TILE * startingX--, TILE * startingY, TILE * 128, TILE * 15);
        } else if (e -> key() == Qt::Key_U) {
            startingY--;
            setSceneRect(TILE * startingX, TILE * startingY, TILE * 128, TILE * 15);
        } else if (e -> key() == Qt::Key_J) {
            startingY++;
            setSceneRect(TILE * startingX, TILE * startingY, TILE * 128, TILE * 15);
        }
    } else if (_state == GameState::TITLE_SCREEN) {
        if (e -> key() == Qt::Key_Left && _arrowPos > 0) {
            _arrowPos--;
        } else if (e -> key() == Qt::Key_Right && _arrowPos < 2) {
            _arrowPos++;
        }
    }
}


void Game::keyReleaseEvent(QKeyEvent* e)
{
    if (e->isAutoRepeat())
        return;

    // player controls
    if ((_state == GameState::RUNNING || _state == GameState::TITLE_SCREEN) && _player)
    {
        if (e->key() == Qt::Key_Left)
            _left_pressed = false;
        else if (e->key() == Qt::Key_Right)
            _right_pressed = false;
        else if (e->key() == Qt::Key_Space)
        {
            _jump_pressed = false;
            _jump_released=true;
        }
        else if (e->key() == Qt::Key_Down){
            if(_player->climbing()){
                _down_pressed = false;
            }
            else{
                _crouch_pressed = false;
            }
        }
        else if (e->key() == Qt::Key_X)
        {

            _swing_pressed=false;
            _swing_released=true;

        }

        else if (e->key() == Qt::Key_Up){
            if(_player->climbing()){
                _up_pressed = false;
            }
        }
        else if (e->key() == Qt::Key_Z){
            _pogo_pressed = false;
            _pogo_released = true;
        }
    }
}


void Game::wheelEvent(QWheelEvent* e)
{

    if (e->angleDelta().y() > 0)
        scale(1.1, 1.1);
    else
        scale(1 / 1.1, 1 / 1.1);

}

void Game::resizeEvent(QResizeEvent* evt)
{
    fitInView(0, 0, TILE * 16-4, TILE * 15-4);
}

void Game::spawningPoint()
{
    BBoy *test = new BBoy(QPointF(_player->x() - 6* TILE, _player->y() - 2*TILE));
}

void Game::gameEnd()
{
    //std::cout<<_player->dead();
    if (_state == GameState::GAME_OVER){
    }
    if (_state != GameState::GAME_CLEAR && _state != GameState::GAME_OVER && _state != GameState::LIFT_TO_DUCKBURG)
        return;

    _engine.stop();
    _hud->togglePause();
    //stopMusic();
    //Sounds::instance()->reset();
    if (_state == GameState::GAME_CLEAR)
        std::cout<<"Game Cleared";
    //playMusic("princessmusic");
    else if (_state == GameState::GAME_OVER)
        //Sounds::instance()->play("gameover");
        std::cout<<"Game Over";

    if (_state == GameState::GAME_CLEAR)
    {/*
        _player->setX(7 * TILE);
        _player->resetAfterScript();*/
    }
    else{
        _world->clear();
    }

    // vedi cosa fa in Supermario-2021
    //screen->setY(-TILE * 12.0);

    //setSceneRect(QRectF());
    //centerOn(0, 0);
}

void Game::playMusic(const std::string& name)
{
    if (!_current_music_loop.empty())
        Sounds::instance()->stop(_current_music_loop);

    _current_music_loop = name;
    if(!_current_music_loop.empty())
        Sounds::instance()->play("themoontheme", true);
}

void Game::stopMusic(bool resumable)
{
    if (!_current_music_loop.empty())
        Sounds::instance()->stop(_current_music_loop, resumable);
}

void Game::resumeMusic()
{
    if (!_current_music_loop.empty())
        Sounds::instance()->resume(_current_music_loop);
}

void Game::restoreLevelMusic()
{
    if (!_current_music_loop.empty())
        playMusic(_level_music_loop);
}


