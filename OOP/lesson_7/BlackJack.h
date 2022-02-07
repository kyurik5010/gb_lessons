#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <random> // для shuffle
//#include <fstream>



#ifndef OOP_LSN5_BLACKJACK_H
#define OOP_LSN5_BLACKJACK_H
//std::string filename = "log_file.txt"; // для дебага
//std::ofstream outf(filename);


#pragma pack (push, 1)
class Card{
    enum m_suit {diamonds, hearts, spades, cross};
    enum m_value{
        ace = 1,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
    };
    m_suit st;
    m_value vl;
    bool isFacedUp = true;
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
                case 1: out << "ace"; break;
                case 2: out << "two"; break;
                case 3: out << "three"; break;
                case 4: out << "four"; break;
                case 5: out << "five"; break;
                case 6: out << "six"; break;
                case 7: out << "seven"; break;
                case 8: out << "eight"; break;
                case 9: out << "nine"; break;
                case 10: out << "ten"; break;
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
    void Add(std::shared_ptr<Card> &c){ m_hand.push_back(c); }
    void Clear(){ m_hand.clear(); }  //подумал что этого хватит с учетом того, что программа переведена на умные указатели
    std::vector<std::shared_ptr<Card>> getHand() { return m_hand; }

    int GetValue() const
    {
        int score = 0;
        int ace = 0;
        int* aces = new int [m_hand.size()];
        for (int i = 0; i < m_hand.size(); ++i)
        {
            if(m_hand[i]->getValue() == 1)
                aces[ace++] = i;
            score += m_hand[i]->getValue();
        }

        for (int i = 0; i < ace; ++i)
        {
            if(score + 11 <= 21)
            {
                m_hand[aces[i]]->setAce(11);
                score += 11;
            }
        }
        delete[] aces;
        return score;
    }
};

class GenericPlayer : public Hand{
    std::string m_name;
    int m_player_score = 0;
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
    friend bool operator==(GenericPlayer& gp1, GenericPlayer& gp2) // для удобства при логических условиях в подсчете очков
    {
        return (gp1.GetName() == gp2.GetName());
    }
    friend std::ostream& operator<< (std::ostream &out, GenericPlayer& gp)
    {
        out << gp.m_name;
        for (int i = 0; i < gp.getHand().size(); ++i)
            out << " " << *gp.getHand()[i];
        if(gp.m_name != "House")
            out << " score: " << gp.GetScore();
        if(gp.IsBoosted())
            out << "  BUSTED";
        return out;
    }
};

class Player : public GenericPlayer{
public:
    Player(std::string name){ //Single-argument constructors must be marked explicit to avoid unintentional implicit conversions
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
    void Win() const{ std::cout << "\n\n" << GetName() << " has won the game!\n"; }
    void Lose() const{ std::cout << "\n" << GetName() << " lost"; }
    // void Push() const{ std::cout << "\n" << GetName() << " played a draw!"; } // решил не использовать

};

class House : public GenericPlayer{
public:
    House()
    {
        std::string name = "House";
        setName(name);
    }
    bool IsHitting() const override
    {
        if (GetScore() <= 16)
            return true;
        return false;
    }
    void Lose() const{ std::cout << "\nThe Cassino lost"; }
    void FlipFirstCard(){
        if(!getHand().empty())
            getHand()[0]->flip();
    }
};

//____________________________________________________________________________________________________________/ЗАДАНИЕ 3

class Deck : public Hand{
    std::vector<std::shared_ptr<Card>> m_deck;
public:
    ~Deck() { m_deck.clear(); }
    Deck& Populate()
    {
        m_deck.reserve(52);
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 1; j <= 13; ++j)
            {
                if(j >= 10)
                {
                    m_deck.push_back(std::make_shared <Card> ( i,10 ));
                    continue;
                }
                m_deck.push_back( std::make_shared <Card> (i,j) );
            }
        }
        return *this;
    }

    Deck& Shuffle()
    {
        std::random_device rd;
        std::mt19937 generator(rd()); //random_shuffle was deprecated in C++14 and completely removed in C++17.  ~
        shuffle( m_deck.begin(), m_deck.end(), generator);
//      outf << "Сгенерированная и отсортированная колода: \n";                  // это все для дебага
//        for (int i = 0; i < m_deck.size(); ++i)
//        {
//            if(!(i % 13))
//                outf << "\n";
//            outf << *m_deck[i] << " ";
//        }
        return *this;
    }

    void Deal (Hand& hand)
    {
        hand.Add(m_deck.back());
        m_deck.pop_back();
    }

    void AddltionalCards (GenericPlayer& gp)
    {
        while(!gp.IsBoosted() && gp.IsHitting())
        {
            Deal(gp);
            gp.UpdateScore();
            std::cout << "\n" << gp;
        }

    }
};

//____________________________________________________________________________________________________________/ЗАДАНИЕ 4

