#include "Game.h"
#include "GameConfig.h"
#include "Loader.h"
#include "Scrooge.h"
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QApplication>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QBrush>

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
    _world->setSceneRect(TILE * 0, TILE * 56.5, TILE * 128, TILE * 15); // Vista di default è 0 56.5
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

    /*
    QOpenGLWidget* gl = new QOpenGLWidget();
	setViewport(gl);
    */

    reset();
}

void Game::reset()
{
    _state = GameState::READY;
    _engine.stop();
    _world->clear();

    _player = 0;

    _left_pressed = false;
    _right_pressed = false;

    _jump_pressed = false;

    _fire_pressed = false;
    _crouch_pressed = false;

    //restoreDefaultView();
	_state = GameState::READY;
	_engine.stop();
	_world->clear();
    //_world->setBackgroundBrush(QBrush(Qt::black));
	_player = 0;
	_left_pressed = false;
	_right_pressed = false;
	_jump_pressed = false;
	_fire_pressed = false;
    _jump_released = false;

    //setSceneRect(QRectF());

	QTimer::singleShot(0, this, &Game::start);
}

void Game::start()
{
        FRAME_COUNT = 0;
        _state = GameState::RUNNING;
        _world->clear();
        _engine.start();
        _player = _builder->load("theMoon"); //Momentaneamente commentato finchè Loader non verrà implementata, da qui si piazza Scrooge
}

void Game::nextFrame()
{
	if (_state != GameState::RUNNING && _state != GameState::TITLE_SCREEN)
		return;

    FRAME_COUNT++;

    // process inputs	 (PLAYER CONTROLS)
	if (_state == GameState::RUNNING && !_player->dying())
	{
		if (_left_pressed && _right_pressed)
			_player->move(Direction::NONE);
		else if (_left_pressed)
			_player->move(Direction::LEFT);
		else if (_right_pressed)
			_player->move(Direction::RIGHT);
		
		else
            _player->move(Direction::NONE);
  
        if (_crouch_pressed)
        {
			_player->crouch(true);
            _player->move(Direction::NONE);
        }
        else 
			_player->crouch(false);
            

		if (_jump_pressed)
		{
			_player->jump(true);
			_jump_pressed = false;
        }
        else if (_jump_released)
		{
			_player->jump(false);
			_jump_released = false;
		}
	}

	// advance game
	for (auto item : _world->items())
	{
		Object* obj = dynamic_cast<Object*>(item);

		if (obj && obj->isVisible())
		{
			obj->advance();			 // physics, collision detection and resolution, game logic
            obj->animate();			 // animation
			obj->updateSchedulers(); // game logic
			//obj->paint();			 // graphics, automatically called by Qt
		}
	}

	// @TODO update game state (game over, level cleared, etc.)
    centerOn(QPointF(_player->x(), _player->y()));
    update();

    if(_player->dead()){
        gameOver();
    }
    if (_state == GameState::GAME_OVER || _state == GameState::GAME_CLEAR){
        gameEnd();
    }

}

void Game::keyPressEvent(QKeyEvent* e)
{
    if (e->isAutoRepeat())
        return;
    // Game controls
    if (e->key() == Qt::Key_S)
        start();
    /*
    else if (e->key() == Qt::Key_R)
        reset();
    else if (e->key() == Qt::Key_P)
        togglePause();
    */
    else if (e->key() == Qt::Key_C)
    {
        for (auto item : _world->items())
        {
            if (dynamic_cast<Object*>(item))
            {
                dynamic_cast<Object*>(item)->toggleCollider();
            }
        }
    }
    else if (e->key() == Qt::Key_Minus)
    {
        _engine.setInterval(250);
    }
    else if (e->key() == Qt::Key_Plus)
    {
        _engine.setInterval(1000 / FPS);
    }

    // Player controls
    if (_state == GameState::RUNNING && _player)
    {
        if (e->key() == Qt::Key_Left)
        {
            _left_pressed = true;
        }
        else if (e->key() == Qt::Key_Right)
        {
            _right_pressed = true;
        }
        else if (e->key() == Qt::Key_Down)
			
            _crouch_pressed = true;
            
        else if (e->key() == Qt::Key_Space)
        {
            _jump_pressed = true;
            _jump_released = false;
        }
        else if (e->key() == Qt::Key_F)
        {
            _fire_pressed = true;
        }

        // Cheats
        /*
        else if (e->key() == Qt::Key_I)
        {
            // invincibility
        }
        */
        else if (e->key() == Qt::Key_K)
        {
            startingX++;
            setSceneRect(TILE * startingX, TILE * startingY, TILE * 128, TILE * 15);
        }
        else if (e->key() == Qt::Key_H)
        {
            startingX--;
            setSceneRect(TILE * startingX--, TILE * startingY, TILE * 128, TILE * 15);
        }
        else if (e->key() == Qt::Key_U)
        {
            startingY--;
            setSceneRect(TILE * startingX, TILE * startingY, TILE * 128, TILE * 15);
        }
        else if (e->key() == Qt::Key_J)
        {
            startingY++;
            setSceneRect(TILE * startingX, TILE * startingY, TILE * 128, TILE * 15);
        }
    }
}


void Game::keyReleaseEvent(QKeyEvent* e)
{
	if (e->isAutoRepeat())
		return;

	// player controls
	if (_state == GameState::RUNNING && _player)
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
        else if (e->key() == Qt::Key_Down)
			_crouch_pressed = false;    
		else if (e->key() == Qt::Key_F)
			_fire_pressed = false;
            
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

void Game::gameEnd()
{
    std::cout<<_player->dead();
    if (_state == GameState::GAME_OVER){
        std::cout<<"Lollez";
    }
    if (_state != GameState::GAME_CLEAR && _state != GameState::GAME_OVER)
        return;

    _engine.stop();
    //_hud->togglePause();
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
