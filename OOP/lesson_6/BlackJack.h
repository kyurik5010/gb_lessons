#include <iostream>
#include <vector>

#ifndef OOP_LSN5_BLACKJACK_H
#define OOP_LSN5_BLACKJACK_H

//----------------------------------------------------------------------------------------------------------------------
// СТРУКТУРЫ С ПРОШЛЫХ ЗАНЯТИЙ

class Card{
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
    Card (int suit, int value) {
        st = static_cast<m_suit> (suit);
        vl = static_cast<m_value> (value);
    }
    void flip () { isFacedUp = !isFacedUp; }
    m_value getValue () { return vl; }
    m_suit getSuit () { return st; }
    void setAce(int power){ vl = static_cast<m_value>(power); }
    friend std::ostream& operator<< (std::ostream &out, Card &card);
    ~Card() {}
};

class Hand{
    std::vector<Card*> hnd;
public:
    Hand(){ hnd.reserve(5); }

    void Add(Card& c){ hnd.push_back(&c); }

    void Clear(){ hnd.clear(); }
    std::vector<Card*> getHand() { return hnd; }
    int GetValue() const{
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

class GenericPlayer : public Hand{
    std::string m_name;
public:
    void setName(std::string &name) { m_name = name; }
    std::string getName() const { return m_name; }
    virtual bool IsHitting() const = 0; // чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.

    bool IsBoosted() {
        if(GetValue() > 21)
            return true;
        return false;
    }

    void Bust() { std::cout << getName() << " was busted"; }
    friend std::ostream& operator<< (std::ostream &out, GenericPlayer& Player);
};


//----------------------------------------------------------------------------------------------------------------------
// ЗАДАНИЕ 3

class Player : public GenericPlayer{
public:
    Player(std::string name){
        setName(name);
    }
    bool IsHitting() const override{ // если оставить виртуальным, то класс останется абстрактным, поэтому решил реализовать этот метод
        char choice = 'n';
        std::cout << "\nWant another card? (y/n)";
        std::cin >> choice;
        if(choice == 'y')
            return true;
        return false;
    }
    void Win() const{ std::cout << "\n" << getName() << " won!"; }
    void Lose() const{ std::cout << "\n" << getName() << " lost!"; }
    void Push() const{ std::cout << "\n" << getName() << " played a draw!"; }

};
//----------------------------------------------------------------------------------------------------------------------
// ЗАДАНИЕ 4

class House : public GenericPlayer{
public:
    bool IsHitting() const override {
        if (GetValue() <= 16)
            return true;
        return false;
    }
    void FlipFirstCard(){
        if(!getHand().empty())
            getHand()[0]->flip();
    }
};
//----------------------------------------------------------------------------------------------------------------------
// ЗАДАНИЕ 5


std::ostream& operator<< (std::ostream &out, Card &card)
{

    if(!card.isFacedUp)
        out << "XX";
    else {
        out << "(";
        switch (card.st) {
            case 0: out << "diamonds"; break;
            case 1: out << "hearts"; break;
            case 2: out << "spades"; break;
            case 3: out << "cross"; break;
        }
        out << "|";
        switch (card.vl){
            case 0: out << "ace"; break;
            case 1: out << "one"; break;
            case 2: out << "two"; break;
            case 3: out << "three"; break;
            case 4: out << "four"; break;
            case 5: out << "five"; break;
            case 6: out << "six"; break;
            case 7: out << "seven"; break;
            case 8: out << "eight"; break;
            case 9: out << "nine"; break;
            case 10: out << "ten"; break;
            //case 11: out << "ace"; break;
        }
        out << ")";
    }
    return out;
}

std::ostream& operator<< (std::ostream &out, GenericPlayer& genericPlayer){
    out << genericPlayer.m_name;
    for (int i = 0; i < genericPlayer.getHand().size(); ++i)
        out << " " << *genericPlayer.getHand()[i];

    out << " score: " << genericPlayer.GetValue();
    return out;
}

#endif //OOP_LSN5_BLACKJACK_H