class Game{
    std::vector<std::shared_ptr<Player>>players;
    Deck m_deck;
    House m_house;
public:
    Game(std::vector<std::string>&names)
    {
        for (int i = 0; i < names.size(); ++i)
        {
            players.push_back(std::make_shared<Player>(names[i]));
        }
        m_deck.Populate();
        m_deck.Shuffle();
    }

    void PrintTable(bool final = false){ //
        std::cout << "\n\n\n\n\n____________________________________\n"
                  << m_house;
        if(!final)
            std::cout<< "\n\n";
        else
            std::cout<< " score: " << m_house.GetScore() << "\n\n";
        for (int i = 0; i < players.size(); ++i)
            std::cout << *players[i] << "\n";
        std::cout << "____________________________________";
    }

    void Play(){
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < players.size(); ++j) {
                m_deck.Deal(*players[j]);
            }
            m_deck.Deal(m_house);
        }
        m_house.FlipFirstCard();

        m_house.UpdateScore();
        for (int i = 0; i < players.size(); ++i) {
            players[i] -> UpdateScore();
        }

        PrintTable();

        //добор карт
        for (int i = 0; i < players.size(); ++i)
        {
            m_deck.AddltionalCards(*players[i]);
            PrintTable();
        }
        m_house.FlipFirstCard();
        m_deck.AddltionalCards(m_house);

        PrintTable(true);

        // подсчет очков
        std::vector<std::shared_ptr<Player>>winners; // для игроков с одинаковым счетом
        uint8_t IsCassWin = 0;

        for (int i = 0, j = 0, high_score=0; i < players.size(); ++i)
        {
            if(players[i]->GetScore() > high_score && !players[i]->IsBoosted())
            {
                high_score = players[i]->GetScore();
                if(!winners.empty()) {
                    winners.clear();
                    winners.push_back(players[i]);
                    continue;
                }
                winners.push_back(players[i]);
            }
            else if(players[i]->GetScore() == high_score)
                winners.push_back(players[i]);
        }

        if(!m_house.IsBoosted()){
            if(winners.empty()) {
                IsCassWin = 1;
                std::cout << "\n\n The cassino wins ! \n\n";
                for (int i = 0; i < players.size(); ++i)
                {
                    players[i]->Lose();
                    players[i]->Clear();
                }
            }
            else if((m_house.GetScore() == 21) || (m_house.GetScore() == winners[0]->GetScore()))
                IsCassWin = 1;
        }

        if(winners.size() == 1)
        {
            if(IsCassWin) {
                if (m_house.GetScore() > winners[0]->GetScore())
                {
                    std::cout << "\nThe cassino wins ! \n\n";
                    for (int i = 0; i < players.size(); ++i)
                    {
                        players[i]->Lose();
                        players[i]->Clear();
                    }
                }
                else if (m_house.GetScore() == winners[0]->GetScore())
                {
                    std::cout << "\n\n The cassino and " << winners[0]->GetName() << " have a draw!\n\n";
                    for (int i = 0; i < players.size(); ++i)
                    {
                        if (players[i] != winners[0])
                            players[i]->Lose();
                        players[i]->Clear();
                    }

                }
            }
            else
            {
                winners[0]->Win();
                m_house.Lose();
                for (int i = 0; i < players.size(); ++i)
                {
                    if (players[i] != winners[0])
                        players[i]->Lose();
                    players[i]->Clear();
                }
            }
        }
        else if(winners.size() > 1) // для игроков с одинаковым счетом
        {
            if(IsCassWin)
            {
                std::cout << "\nThe Cassino ";
                for (int i = 0; i < winners.size(); ++i)
                {
                    std::cout << " and " << winners[i];
                }
                std::cout << " win and have a draw!";
                for (int i = 0, bad = 0; i < players.size(); ++i)
                {
                    for (int j = 0; j < winners.size(); ++j)
                    {
                        if(players[i] == winners[j])
                        {
                            bad = 1;
                        }
                    }
                    if(bad)
                        continue;
                    else
                        players[i]->Lose();
                }
                for (int i = 0; i < players.size(); ++i) {
                    players[i]->Clear();
                }
            }
            else
            {
                std::cout << "\n Players " << winners[0]->GetName();
                for (int i = 1; i < winners.size(); ++i) {
                    std::cout << " and " << winners[i];
                }
                std::cout << " win and have a draw!\n\n";
                for (int i = 0, bad = 0; i < players.size(); ++i)
                {
                    for (int j = 0; j < winners.size(); ++j)
                    {
                        if(players[i] == winners[j])
                        {
                            bad = 1;
                        }
                    }
                    if(bad)
                        continue;
                    else
                        players[i]->Lose();
                }
                for (int i = 0; i < players.size(); ++i) {
                    players[i]->Clear();
                }
            }
        }
        m_house.Clear();
        std::cout<<std::flush;
    }
};

#endif //OOP_LSN5_BLACKJACK_H
