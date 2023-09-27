#include <QBrush>
#include "Scrooge.h"
#include "Loader.h"
#include "Game.h"
#include "GameConfig.h"
//#include "StaticObject.h"
#include "StaticObject.h"

using namespace DT;

Scrooge* Loader::load(std::string levelName)
{
    if(levelName=="theMoon")
    {
        Game::instance()->world()->addPixmap(QPixmap(":/background/theMoon.png"));
                //primo livello


    }
    else{
        return nullptr;
    }
}
