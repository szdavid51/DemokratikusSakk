#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define player2 2
#define player1 1
class Figura
{
    int s;
    int o;
    int p;
    bool dead;
public:
    Figura():dead(false){}
    void setpos(int sor, int oszlop){
        s = sor; o = oszlop;
    }
    void setplayer(int a){p = a;}
    int gets()const{return s;}
    int geto()const{return o;}
    int getp()const{return p;}
};
class Gyalog : public Figura
{

};
class Sakktabla
{
    Figura* p;
    Figura* m[9][9];
    public:
    Sakktabla()
    {
        p = new Gyalog[16];
        for(int i = 0; i<=7; i++)
        {
            p[i].setpos(2,i+1);
            p[i].setplayer(player1);
        }
        for(int i = 8; i<=15; i++)
        {
            p[i].setpos(7,i-7);
            p[i].setplayer(player2);
        }
        this->update_m();
    }
    void update_m()
    {
        for(int i=1;i<=8;i++)
            for(int j=1;j<=8;j++)
                m[i][j] = NULL;
        for(int i = 0;i<=15;i++)
        {
            m[p[i].gets()][p[i].geto()] = &p[i];
        }
    }
    void print(std::ostream& out)
    {
        for(int i=1;i<=8;i++)
        {
            for(int j=1;j<=8;j++)
            {
                if(m[i][j] == NULL)
                    out<<"*";
                else out<<m[i][j]->getp();
            }
            out<<"\n";
        }
    }
    bool move(int s, int o, int p)
    {
    }
};
class Game
{
    std::ostream& out; //Stream amire karakteresen kiirja a kimeneteket
    std::istream& in;
    Sakktabla s;
public:
    Game(std::istream& in = std::cin,std::ostream& out = std::cout) : in(in),out(out){} //Alapertelmezetten a standard kimenetre akarunk irni
    void print()
    {
        s.print(out);
    }
    void listenToInput(int p)
    {
        out<<"Kerek input-ot: ";
        char a,b;
        in>>a;
        if(a == '0') this->exit();
        else
        {
            if(a<'a' || a >'h')
            {
                out<<"Hibas input! Helyes formatum pl. e2";
                return this->listenToInput(p);
            }
            else
            {
                in>>b;
                if(b<'1' || b>'8')
                {
                    out<<"Hibas input! Helyes formatum pl. e2";
                    return this->listenToInput(p);
                }
                else
                {
                    if(!s.move(int(b-48), int(a-96), p)){
                        out<<"Hibas input! Nem valasztottal jo figurat!";
                        return this->listenToInput(p);
                    }
                }
            }
        }
    }
    void exit();
    void test(){out<<"yes";}
};


#endif // GAME_H_INCLUDED
