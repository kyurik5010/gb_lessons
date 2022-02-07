//#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <random> // для shuffle
#include <fstream>


#ifndef OOP_LSN5_BLACKJACK_H
#define OOP_LSN5_BLACKJACK_H

std::string filename = "log_file.txt";
std::ofstream outf(filename);


#pragma pack (push, 1)
class Card{
    enum m_suit {diamonds, hearts, spades, cross};
    enum m_value{
        //ace = 0,
        ace = 1,              //________________________________________/изменения: туз приравнял единице, убрал единицу -------- @
        //one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
///        Jack = 10,             ///_____________________________________________________________________________/убрал 16:50 -- @
//        Queen = 10,
//        King = 10,
        };
    m_suit st;
    m_value vl;
    bool isFacedUp = true;     //переделал на true чтобы у дилера пряталась именно первая карта, как указано в 4 задании -------- @
public:
    Card (int suit, int value) {
        st = static_cast<m_suit> (suit);
        vl = static_cast<m_value> (value);
    }
    void flip () { isFacedUp = !isFacedUp; }
    m_value getValue () { return vl; }
    m_suit getSuit () { return st; }
    void setAce(int power){ vl = static_cast<m_value>(power); }
    friend std::ostream& operator<< (std::ostream &out, Card &card)
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
                //case 0: out << "ace"; break;  //________________________________________________________________/убрал --------- @
                case 1: out << "ace"; break;    //_________________________________________________________/переименовал --------- @
                case 2: out << "two"; break;
                case 3: out << "three"; break;
                case 4: out << "four"; break;
                case 5: out << "five"; break;
                case 6: out << "six"; break;
                case 7: out << "seven"; break;
                case 8: out << "eight"; break;
                case 9: out << "nine"; break;
                case 10: out << "ten"; break;
//                case 11: out << "Jack"; break;  //___________________________________________/добавил: валет дама король --------- @
//                case 12: out << "Queen"; break;
//                case 13: out << "King"; break;
            }
            out << ")";
        }
        return out;
    }
};
#pragma pack (pop)

class Hand{
    std::vector<std::shared_ptr<Card>> m_hand;
public:
    Hand(){ m_hand.reserve(5); }
    ~Hand() { Clear(); }

    void Add(std::shared_ptr<Card> &c){
        m_hand.push_back(c);
    }

    void Clear()
    {
//        for(auto i : m_hand)     //______________________________________/убрал, т.к. переделал все на умные указатели  -------- !
//            i.release();
        m_hand.clear();
    }
    std::vector<std::shared_ptr<Card>> getHand() { return m_hand; }
    int GetValue() const
    {
        int score = 0;
        int ace = 0;
        int* aces = new int [m_hand.size()];        //_____________________________/массив для тузов сделал динмаическим -------- !
        for (int i = 0; i < m_hand.size(); ++i) {
            if(m_hand[i]->getValue() == 1)          // тузы откладываются и подсчитываются отдельно
                aces[ace++] = i;
//            else if(m_hand[i]->getValue() >= 11)    //______________________________________________/валет, дама, король -------- !
//                score += 10; // надеюсь тузы нерфить не будет
            score += m_hand[i]->getValue();
        }

        for (int i = 0; i < ace; ++i)               //_____________________________________________________/посчет тузов -------- !
        {
            if(score + 11 <= 21) {
                m_hand[aces[i]]->setAce(11);
                score += 11;
            }
//            else                                  //____________________________________________________________/убрал  -------- !
//            {
//                hnd[aces[i]]->setAce(1);
//                score += 1;
//            }
        }
        delete[] aces;                              //__________________________________________________________/добавил  -------- !
        return score;
    }
};

class GenericPlayer : public Hand{
    std::string m_name;
    int m_player_score;
    uint8_t IsBusted = 0;
public:
    void setName(std::string &name) { m_name = name; }
    std::string GetName() const { return m_name; }
    virtual bool IsHitting() const = 0;
    void UpdateScore(){
        m_player_score = GetValue();
    }
    int GetScore() const { return m_player_score; }
    bool IsBoosted() {
        if(GetScore() > 21 && !IsBusted) {
            IsBusted = 1;
            return true;
        }
        else if(IsBusted)
            return true;
        else
            return false;
    }
    //void Bust() { std::cout << " BUSTED"; }
    friend std::ostream& operator<< (std::ostream &out, GenericPlayer& gp){
        out << gp.m_name;
        for (int i = 0; i < gp.getHand().size(); ++i)
            out << " " << *gp.getHand()[i];

        out << " score: " << gp.GetScore();
        if(gp.IsBoosted())
            out << "  BUSTED";
        return out;
    }
};

class Player : public GenericPlayer{
public:
    Player(std::string name){
        setName(name);
    }
    bool IsHitting() const override{  //________________________________________/function should be marked [[nodiscard]] --------- ?
        char choice = 'n';
        std::cout << "\nDoes " << GetName() << " want another card? (y/n)";
        std::cin >> choice;
        if(choice == 'y')
            return true;
        return false;
    }
    void Win() const{ std::cout << "\n\n" << GetName() << " has won the game!\n\n"; }
    void Lose() const{ std::cout << "\n" << GetName() << " lost"; }
    void Push() const{ std::cout << "\n" << GetName() << " played a draw!"; }

};

class House : public GenericPlayer{
public:
    House()
    {
        std::string name = "House";
        setName(name);
    }
    bool IsHitting() const override {
        if (GetScore() <= 16)
            return true;
        return false;
    }
    void FlipFirstCard(){
        if(!getHand().empty())
            getHand()[0]->flip();
    }
};

//____________________________________________________________________________________________________________/ЗАДАНИЕ 3

