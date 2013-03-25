#include <vector>
#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;
//lesson, first missed G2J, need to be more careful
//second, when moved, need to check if position is above 40
//third, when doubleCount ==3 need to got ot jail immediately(return) and
//no more position update etc...
class Monopoly{
    public:
        Monopoly();
        void reset();
        void move();
        void checkPos();
        void drawChest();
        void drawChance();
        void print();
    private:
        enum CARDS {NORMAL= 0, TO_GO, TO_JAIL, TO_C1, TO_E3, TO_H2, TO_R1, RAIL, UTIL, BACK3};
        enum POS {GO = 0,
                  CC1= 2,
                  R1=5,
                  CH1=7,
                  JAIL= 10,
                  C1 = 11,
                  U1 = 12,
                  R2 = 15,
                  CC2 = 17,
                  CH2 = 22,
                  E3 = 24,
                  R3 = 25,
                  U2 = 28,
                  G2J = 30,
                  CC3 = 33,
                  R4 = 35,
                  CH3=36,
                  H2 = 39
        };
        void chestInit();
        void chanceInit();
        vector<int> gridStat; //totally for this problem
        vector<int> chestCards;
        vector<int> chanceCards;
        int position;
        int chancePos;
        int chestPos;
        int doubleCount; //3 consecutive doubles will go to jail
};
Monopoly::Monopoly(){
    gridStat.resize(40,0);
}
void Monopoly::reset(){
    position = 0;
    chancePos = 0;
    chestPos = 0;
    doubleCount = 0;
    chestInit();
    chanceInit();
    //shuffle cards randomly
    random_shuffle(chestCards.begin(), chestCards.end());
    random_shuffle(chanceCards.begin(), chanceCards.end());
}

//update position  based on cards
void Monopoly::drawChest(){
    switch(chestCards[chestPos]){
        case NORMAL:
            break;
        case TO_GO:
            position = GO;
            break;
        case TO_JAIL:
            position = JAIL;
            break;
        default:
            assert(0);
            break;
        
    }
    ++chestPos;
    if(chestPos == 16)
        chestPos = 0;
}

//update position  based on cards
void Monopoly::drawChance(){
    switch(chanceCards[chancePos]){
        case NORMAL:
            break;
        case TO_GO:
            position = GO;
            break;
        case TO_JAIL:
            position = JAIL;
            break;
        case TO_C1:
            position = C1;
            break;
        case TO_E3:
            position = E3;
            break;
        case TO_H2:
            position = H2;
            break;
        case TO_R1:
            position = R1;
            break;
        case RAIL:
            if(position ==CH1)
                position = R2;
            else if(position ==CH2)
                position = R3;
            else if(position == CH3)
                position = R1;
            else 
                assert(0);
            break;
        case UTIL:
            if(position == CH1 || position == CH3)
                position = U1;
            else
                position = U2;
            break;
        case BACK3:
            position -= 3;
            if(position < 0)
                position += 40;
            break;
        default:
            assert(0);
    }
    ++chancePos;
    if(chancePos == 16)
        chancePos = 0;
}
void Monopoly::checkPos(){
    if(position >= 40)
        position -= 40;
    if(position == CH1 || position == CH2 || position == CH3){
        drawChance();
    }else if(position == CC1 || position ==CC2 || position == CC3){
        drawChest();
    }else if(position == G2J){
        position = JAIL;
    }
}
void Monopoly::move(){
    int dice = 4;
    int d1 = rand()%dice+1;
    int d2 = rand()%dice+1;
    if(d1 ==d2) 
        ++doubleCount;
    else
        doubleCount = 0;
    if(doubleCount == 3){
        doubleCount = 0;
        position = JAIL;
        ++gridStat[position];
        return;
    }
    position += (d1+d2);
    checkPos();
    //TODO update position 
    if(position >= 40) position %= 40;
        ++gridStat[position];
}
void Monopoly::chestInit(){
    chestCards.clear();
    chestCards.resize(16, 0);
    chestCards[0] = TO_GO;
    chestCards[1] = TO_JAIL;
}

void Monopoly::chanceInit(){
    chanceCards.clear();
    chanceCards.resize(16);
    chanceCards[0]=TO_GO;
    chanceCards[1]=TO_JAIL;
    chanceCards[2]=TO_C1;
    chanceCards[3]=TO_E3;
    chanceCards[4]=TO_H2;
    chanceCards[5]=TO_R1;
    chanceCards[6]=RAIL;
    chanceCards[7]=RAIL;
    chanceCards[8]=UTIL;
    chanceCards[9]=BACK3;
}

void Monopoly::print(){
    for(int i = 0; i < 40; ++i){
        printf("%d %d\n", i, gridStat[i]);
    }
}
int main(){
    int limit = 1000;
    Monopoly mono;
    for(int play = 0; play < limit; ++play){
        mono.reset();
        for(int i = 0; i < 10000; ++i){
            mono.move();
        }
    }
    mono.print();
}
