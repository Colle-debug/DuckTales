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


Sprites* Sprites::instance()
{
    static Sprites uniqueInstance;
    return &uniqueInstance;
}

Sprites::Sprites()
{
    scrooge = loadTexture(":/sprites/scroogeNew.png", QColor(0, 89, 255, 255));
}

void Sprites::get(const std::string & id, QPixmap animOutput[])
{
    if      (id == "scrooge-stand"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,0,0));
    } 
    else if(id == "scrooge-walk-0"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,1,0));
    }
    else if(id == "scrooge-walk-1"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,2,0));
    }
    else if(id == "scrooge-walk-2"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,3,0));
    }
    else if(id == "scrooge-jump-fall"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,4,0));
    }else if(id == "scrooge-bounce-0"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,0,2));
    }else if(id == "scrooge-bounce-1"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,1,2));
    }
    else if(id == "scrooge-crouch-0"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,2,2));
    }
    else if(id == "scrooge-crouch-1"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,3,2));
    }
    else if(id == "scrooge-stuck"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,4,2));
    }
    else if(id == "scrooge-climb-0"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,5,2));
    }
    else if(id == "scrooge-climb-1"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,0,4));
    }
    else if(id == "scrooge-preputt-0"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,1,4));
    }
    else if(id == "scrooge-preputt-1"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,2,4));
    }
    else if(id == "scrooge-putt-0"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,3,4));
    }
    else if(id == "scrooge-putt-1"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,4,4));
    }
    else if(id == "scrooge-putt-success-0"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,5,4));
    }
    else if(id == "scrooge-putt-success-1"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,0,6));
    }
    else if(id == "scrooge-putt-fail-0"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,1,6));
    }
    else if(id == "scrooge-putt-fail-1"){
        animOutput[0] = scrooge.copy(moveBy(scrooge_stand,2,6));
    }



    else
    {
        printf("warning: cannot get texture \"%s\"\n", id.c_str());
        //return QPixmap();
    } 
}
