#include "BlackJack.h"


Card::Card (int suit, int value) {
    st = static_cast<m_suit> (suit);
    vl = static_cast<m_value> (value);
}
void Card::flip () { isFacedUp = !isFacedUp; }
Card::m_value Card::getValue () { return vl; }
Card::m_suit Card::getSuit () { return st; }
void Card::setAce(int power){ vl = static_cast<m_value>(power); }
std::ostream& operator<< (std::ostream &out, Card &card){
    if(!card.isFacedUp)
        out << "XX";
    else
    {
        out << "(";
        switch (card.st)
        {
            case 0: out << "diamonds"; break;
            case 1: out << "hearts"; break;
            case 2: out << "spades"; break;
            case 3: out << "cross"; break;
        }
        out << "|";
        switch (card.vl)
        {
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


Hand::Hand(){ m_hand.reserve(5); }
Hand::~Hand() { Clear(); }
void Hand::Add(std::shared_ptr<Card> &c){ m_hand.push_back(c); }
void Hand::Clear(){ m_hand.clear(); }  //подумал что этого хватит с учетом того, что программа переведена на умные указатели
std::vector<std::shared_ptr<Card>> Hand::getHand() { return m_hand; }
int Hand::GetValue() const
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

void GenericPlayer::setName(std::string &name) { m_name = name; }
std::string GenericPlayer::GetName() const { return m_name; }            //по поводу const не уверен
//bool GenericPlayer::IsHitting() const;                        //здесь не уверен, такая же пометка в h
void GenericPlayer::UpdateScore(){ m_player_score = GetValue(); }
int GenericPlayer::GetScore() const { return m_player_score; }
bool GenericPlayer::IsBoosted()
{
    if(GetScore() > 21 && !IsBusted) {
        IsBusted = 1;
        return true;
    }
    else if(IsBusted)
        return true;
    else
        return false;
}
bool operator==(GenericPlayer& gp1, GenericPlayer& gp2) // для использования влогических операциях при подсчете очков
{
    return (gp1.GetName() == gp2.GetName());
}
std::ostream& operator<< (std::ostream &out, GenericPlayer& gp)
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


Player::Player(std::string name){ setName(name);}
bool Player::IsHitting() const
{
char choice = 'n';
std::cout << "\nDoes " << GetName() << " want another card? (y/n)";
std::cin >> choice;
if(choice == 'y')
return true;
return false;
}
void Player::Win() const{ std::cout << "\n\n" << GetName() << " has won the game!\n"; }
void Player::Lose() const{ std::cout << "\n" << GetName() << " lost"; }
//Player::Push() const{ std::cout << "\n" << GetName() << " played a draw!"; } // решил не использовать


House::House()
{
    std::string name = "House";
    setName(name);
}
bool House::IsHitting() const{
    if (GetScore() <= 16)
    return true;
    return false;
}
void House::Lose() const{ std::cout << "\nThe Cassino lost"; }
void House::FlipFirstCard()
{
    if(!getHand().empty())
        getHand()[0]->flip();
}


//____________________________________________________________________________________________________________/ЗАДАНИЕ 3

Deck::~Deck() { m_deck.clear(); }
Deck& Deck::Populate()
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
Deck& Deck::Shuffle()
{
    std::random_device rd;
    std::mt19937 generator(rd()); //random_shuffle was deprecated in C++14 and completely removed in C++17.  ~
    shuffle( m_deck.begin(), m_deck.end(), generator);
    return *this;
}
void Deck::Deal (Hand& hand)
{
    hand.Add(m_deck.back());
    m_deck.pop_back();
}
void Deck::AddltionalCards (GenericPlayer& gp)
{
    while(!gp.IsBoosted() && gp.IsHitting())
    {
        Deal(gp);
        gp.UpdateScore();
        std::cout << "\n" << gp;
    }

}

//____________________________________________________________________________________________________________/ЗАДАНИЕ 4

Game::Game(std::vector<std::string>&names)
{
    for (int i = 0; i < names.size(); ++i)
    {
        players.push_back(std::make_shared<Player>(names[i]));
    }
    m_deck.Populate();
    m_deck.Shuffle();
}
void Game::PrintTable(bool final) //Вывод игрового стола в консоль
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n____________________________________\n"
              << m_house;
    if(!final)
        std::cout<< "\n\n";
    else
        std::cout<< " score: " << m_house.GetScore() << "\n\n";
    for (int i = 0; i < players.size(); ++i)
        std::cout << *players[i] << "\n";
    std::cout << "____________________________________\n";
}
void Game::Play()
{
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
                std::cout << " and " << winners[i]->GetName();
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
                std::cout << " and " << winners[i]->GetName();
            }
            std::cout << " win and have a draw!\n\n";
            std::cout << " The cassino lost\n";
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