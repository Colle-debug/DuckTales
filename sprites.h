#ifndef SPRITES_H
#define SPRITES_H
#include <QPixmap>


// Singleton class
class Sprites
{
private:

           // sprites
    QPixmap hud;
    QPixmap enemies;
    QPixmap scrooge;
    QPixmap title_screen;

    Sprites();

public:

    // singleton
    static Sprites* instance();

    // extract texture from sprites using the given id
    void get(const std::string & id, QPixmap animOutput[4]);
};
#endif
