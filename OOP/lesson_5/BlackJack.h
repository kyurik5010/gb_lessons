#include <iostream>
#include <vector>

#ifndef OOP_LSN5_BLACKJACK_H
#define OOP_LSN5_BLACKJACK_H

//----------------------------------------------------------------------------------------------------------------------
// СТРУКТУРЫ С ПРОШЛЫХ ЗАНЯТИЙ

class card{
    enum m_suit {diamonds, hearts, spades, cross};
    enum m_value{
        ace = 0,
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,};
    m_suit st;
    m_value vl;
    bool isFacedUp = false;
public:
    card (int suit, int value) {
        st = static_cast<m_suit> (suit);
        vl = static_cast<m_value> (value);
    }
    void flip(){
        isFacedUp = !isFacedUp;
    }
    int getValue (){
        return static_cast<int>(vl);
    }
    void setAce(int power){
        vl = static_cast<m_value>(power);
    };
    ~card() {}
};

class hand{
    std::vector<card*> hnd;
public:
    hand(){ hnd.reserve(5); }

    void Add(card* c){ hnd.push_back(c); }

    void Clear(){ hnd.clear(); }

    int GetValue(){
        int score = 0;
        int ace = 0;
        int aces[hnd.size()]; // массив для тузов
        for (int i = 0; i < hnd.size(); ++i) {
            if(!hnd[i]->getValue()) // если туз, то он откладывается и считается отдельно от простых карт
                aces[ace++] = i;
            score += hnd[i]->getValue();
        }

        for (int i = 0; i < ace; ++i) { // считаем тузы
            if(score + 11 <= 21) {
                hnd[aces[i]]->setAce(11); // не уверен можно ли считать тузы каждый раз по-разному, и
                score += 11;                     // и как часто вообще будут подсчитываться очки в руке, поэтому пока так.
            }                                    // Любопытно, что согласно дебагеру 11 присваивается следующим образом:
            else                                 // vl={card::m_value} three|eight
            {
                hnd[aces[i]]->setAce(1);
                score += 1;
            }
        }
        return score;
    }
};

//----------------------------------------------------------------------------------------------------------------------
// ЗАНЯТИЕ 5 - ЗАДАНИЕ 4

class GenericPlayer : public hand{
    std::string name;
public:
    virtual bool IsHitting() = 0; // чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.

    bool IsBoosted() {
        if(GetValue() > 21)
            return true;
        return false;
    }

    void Bust() {
        std::cout << name << " was busted";
    }
};


#endif //OOP_LSN5_BLACKJACK_H
