#include "Hud.h"
#include "Game.h"
#include "Sprites.h"
#include <QPainter>

using namespace DT;

HUD::HUD(int w, int h, QWidget* parent) : QWidget(parent)
{
	_background = Sprites::instance()->getHUD("hud");
	_flashin_coin_timer.setInterval(150);


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
	painter.setWindow(0,0,TILE * 20.2, TILE * 9.1);
	painter.drawPixmap(0,  0, _background); 


	painter.drawPixmap(105, 15, Sprites::instance()->getNumber(1989));


}

void HUD::flashCoin()
{
	static int animation_counter = 0;
	_coin = &_flashin_coin_animation[(animation_counter++) % 6];

	update();
}

void HUD::subTime() 
{
	_time -= 1; update();
	_last_digit = _time % 10;

	if (_time == 100)
	{
		//Game::instance()->stopMusic(true);
		//Sounds::instance()->play("lowtime");
		//Sounds::instance()->speedUp();
	}
	else if (_time == 96)
		std::cout << "miao";
	else if (_time == 0)
		emit timeExpired();
}

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
