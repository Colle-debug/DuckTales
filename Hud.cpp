#include "Hud.h"
#include "Game.h"
#include "Sprites.h"
//#include "Sounds.h"
#include <QPainter>

using namespace DT;

HUD::HUD(int w, int h, QWidget* parent) : QWidget(parent)
{
    //_background = Sprites::instance()->get("hud"); //Va modificata la funzione di get o se ne ridefinisce un'altra con lo stesso nome senza secondo parametro
    _flashin_coin_timer.setInterval(150);

    /*_flashin_coin_animation[0] = Sprites::instance()->get("hud-coin-0");
    _flashin_coin_animation[1] = Sprites::instance()->get("hud-coin-1");
    _flashin_coin_animation[2] = Sprites::instance()->get("hud-coin-2");
    _flashin_coin_animation[3] = Sprites::instance()->get("hud-coin-1");
    _flashin_coin_animation[4] = Sprites::instance()->get("hud-coin-0");
    _flashin_coin_animation[5] = Sprites::instance()->get("hud-coin-0");
*/
    _coin = &_flashin_coin_animation[0];

    QObject::connect(&_flashin_coin_timer, SIGNAL(timeout()), this, SLOT(flashCoin()));
    _flashin_coin_timer.start();

    resize(w, h);

    reset();
}

void HUD::start()
{
    _time = 400;
}

void HUD::reset()
{
    _score = 0;
    _coins = 0;
    _world = 1;
    _level = 1;
    _time = -1;
    _fps = 0;
    _last_digit = 0;
    _score_items.clear();
}



void HUD::togglePause()
{
    if (_flashin_coin_timer.isActive())
        _flashin_coin_timer.stop();
    else
        _flashin_coin_timer.start();
}

void HUD::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setBackgroundMode(Qt::TransparentMode);
    painter.setWindow(0, +2, TILE * 16, TILE * 15);
    painter.drawPixmap(25,  15, _background);
    /*painter.drawPixmap(25,  23, Sprites::instance()->getNumber(_score, 6));
    painter.drawPixmap(89,  15,  Sprites::instance()->getString("F"));
    painter.drawPixmap(105, 15, Sprites::instance()->getNumber(_fps));
    painter.drawPixmap(89,  23, *_coin);
    painter.drawPixmap(105, 23, Sprites::instance()->getNumber(_coins, 2));
    painter.drawPixmap(153, 23, Sprites::instance()->getNumber(_world));
    painter.drawPixmap(169, 23, Sprites::instance()->getNumber(_level));*/
    if(_time >= 0)
        //painter.drawPixmap(209, 23, Sprites::instance()->getNumber(_time, 3));
    for (auto& s : _score_items)
        s.draw(&painter);
}

void HUD::flashCoin()
{
    static int animation_counter = 0;
    _coin = &_flashin_coin_animation[(animation_counter++) % 6];

    update();
}

/*void HUD::subTime() // Da quanto ho capito questo serve a cambiare la musica in base al tempo, in Scrooge non dovrebbe esserci
{
    _time -= 1; update();
    _last_digit = _time % 10;

    if (_time == 100)
    {
        /*Game::instance()->stopMusic(true);
        Sounds::instance()->play("lowtime");
        Sounds::instance()->speedUp();
    }
    else if (_time == 96)
        //Game::instance()->resumeMusic();
    else if (_time == 0)
        emit timeExpired();
}*/

void HUD::addScore(int s, QPointF pos)
{
    _score += s;
    if(pos != QPointF(-1, -1))
        _score_items.push_back(ScoreItem(s, pos));
    update();
}


void HUD::advance()
{
    for (auto & s : _score_items)
        s++;

    /*if (_castle_clear && _time > 0)
    {
        _score += 50;
        _time--;
        if(_time % 10)
            Sounds::instance()->play("scorering");
        if (_time == 0)
            _castle_clear->cleared(_last_digit);
    }*/

    update();
}

ScoreItem::ScoreItem(int score, QPointF pos)
{
    _expired = false;
    _origin = Game::instance()->mapFromScene(pos);
    _origin.setX(_origin.x() / Game::instance()->transform().m11());
    _origin.setY(_origin.y() / Game::instance()->transform().m22());

    if(score == 0)	// oneup
        //Sounds::instance()->play("oneup");
    _age = 0;
    //_texture = Sprites::instance()->getScore(score);
}

void ScoreItem::operator++(int)
{
    if (!_expired)
        _expired = ++_age == 120;
}

void ScoreItem::draw(QPainter* painter)
{
    if(!_expired)
        painter->drawPixmap(_origin + QPointF(0, -_age * 0.5), _texture);
}
