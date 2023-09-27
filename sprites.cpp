#include "Sprites.h"
#include <QBitmap>
#include <string>
#include <QPainter>
#include <QPixmap>


// utility function
QRect moveBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
    rect.moveTo(QPoint(rect.x() + x*dx + x*border_x, rect.y() + y*dy + y*border_y));
    return rect;
}

QRect moveScroogeBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
    return moveBy(rect, x, y, dx, dy, 2, 2);
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
static QRect scrooge_stand(1, 1, 21, 29);


Sprites* Sprites::instance()
{
    static Sprites uniqueInstance;
    return &uniqueInstance;
}

Sprites::Sprites()
{
    scrooge = loadTexture(":/sprites/scrooge.png", QColor(0, 89, 255, 255));
}

QPixmap Sprites::get(const std::string & id)
{
    if      (id == "scrooge-stand"){
        return scrooge.copy(scrooge_stand);
    }
    else
    {
        printf("warning: cannot get texture \"%s\"\n", id.c_str());
        return QPixmap();
    }
}
