#include <QBrush>
#include "Scrooge.h"
#include "Loader.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"

using namespace DT;

Scrooge* Loader::load(std::string levelName)
{
    if(levelName=="theMoon")
    {
       
        Game::instance()->world()->addPixmap(QPixmap(":/background/theMoon.png"));
        //primo livello

        new Block(QPointF(0, 69*TILE), 54*TILE, 2.5*TILE); //primo rappresenta la posizione dall'alto verso il basso, il secondo rappresenta la lunghezza, il terzo invece lo spessore
        for (int i=0; i<5; i++)
        {
            new Block(QPointF((13+i)*TILE, 68*TILE), TILE, TILE);
        }
        new Block(QPointF(15*TILE,67*TILE),2*TILE,TILE);
       //in alternativa si puo fare un unico blocco di dimensione 4
       //new Block(QPointF(13*TILE,68*TILE,4*TILE,TILE))
       new Block(QPointF(26*TILE,68*TILE), 2*TILE,TILE);
    
      for (int i=0; i<5; i++)
        {
            new Block(QPointF((42+i)*TILE, 68*TILE), TILE, TILE);
        }
      for (int i=0; i<3; i++)
        {
            new Block(QPointF((43+i)*TILE, 67*TILE), TILE, TILE);
        }  
      
       new Block(QPointF(19*TILE,67*TILE),TILE,TILE);
       new Block(QPointF(19*TILE,68*TILE),TILE,TILE);
       new Block(QPointF(58*TILE,69*TILE),4*TILE,2.5*TILE);
       new Block(QPointF(64*TILE,69*TILE),18*TILE,2.5*TILE);
       new Block(QPointF(48*TILE, 68*TILE), 2*TILE, TILE);
       
       for(int i=0;i<4;i++){
       new Block(QPointF((66+i)*TILE, 68*TILE), TILE, TILE);
       }
       new Block(QPointF(67*TILE, 67*TILE), TILE, TILE);
       new Block(QPointF(67*TILE, 66*TILE), TILE, TILE);
       new Block(QPointF(67*TILE, 65*TILE), TILE, TILE);
       new Block(QPointF(69*TILE, 67*TILE), TILE, 2*TILE);
       new Block(QPointF(69*TILE, 66*TILE), TILE, 2*TILE);
       new Block(QPointF(93*TILE,65*TILE),3*TILE,6.5*TILE); //sistema questo
       new Block(QPointF(98*TILE,69*TILE),8*TILE,2.5*TILE);
       new Block(QPointF(100*TILE,68*TILE),2*TILE,TILE); // ultimo tronco in fondo 
       new Block(QPointF(108*TILE,69*TILE),11*TILE,2.5*TILE);
       new Block(QPointF(119*TILE,64*TILE),2*TILE,TILE*6);
       new Block(QPointF(0,56.5*TILE),16*TILE,3.5*TILE);
       new Block(QPointF(54*TILE,49*TILE),4*TILE,TILE);//FINE LIANA
       new Block(QPointF(22*TILE,47*TILE),4*TILE,TILE);//FINE LIANA
       //blocchi finali primo livello a destra
       new Block(QPointF(123*TILE,68*TILE),TILE,8*TILE);
       new Block(QPointF(121*TILE,69*TILE),2*TILE,7*TILE);
       new Block(QPointF(124*TILE,66*TILE),TILE,10*TILE); // potrebbe essere necessario diminuire di uno l'altezza
       new Block(QPointF(125*TILE,63*TILE),TILE,13*TILE);
       new Block(QPointF(126*TILE,60*TILE),2*TILE,24*TILE);
      
      
      
      
      
      //blocchi tra il primo livello ed il secondo livello 
       new Block(QPointF(4*TILE,45*TILE),2*TILE,2*TILE);
       new Block(QPointF(6*TILE,46*TILE),2*TILE,3*TILE);
       new Block(QPointF(8*TILE,48*TILE),4*TILE,3*TILE);
       new Block(QPointF(12*TILE,50*TILE),6*TILE,4*TILE);
       new Block(QPointF(18*TILE,52*TILE),4*TILE,2*TILE);
       new Block(QPointF(22*TILE,52*TILE),TILE,4*TILE);
       new Block(QPointF(25*TILE,52*TILE),TILE,4*TILE);
       new Block(QPointF(26*TILE,52*TILE),2*TILE,2*TILE);
       new Block(QPointF(28*TILE,52*TILE),2*TILE,5*TILE);
       new Block(QPointF(30*TILE,54*TILE),24*TILE,7*TILE);
       new Block(QPointF(54*TILE,54*TILE),TILE,9*TILE);
       new Block(QPointF(57*TILE,54*TILE),TILE,9*TILE);
       new Block(QPointF(58*TILE,54*TILE),24*TILE,7*TILE); //384*11
       new Block(QPointF(70*TILE,53*TILE),6*TILE,TILE); //35*16
       new Block(QPointF(82*TILE,52*TILE),2*TILE,4.5*TILE); //32*72
       new Block(QPointF(84*TILE,52*TILE),10*TILE,2*TILE); //160*32
       new Block(QPointF(94*TILE,50*TILE),4*TILE,4*TILE); //64*64
       new Block(QPointF(100*TILE,48*TILE),4*TILE,4*TILE); //
       new Block(QPointF(104*TILE,46*TILE),2*TILE,4*TILE); //
       new Block(QPointF(106*TILE,44*TILE),2*TILE,2*TILE);
       new Block(QPointF(82*TILE,56.5*TILE),46*TILE,3.5*TILE); //grande blocco dopo 384*11
       






       //oggetti livello 1, spine
       new Block(QPointF(12*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(13*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(14*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(15*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(16*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(17*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(18*TILE,50*TILE),TILE,2*TILE);
       new Block(QPointF(19*TILE,50*TILE),TILE,2*TILE);
       new Block(QPointF(20*TILE,50*TILE),TILE,2*TILE);
       new Block(QPointF(21*TILE,50*TILE),TILE,2*TILE);
       new Block(QPointF(90*TILE,50*TILE),TILE,2*TILE);
       new Block(QPointF(91*TILE,50*TILE),TILE,2*TILE);
       new Block(QPointF(92*TILE,50*TILE),TILE,2*TILE);
       new Block(QPointF(93*TILE,50*TILE),TILE,2*TILE);
       new Block(QPointF(94*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(95*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(96*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(97*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(98*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(99*TILE,48*TILE),TILE,2*TILE);
       new Block(QPointF(32*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(33*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(34*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(35*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(36*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(37*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(38*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(39*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(60*TILE,44*TILE),TILE,2*TILE);
       new Block(QPointF(61*TILE,44*TILE),TILE,2*TILE);
       new Block(QPointF(64*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(65*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(68*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(69*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(76*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(77*TILE,45*TILE),TILE,TILE);
       new Block(QPointF(84*TILE,44*TILE),TILE,2*TILE);
       new Block(QPointF(85*TILE,44*TILE),TILE,2*TILE);
     
       //rocce primo livello 
       new Block(QPointF(60*TILE,52*TILE),TILE,TILE);
       new Block(QPointF(61*TILE,52*TILE),TILE,TILE);
       new Block(QPointF(60*TILE,53*TILE),TILE,TILE);
       new Block(QPointF(61*TILE,53*TILE),TILE,TILE);
       new Block(QPointF(84*TILE,51*TILE),TILE,TILE);
       new Block(QPointF(85*TILE,51*TILE),TILE,TILE);
       new Block(QPointF(86*TILE,51*TILE),TILE,TILE);
       new Block(QPointF(87*TILE,51*TILE),TILE,TILE);
       new Block(QPointF(88*TILE,51*TILE),TILE,TILE);
       new Block(QPointF(85*TILE,50*TILE),TILE,TILE);
       new Block(QPointF(86*TILE,50*TILE),TILE,TILE);
       //rocce sui funghi
       new Block(QPointF(71*TILE,48*TILE),TILE,TILE);
       new Block(QPointF(74*TILE,48*TILE),TILE,TILE);


     
     
       //funghi giganti
       new Block(QPointF(32*TILE,49*TILE),2*TILE,5*TILE);
       new Block(QPointF(42*TILE,49*TILE),2*TILE,5*TILE);
       new Block(QPointF(48*TILE,49*TILE),2*TILE,5*TILE);
       new Block(QPointF(62*TILE,49*TILE),2*TILE,5*TILE);
       new Block(QPointF(70*TILE,49*TILE),2*TILE,4*TILE);
       new Block(QPointF(74*TILE,49*TILE),2*TILE,4*TILE);








      new Block(QPointF(0,41.5*TILE),48*TILE,3.5*TILE);
      new Block(QPointF(2*TILE,39*TILE),53*TILE,2.5*TILE);
      new Block(QPointF(10*TILE,30*TILE),9*TILE,9*TILE);
      new Block(QPointF(19*TILE,36*TILE),2*TILE,3*TILE);
      //new Block(QPointF(62*TILE,30*TILE),4*TILE,9*TILE);
      new Block(QPointF(21*TILE,38*TILE),2*TILE,1*TILE);
      new Block(QPointF(10*TILE,30*TILE),9*TILE,9*TILE);
      new Block(QPointF(57*TILE,39*TILE),30*TILE,5*TILE);
      new Block(QPointF(48*TILE,41.5*TILE),7*TILE,2.5*TILE);
      new Block(QPointF(89*TILE,39*TILE),7*TILE,5*TILE);
      new Block(QPointF(96*TILE,39*TILE),10*TILE,6*TILE); //forse bisogna farlo di un tile in più

      new Block(QPointF(64*TILE,31*TILE),6*TILE,8*TILE);
      new Block(QPointF(6*TILE,34*TILE),TILE,TILE);
      new Block(QPointF(9*TILE,32*TILE),TILE,TILE);
      new Block(QPointF(9*TILE,36*TILE),TILE,TILE);
      new Block(QPointF(94*TILE,32*TILE),5*TILE,4*TILE);
      new Block(QPointF(94*TILE,30*TILE),3*TILE,2*TILE);
      new Block(QPointF(101*TILE,35*TILE),TILE,3*TILE);
      new Block(QPointF(102*TILE,39*TILE),2*TILE,TILE);
      new Block(QPointF(104*TILE,35*TILE),2*TILE,3*TILE);
      new Block(QPointF(106*TILE,30*TILE),2*TILE,5*TILE);
      new Block(QPointF(2*TILE,30*TILE),4*TILE,9*TILE);

      //blocchi tra primo e secondo verde
      new Block(QPointF(26*TILE,24*TILE),44*TILE,7*TILE);
      new Block(QPointF(70*TILE,24*TILE),16*TILE,6*TILE);
      new Block(QPointF(90*TILE,24*TILE),20*TILE,6*TILE); //estremità liana, l'altra è inclusa nel blocco 58*39
      //new Block(QPointF(68*TILE,49*TILE),2*TILE,5*TILE);
      new Block(QPointF(89*TILE,24*TILE),TILE,5*TILE);

      //oggetti secondo livello 
      new Block(QPointF(30*TILE,35*TILE),2*TILE,4*TILE);
      new Block(QPointF(32*TILE,35*TILE),2*TILE,4*TILE);
      new Block(QPointF(42*TILE,35*TILE),2*TILE,4*TILE);
      new Block(QPointF(44*TILE,35*TILE),2*TILE,4*TILE); //funghi

      new Block(QPointF(21*TILE,36*TILE),TILE,TILE);
      new Block(QPointF(21*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(22*TILE,36*TILE),TILE,TILE);
      new Block(QPointF(22*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(23*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(23*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(24*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(58*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(61*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(63*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(63*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(63*TILE,36*TILE),TILE,TILE);

      new Block(QPointF(70*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(70*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(70*TILE,36*TILE),TILE,TILE);
      new Block(QPointF(71*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(71*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(71*TILE,36*TILE),TILE,TILE);
      new Block(QPointF(72*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(72*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(92*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(93*TILE,38*TILE),TILE,TILE);
      new Block(QPointF(94*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(96*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(98*TILE,37*TILE),TILE,TILE);
      new Block(QPointF(102*TILE,35*TILE),TILE,TILE);
      new Block(QPointF(103*TILE,35*TILE),TILE,TILE);
      new Block(QPointF(97*TILE,30*TILE),TILE,TILE);
      new Block(QPointF(97*TILE,31*TILE),TILE,TILE);
      new Block(QPointF(98*TILE,30*TILE),TILE,TILE);
      new Block(QPointF(98*TILE,31*TILE),TILE,TILE);
      new Block(QPointF(31*TILE,31*TILE),TILE,2*TILE);
      new Block(QPointF(32*TILE,31*TILE),TILE,2*TILE);
      new Block(QPointF(43*TILE,31*TILE),TILE,2*TILE);
      new Block(QPointF(44*TILE,31*TILE),TILE,2*TILE);

      //new Block(QPointF(89*TILE,36*TILE),TILE,TILE);
      new Block(QPointF(63*TILE,36*TILE),TILE,TILE);
      new Block(QPointF(63*TILE,36*TILE),TILE,TILE);
      new Block(QPointF(86*TILE,24*TILE),TILE,5*TILE);

      //piattaforma
      new Block(QPointF(86*TILE,34*TILE),4*TILE,TILE);

      new Block(QPointF(0,41.5*TILE),48*TILE,3.5*TILE); //grande blocco bianco primo livello a sx confine con il secondo livello 


      //terzo livello
      new Block(QPointF(4*TILE,21*TILE),2*TILE,5.5*TILE);
      new Block(QPointF(6*TILE,19*TILE),2*TILE,7.5*TILE);
      new Block(QPointF(8*TILE,24*TILE),4*TILE,2.5*TILE);
      new Block(QPointF(12*TILE,23*TILE),4*TILE,3.5*TILE);
      new Block(QPointF(16*TILE,23*TILE),5*TILE,4*TILE);
      new Block(QPointF(8*TILE,17*TILE),4*TILE,3*TILE);
      //new Block(QPointF(10*TILE,17*TILE),2*TILE,3*TILE);
      new Block(QPointF(12*TILE,15*TILE),6*TILE,3*TILE);
      new Block(QPointF(18*TILE,15*TILE),28*TILE,TILE);
      new Block(QPointF(46*TILE,15*TILE),8*TILE,9*TILE);
      new Block(QPointF(64*TILE,22*TILE),TILE,2*TILE);
      new Block(QPointF(64*TILE,15*TILE),2*TILE,7*TILE);
      new Block(QPointF(66*TILE,19*TILE),2*TILE,TILE);
      new Block(QPointF(66*TILE,15*TILE),18*TILE,TILE);
      new Block(QPointF(80*TILE,0),4*TILE,15*TILE);
      new Block(QPointF(84*TILE,0),2*TILE,15*TILE);
      new Block(QPointF(86*TILE,0),TILE,14*TILE);
      new Block(QPointF(87*TILE,3*TILE),3*TILE,TILE);

      new Block(QPointF(89*TILE,9*TILE),1*TILE,5*TILE);
      new Block(QPointF(90*TILE,9*TILE),2*TILE,6*TILE);
      new Block(QPointF(92*TILE,7*TILE),2*TILE,9*TILE);
      new Block(QPointF(94*TILE,7*TILE),2*TILE,11*TILE);
      new Block(QPointF(96*TILE,7*TILE),2*TILE,4.5*TILE);
      new Block(QPointF(96*TILE,15*TILE),2*TILE,3*TILE);
      new Block(QPointF(98*TILE,16*TILE),2*TILE,2*TILE);
      new Block(QPointF(100*TILE,17*TILE),2*TILE,3*TILE);
      new Block(QPointF(102*TILE,18*TILE),2*TILE,2*TILE);
      new Block(QPointF(104*TILE,19*TILE),2*TILE,3*TILE);
      new Block(QPointF(106*TILE,21*TILE),2*TILE,3*TILE);

      new Block(QPointF(109*TILE,6*TILE),TILE,TILE);
      new Block(QPointF(111*TILE,5*TILE),TILE,TILE);
      new Block(QPointF(111*TILE,4*TILE),TILE,TILE);
      new Block(QPointF(114*TILE,8*TILE),TILE,TILE);
      new Block(QPointF(114*TILE,7*TILE),TILE,TILE);
      new Block(QPointF(116*TILE,4*TILE),TILE,TILE);
      new Block(QPointF(116*TILE,5*TILE),TILE,TILE);
      new Block(QPointF(118*TILE,6*TILE),TILE,TILE);
      new Block(QPointF(118*TILE,7*TILE),TILE,TILE);
      new Block(QPointF(119*TILE,3*TILE),TILE,TILE);
      new Block(QPointF(119*TILE,4*TILE),TILE,TILE);
      new Block(QPointF(122*TILE,7*TILE),TILE,TILE);
      new Block(QPointF(122*TILE,8*TILE),TILE,TILE);
      new Block(QPointF(122*TILE,7*TILE),TILE,TILE);
      new Block(QPointF(124*TILE,8*TILE),4*TILE,TILE);


      new Block(QPointF(11*TILE,23*TILE),TILE,TILE);
      new Block(QPointF(12*TILE,22*TILE),TILE,TILE);
      new Block(QPointF(13*TILE,22*TILE),TILE,TILE);
      new Block(QPointF(14*TILE,22*TILE),TILE,TILE);
      new Block(QPointF(14*TILE,21*TILE),TILE,TILE);
      new Block(QPointF(15*TILE,22*TILE),TILE,TILE);
      new Block(QPointF(19*TILE,22*TILE),TILE,TILE);
      new Block(QPointF(19*TILE,21*TILE),TILE,TILE);
      new Block(QPointF(19*TILE,20*TILE),TILE,TILE);
      new Block(QPointF(20*TILE,22*TILE),TILE,TILE);
      new Block(QPointF(28*TILE,23*TILE),TILE,TILE);
      new Block(QPointF(36*TILE,23*TILE),TILE,TILE);

      new Block(QPointF(31*TILE,23*TILE),TILE,TILE);   
      new Block(QPointF(32*TILE,23*TILE),TILE,TILE);
      new Block(QPointF(39*TILE,23*TILE),TILE,TILE);
      new Block(QPointF(40*TILE,23*TILE),TILE,TILE);





      new Block(QPointF(87*TILE,3*TILE),3*TILE,TILE);
      //piattaforma



      //livello sotteraneo


      new Block(QPointF(64*TILE,75*TILE),TILE,9*TILE);
      new Block(QPointF(65*TILE,81*TILE),3*TILE,TILE);
      new Block(QPointF(76*TILE,81*TILE),3*TILE,TILE);
      new Block(QPointF(79*TILE,75*TILE),TILE,7*TILE);
      new Block(QPointF(80*TILE,75*TILE),32*TILE,TILE);
      new Block(QPointF(112*TILE,71.5*TILE),7*TILE,4.5*TILE);
      new Block(QPointF(64*TILE,84*TILE),64*TILE,2.5*TILE);
      new Block(QPointF(88*TILE,83*TILE),9*TILE,TILE);
      new Block(QPointF(90*TILE,82*TILE),4*TILE,TILE);
      new Block(QPointF(90*TILE,81*TILE),2*TILE,TILE);
      new Block(QPointF(99*TILE,83*TILE),8*TILE,TILE);
      new Block(QPointF(99*TILE,82*TILE),8*TILE,TILE);
      new Block(QPointF(99*TILE,81*TILE),3*TILE,TILE);
      new Block(QPointF(105*TILE,81*TILE),2*TILE,TILE);
      new Block(QPointF(109*TILE,82*TILE),2*TILE,TILE);
      new Block(QPointF(113*TILE,82*TILE),2*TILE,TILE);
      new Block(QPointF(109*TILE,83*TILE),9*TILE,TILE);



      new Block(QPointF(86*TILE,83*TILE),TILE,TILE);
      new Block(QPointF(87*TILE,83*TILE),TILE,TILE);
      new Block(QPointF(97*TILE,83*TILE),TILE,TILE);
      new Block(QPointF(98*TILE,83*TILE),TILE,TILE);
      new Block(QPointF(108*TILE,83*TILE),TILE,TILE);
      new Block(QPointF(107*TILE,83*TILE),TILE,TILE);
      new Block(QPointF(123*TILE,83*TILE),TILE,TILE);
      new Block(QPointF(89*TILE,82*TILE),TILE,TILE);
      new Block(QPointF(98*TILE,82*TILE),TILE,TILE);
      new Block(QPointF(111*TILE,82*TILE),TILE,TILE);
      new Block(QPointF(112*TILE,82*TILE),TILE,TILE);
      new Block(QPointF(123*TILE,82*TILE),TILE,TILE);
      new Block(QPointF(102*TILE,81*TILE),TILE,TILE);
      new Block(QPointF(112*TILE,81*TILE),TILE,TILE);
      new Block(QPointF(123*TILE,81*TILE),TILE,TILE);  
      new Block(QPointF(90*TILE,80*TILE),TILE,TILE);
      new Block(QPointF(102*TILE,80*TILE),TILE,TILE);
      new Block(QPointF(112*TILE,80*TILE),TILE,TILE);
      new Block(QPointF(123*TILE,80*TILE),TILE,TILE);

      new Block(QPointF(21*TILE,24*TILE),TILE,7*TILE);
      new Block(QPointF(22*TILE,26*TILE),TILE,3*TILE);
      new Block(QPointF(25*TILE,26*TILE),TILE,3*TILE);
      new Block(QPointF(44*TILE,19*TILE),2*TILE,TILE);
      new Block(QPointF(54*TILE,21*TILE),6*TILE,TILE);

    return new Scrooge(QPointF(2.0 * TILE, 0));

    }
    else{
    return nullptr;
    }
}
