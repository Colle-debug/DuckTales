#include "Sprites.h"
#include <QBitmap>
#include <string>
#include <QPainter>
#include <QPixmap>


// utility function
QRect moveBy(QRect rect, int x, int y, int dx = 25, int dy = 30, int border_x = 1, int border_y = 1)
{
    rect.moveTo(QPoint(rect.x() + x*dx , rect.y() + y*dy + y*border_y));
    return rect;
}

QRect moveScroogeBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
    return moveBy(rect, x, y, dx, dy, 0, 0);
}

static QPixmap loadTextureTransparent(const std::string & file, QColor mask_color = Qt::white)
{
    QPixmap pixmap(file.c_str());
    pixmap.setMask(pixmap.createMaskFromColor(mask_color));
    return pixmap;
}

// load texture from image file
// transparent pixel are identified with the given color
// if an image format not supporting transparency is used (e.g. like .bmp)
static QPixmap loadTexture(const std::string file, QColor mask_color = Qt::white)
{
  //if(strends(file, ".bmp"))
    return loadTextureTransparent(file, mask_color);
    //else
    //return QPixmap(file.c_str());
}

// main object positions within sprites
static QRect scrooge_stand(1, 1, 24, 30);
static QRect _pinkAlien(42,5,32,35);
static QRect _octopus(4,7,16,24);
static QRect _platform(79,31,33,17);
static QRect _beagleBoy(113,7,25,32);
static QRect _block(111,31,16,16);
static QRect _sphere(16,32,16,16);

Sprites* Sprites::instance()
{
    static Sprites uniqueInstance;
    return &uniqueInstance;
}

Sprites::Sprites()
{
    scrooge = loadTexture(":/sprites/scroogeNew.png", QColor(0, 89, 255, 255));
    pinkAlien = loadTexture(":/sprites/enemies.png", QColor(255,0,255));
    octopus = loadTexture(":/sprites/enemies.png", QColor(255,0,255));
    beagleBoy = loadTexture(":/sprites/enemies.png", QColor(255,0,255));
    platform = loadTexture(":/sprites/itemsupdated.png", QColor(255,0,255));
    block = loadTexture(":/sprites/itemsupdated.png", QColor(255,0,255));
    sphere = loadTexture(":/sprites/itemsupdated.png", QColor(255,0,255));
}

QPixmap* Sprites::getSprite(const std::string& id)
{
    if(id=="scrooge")
        return &scrooge;
    else if(id=="pinkAlien")
        return &pinkAlien;
    else if(id=="octopus")
        return &octopus;
    else if(id=="platform")
        return &platform;
    else if(id=="beagleBoy")
        return &beagleBoy;
    else if(id=="block")
        return &block;
    else if (id=="sphere")
        return &sphere;    

    else
        return 0;
}

void Sprites::get(const std::string & id, QRect animOutput[])
{
    if      (id == "scrooge-stand"){
        //animOutput[0] = moveBy(scrooge_stand,0,0);
        animOutput[0] = moveBy(scrooge_stand,0,0);
    }
    else if(id == "scrooge-walk-0"){
        animOutput[0] = moveBy(scrooge_stand,1,0);
    }
    else if(id == "scrooge-walk-1"){
        animOutput[0] = moveBy(scrooge_stand,2,0);
    }
    else if(id == "scrooge-walk-2"){
        animOutput[0] = moveBy(scrooge_stand,3,0);
    }
    else if(id == "scrooge-jump-fall"){
        animOutput[0] = moveBy(scrooge_stand,4,0);
    }
     else if(id == "scrooge-dying"){
        animOutput[0] = moveBy(scrooge_stand,5,0);
    }
    else if(id == "scrooge-bounce-0"){
        animOutput[0] = moveBy(scrooge_stand,0,2);
    }else if(id == "scrooge-bounce-1"){
        animOutput[0] = moveBy(scrooge_stand,1,2);
    }
    else if(id == "scrooge-crouch-0"){
        animOutput[0] = moveBy(scrooge_stand,2,2);
    }
    else if(id == "scrooge-crouch-1"){
        animOutput[0] = moveBy(scrooge_stand,3,2);
    }
    else if(id == "scrooge-stuck"){
        animOutput[0] = moveBy(scrooge_stand,4,2);
    }
    else if(id == "scrooge-climb-0"){
        animOutput[0] = moveBy(scrooge_stand,5,2);
    }
    else if(id == "scrooge-climb-1"){
        animOutput[0] = moveBy(scrooge_stand,0,4);
    }
    else if(id == "scrooge-preputt-0"){
        animOutput[0] = moveBy(scrooge_stand,1,4);
    }
    else if(id == "scrooge-preputt-1"){
        animOutput[0] = moveBy(scrooge_stand,2,4);
    }
    else if(id == "scrooge-putt-0"){
        animOutput[0] = moveBy(scrooge_stand,3,4);
    }
    else if(id == "scrooge-putt-1"){
        animOutput[0] = moveBy(scrooge_stand,4,4);
    }
    else if(id == "scrooge-putt-success-0"){
        animOutput[0] = moveBy(scrooge_stand,5,4);
    }
    else if(id == "scrooge-putt-success-1"){
        animOutput[0] = moveBy(scrooge_stand,0,6);
    }
    else if(id == "scrooge-putt-fail-0"){
        animOutput[0] = moveBy(scrooge_stand,1,6);
    }
    else if(id == "scrooge-putt-fail-1"){
        animOutput[0] = moveBy(scrooge_stand,2,6);
    }
    else if(id == "pink-alien-0"){
        animOutput[0] = moveBy(_pinkAlien,0,0);
    }
    else if(id == "pink-alien-1"){
        animOutput[0] = moveBy(_pinkAlien,1,1,34,1);
    }
    else if(id == "octopus-0"){
        animOutput[0] = moveBy(_octopus,0,0);
    }
    else if(id == "octopus-1"){
        animOutput[0] = moveBy(_octopus,1,0,19);
    }
    else if(id == "beagleBoy-0"){
        animOutput[0] = moveBy(_beagleBoy,0,0);
    }
    else if(id == "beagleBoy-1"){
        animOutput[0] = moveBy(_beagleBoy,1,0,26);
    }
    else if(id == "beagleBoy-2"){
        animOutput[0] = moveBy(_beagleBoy,1,0,53);
    }
    else if(id == "platform")
    {
        animOutput[0] = moveBy(_platform,0,0);
    }
     else if(id == "block-0"){
        animOutput[0] = moveBy(_block,0,0);
    }
     else if(id == "block-1"){
        animOutput[0] = moveBy(_block,-1,0,96);
    }
    else if(id == "block-2"){
        animOutput[0] = moveBy(_block,-1,0,112);
    }
     else if(id == "sphere"){
        animOutput[0] = moveBy(_sphere,0,0);
     }

   

    else
    {
        printf("warning: cannot get texture \"%s\"\n", id.c_str());
        //return QPixmap();
    }
}