/**
3. Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт. Класс Deck имеет 4 метода:
• vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.
• void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle
• vold Deal (Hand& aHand) - метод, который раздает в руку одну карту
• void AddltionalCards (GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока
 он может и хочет их получать

Обратите внимание на применение полиморфизма. В каких методах применяется этот принцип ООП?
 */

class Deck : public Hand{
    std::vector<std::shared_ptr<Card>> m_deck;
public:
    ~Deck() { m_deck.clear(); }
    Deck& Populate(){
        m_deck.reserve(52);
        for (int i = 0; i < 4; ++i) {
            for (int j = 1; j <= 13; ++j) {
                if(j >= 10) {
                    m_deck.push_back(std::make_shared <Card> ( i,10 )); ///____________/10, Jack, Queen, King -------- !
                    continue;
                }
                m_deck.push_back( std::make_shared <Card> (i,j) );
            }
        }
        return *this;
    }

    Deck& Shuffle() {
        std::random_device rd;
        std::mt19937 generator(rd());
        shuffle( m_deck.begin(), m_deck.end(), generator);
        outf << "Сгенерированная и отсортированная колода: \n";
        for (int i = 0; i < m_deck.size(); ++i) {
            if(!(i % 13))
                outf << "\n";
            outf << *m_deck[i] << " ";
        }
        return *this;
    }                                          //random_shuffle was deprecated in C++14 and completely removed in C++17.  ~

    void Deal (Hand& hand) {
        hand.Add(m_deck.back()); //__________________________________________________________________/[m_deck.size()] --------- !
        m_deck.pop_back();
    }

    void AddltionalCards (GenericPlayer& gp) {
        while(!gp.IsBoosted() && gp.IsHitting())
        {
            Deal(gp);
            gp.UpdateScore();
            std::cout << "\n" << gp;
        }

    }
};

//____________________________________________________________________________________________________________/ЗАДАНИЕ 4

/**
4. Реализовать класс Game, который представляет собой основной процесс игры. У этого класса будет 3 поля:
• колода карт
• рука дилера
• вектор игроков.
    Конструктор класса принимает в качестве параметра вектор имен игроков и создает объекты самих игроков.
В конструкторе создается колода карт и затем перемешивается.
    Также класс имеет один метод play(). В этом методе раздаются каждому игроку по две стартовые карты,
а первая карта дилера прячется. Далее выводится на экран информация о картах каждого игрока, в т.ч. и для дилера.
    Затем раздаются игрокам дополнительные карты. Потом показывается первая карта дилера и дилер набирает карты,
если ему надо. После этого выводится сообщение, кто победил, а кто проиграл. В конце руки всех игроков очищаются.
 */

class Game{
    std::vector<std::shared_ptr<Player>>players;
    Deck m_deck;
    House m_house;
public:
    Game(std::vector<std::string>&names){
        for (int i = 0; i < names.size(); ++i) {
            players.push_back(std::make_shared<Player>(names[i]));
            m_deck.Populate().Shuffle();                //___________________/ это нормально или считается плохим тоном? --------- ?
        }
    }
    void Play(){
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < players.size(); ++j) {
                m_deck.Deal(*players[j]);//______________________________/здесь может возникнуть проблема --------- !
            }
            m_deck.Deal(m_house);                    ///__________________________________/переместил во внешний цикл 16:19---- @
        }
        m_house.FlipFirstCard();

        m_house.UpdateScore();
        for (int i = 0; i < players.size(); ++i) {
            players[i] -> UpdateScore();
        }

        //отрисовка поля
        std::cout << "House:   " << m_house << "\n\n\n";
        for (int i = 0; i < players.size(); ++i)
            std::cout << *players[i] << "\n";

        //добор карт
        for (int i = 0; i < players.size(); ++i)
        {
            m_deck.AddltionalCards(*players[i]);

            //отрисовка поля
            std::cout << "\n\n\n" << "House:   " << m_house << "\n\n\n";
            for (int j = 0; j < players.size(); ++j)
                std::cout << *players[j] << "\n";
        }
        m_house.FlipFirstCard();
        m_deck.AddltionalCards(m_house);

        //отрисовка поля
        std::cout << "\n\n\n" << "House:   " << m_house << "\n\n\n";
        for (int i = 0; i < players.size(); ++i)
            std::cout << *players[i] << "\n";

        // подсчет очков

        int winner = -1;      // сделать массивом индексов, если длина больше 1 запустить протокол ничьей для игроков
        uint8_t cassWin = 0;


        for (int i = 0, high_score=0; i < players.size(); ++i)
        {
            if(players[i]->GetScore() > high_score)
            {
                high_score = players[i]->GetScore();
                winner = i; // будет массивом
            }
            // механика для игроков с одинаковым счетом
        }

        if(m_house.GetScore() <= 21 && m_house.GetScore() > players[winner]->GetScore())
        {
            std::cout << "\n\n The cassino wins ! \n\n";
            cassWin = 1;
            for (int i = 0; i < players.size(); ++i)
            {
                players[i]->Lose();
                players[i]->Clear();
            }
        }

        else if(m_house.GetScore() == players[winner]->GetScore())
        {
            std::cout << "\n\n The cassino and " << players[winner]->GetName() << " have a draw!\n\n";
            for (int i = 0; i < players.size(); ++i)
            {
                if(i != winner)
                    players[i]->Lose();
                players[i]->Clear();
            }

        }

        else
        {
            for (int i = 0; i < players.size(); ++i) {
                if (i == winner)
                    players[i]->Win();
                else
                    players[i]->Lose();
                players[i]->Clear();
            }
        }
        m_house.Clear();
        std::cout<<std::flush;
    }

};

#endif //OOP_LSN5_BLACKJACK_H
