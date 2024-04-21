#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define player2 2
#define player1 1
#include <stdlib.h>
template<typename T>
class DinamikusTomb {
private:
    T* tomb;
    size_t meret;

public:
    DinamikusTomb() : tomb(nullptr), meret(0) {}

    explicit DinamikusTomb(size_t kezdo_meret) : meret(kezdo_meret) {
        tomb = new T[meret];
    }

    ~DinamikusTomb() {
        delete[] tomb;
    }

    void atmeretez(size_t uj_meret) {
        T* uj_tomb = new T[uj_meret];
        if (tomb) {
            size_t minimalis_meret = (uj_meret < meret) ? uj_meret : meret;
            for (size_t i = 0; i < minimalis_meret; ++i) {
                uj_tomb[i] = tomb[i];
            }
            delete[] tomb;
        }
        tomb = uj_tomb;
        meret = uj_meret;
    }

    size_t getMeret() const {
        return meret;
    }

    T& operator[](size_t index) {
        if (index >= meret || index < 0) {
            throw "index error";
        }
        return tomb[index];
    }
};
struct pos{
int s,o;
};
class Sakktabla;
class Figura
{
    protected:
    int s;
    int o;
    int p;
    const char* name;
    bool dead;
public:
    Figura(int s, int o, int p, const char* name = ""):s(s),o(o),p(p),name(name),dead(false){}
    void setpos(int sor, int oszlop){
        s = sor; o = oszlop;
    }
    void setplayer(int a){p = a;}
    int gets()const{return s;}
    int geto()const{return o;}
    int getp()const{return p;}
    const char* getname()const{return name;}
    bool isdead()const{return dead;}
    bool move(Sakktabla& s){
        //call function to get possible moves
        //choose random move and return true
        //return false if no moves can be made
    }
    virtual DinamikusTomb<pos> getPossibleMoves(Sakktabla& s) = 0;
};
class Gyalog : public Figura
{
public:
    Gyalog(int s, int o, int p):Figura(s,o,p,"p"){}
    static void Setup(DinamikusTomb<Figura*>& f)
    {
        size_t kezdetIndex = f.getMeret();
        f.atmeretez(kezdetIndex + 16);
        for(size_t i = kezdetIndex; i<=kezdetIndex + 7; i++)
            f[i] = new Gyalog(2,i - kezdetIndex + 1,player1);
        for(size_t i = kezdetIndex + 8; i<=kezdetIndex + 15; i++)
            f[i] = new Gyalog(kezdetIndex + 7,i - kezdetIndex - 7, player2);
    }
    DinamikusTomb<pos> getPossibleMoves(Sakktabla& s)
    {
        //determines valid moves and adds valid positions it can move to to a dinamic array
        //returns dinamic array
    }
};
class Sakktabla
{
    DinamikusTomb <Figura*> f;
    Figura* m[9][9];
    public:
    Sakktabla():f(0)
    {
        Gyalog::Setup(f);
        this->update_m();
    }
    void update_m()
    {
        for(int i=1;i<=8;i++)
            for(int j=1;j<=8;j++)
                m[i][j] = NULL;
        for(int i = 0;i<=15;i++)
        {
            m[f[i]->gets()][f[i]->geto()] = f[i];
        }
    }
    void print(std::ostream& out)
    {
        for(int i=1;i<=8;i++)
        {
            for(int j=1;j<=8;j++)
            {
                if(m[i][j] == NULL || m[i][j]->isdead())
                    out<<" ** ";
                else out<<" "<<m[i][j]->getname()<<m[i][j]->getp()<<" ";
            }
            out<<"\n\n";
        }
    }
    bool move(int s, int o, int cp)
    {
        //if there is a piece that can move and it belongs to cp player then make that piece move and if succesful return true
        //else return false
    }
    void reset()
    {

    }
};
enum GameState{
Menu,
StartJatek,
Jatek,
ExitProgram,
ExitJatek,
};
class Game
{
    std::istream& in;
    std::ostream& out; //Stream amire karakteresen kiirja a kimeneteket
    Sakktabla s;
    int cp;
    GameState state;
public:
    Game(std::istream& in = std::cin,std::ostream& out = std::cout) : in(in),out(out){} //Alapertelmezetten a standard kimenetre akarunk irni
    void start()
    {
        state = Menu;
        this->gameloop();
    }
    void gameloop()
    {
        while(state!=ExitProgram)
        {
            switch(state)
            {
            case Menu:
                this->menu();
                break;
            case StartJatek:
                cp = player1;
                state = Jatek;
                break;
            case Jatek:
                this->jatek();
                break;
            case ExitJatek:
                s.reset();
                state = Menu;
                break;
            default:
                break;
            }
        }
    }
    void jatek()
    {
        system("cls");
        this->print();
        this->listenToInput();
    }
    void menu()
    {
        system("cls");
        out<<"Demokratikus sakk ascii art\n1.Start Game\n2.Exit";
        int c;
        in>>c;
        if(c==1)
            state= StartJatek;
        if(c==2)
            this->exit();
    }
    void print()
    {
        s.print(out);
    }
    void listenToInput()
    {
        out<<"\nPlayer"<<cp<<" ,kerek input-ot: ";
        char a,b;
        in>>a;
        if(a == '0') return this->exit();
        else{
            if(a<'a' || a >'h'){
                out<<"Hibas input! Helyes formatum pelda: e2";
                return this->listenToInput();
            }
            else{
                in>>b;
                if(b<'1' || b>'8')
                {
                    out<<"Hibas input! Helyes formatum pelda: e2";
                    return this->listenToInput();
                }
                else{
                    if(!s.move(int(b-48), int(a-96), cp)){
                        out<<"Hibas input! Nem valasztottal jo figurat!";
                        return this->listenToInput();
                    }
                    else{
                        if(cp == player1) //switch players
                            cp = player2;
                        else cp = player1;
                        return;
                    }
                }
            }
        }
    }
    void exit(){
        if(state == Jatek)
            state = ExitJatek;
        if(state==Menu)
            state = ExitProgram;
    }
    void test(){out<<"yes";}
};


#endif // GAME_H_INCLUDED