/*QPixmap Sprites::getNumber(int n, int fill)
{
    std::string text = std::to_string(n);

    // fill with 0s on the left
    if (fill)
        while (text.size() != fill)
            text = '0' + text;

    // create collage texture
    QPixmap collage(8 * int(text.size()), 8);
    QPainter painter(&collage);

    // add numbers
    for (int i = 0; i < text.size(); i++)
        painter.drawPixmap(8* i, 0, Sprites::instance()->get(std::string("number-") + text[i]));

    // end painting (necessary for setMask)
    painter.end();

    // make background transparent
    collage.setMask(collage.createMaskFromColor(QColor(147, 187, 236)));

    return collage;
}

QPixmap Sprites::getString(std::string text, int fill)
{
    // fill with 0s on the left
    if (fill)
        while (text.size() != fill)
            text = ' ' + text;

    // create collage texture
    QPixmap collage(8 * int(text.size()), 8);
    QPainter painter(&collage);

    // add letters
    for (int i = 0; i < text.size(); i++)
        if(text[i] != ' ')
            painter.drawPixmap(8 * i, 0, Sprites::instance()->get(std::string("char-") + text[i]));

    // end painting (necessary for setMask)
    painter.end();

    // make background transparent
    collage.setMask(collage.createMaskFromColor(QColor(147, 187, 236)));

    return collage;
}

// score composite from sprite single score pieces
QPixmap Sprites::getScore(int s)
{
    bool thousands = s >= 1000;
    int base_score = s / (thousands ? 100 : 10);

    QPixmap collage(16, 8);
    QPainter painter(&collage);

    // add 0s
    if (thousands)
        painter.drawPixmap(8, 0, _stage_tiles.copy(moveBy(score, 6, 0, 8, 8)));
    else
        painter.drawPixmap(8, 0, _stage_tiles.copy(moveBy(score, 5, 0, 8, 8)));

    // add base number
    if(base_score == 10)
        painter.drawPixmap(0, 0, _stage_tiles.copy(score));
    else if (base_score == 20)
        painter.drawPixmap(0, 0, _stage_tiles.copy(moveBy(score, 1, 0, 8, 8)));
    else if (base_score == 40)
        painter.drawPixmap(0, 0, _stage_tiles.copy(moveBy(score, 2, 0, 8, 8)));
    else if (base_score == 50)
        painter.drawPixmap(0, 0, _stage_tiles.copy(moveBy(score, 3, 0, 8, 8)));
    else if (base_score == 80)
        painter.drawPixmap(0, 0, _stage_tiles.copy(moveBy(score, 4, 0, 8, 8)));
    else // 1 up
        painter.drawPixmap(0, 0, _stage_tiles.copy(QRect(718, 185, 16, 8)));

    // end painting (necessary for setMask)
    painter.end();

    // make background transparent
    collage.setMask(collage.createMaskFromColor(QColor(147, 187, 236)));

    return collage;
}*/
