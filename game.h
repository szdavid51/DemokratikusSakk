#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define opponent = 2;
#define player = 1;
class Figura
{
public:
    void setpos(int sor, int oszlop){}
    void setplayer(int a){}
};
class Gyalog : public Figura
{

};
struct Sakktabla
{
    Figura* p;
    Sakktabla()
    {
        p = new Gyalog[16];
        for(int i = 0; i<=7; i++)
        {
            p[i].setpos(2,i+1);
            p[i].setplayer(player);
        }
        for(int i = 8; i<=15; i++)
        {
            p[i].setpos(7,i-7);
            p[i].setplayer(opponent);
        }
    }
};
class Game
{
    std::ostream& out; //Stream amire karakteresen kiirja a kimeneteket
    Sakktabla s;
public:
    Game(std::ostream& out = std::cout) : out(out){} //Alapertelmezetten a standard kimenetre akarunk irni
    void print()
    {
        for(int i = 0;i < 7;i++)
        {
            for(int j = 0; j< 7; j++)
                out<<s.m[i][j]<<" ";
            out<<"\n";
        }
    }
    void test(){out<<"yes";}
};


#endif // GAME_H_INCLUDED
