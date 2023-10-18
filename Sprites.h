#ifndef SPRITES_H
#define SPRITES_H
#include <QPixmap>


// Singleton class
class Sprites
{
private:

           // sprites
    QPixmap hud;
    QPixmap pinkAlien;
    QPixmap octopus;
    QPixmap beagleBoy;
    QPixmap scrooge;
    QPixmap title_screen;
    QPixmap platform;

    Sprites();

public:

           // singleton
    static Sprites* instance();

           // extract texture from sprites using the given id
    QPixmap* getSprite(const std::string& id);
    void get(const std::string & id, QRect animOutput[]);

    // score composite from sprite single score pieces
    QPixmap getScore(int );

    // number composite from sprite single characters
    QPixmap getNumber(int n, int fill = 0);

    // string composite from sprite single characters
    QPixmap getString(std::string text, int fill = 0);
};
#endif
