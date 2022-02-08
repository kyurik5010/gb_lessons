//
// Created by Юрий Михайлович on 08.02.2022.
//
#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <random> // для shuffle

#ifndef LSN_7_BLACKJACK_BLACKJACK_H
#define LSN_7_BLACKJACK_BLACKJACK_H

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
    Card (int suit, int value);
    void flip ();
    m_value getValue ();
    m_suit getSuit ();
    void setAce(int power);
    friend std::ostream& operator<< (std::ostream &out, Card &card);
};
#pragma pack (pop)



class Hand{
    std::vector<std::shared_ptr<Card>> m_hand;
public:
    Hand();
    ~Hand();
    void Add(std::shared_ptr<Card> &c);
    void Clear();
    std::vector<std::shared_ptr<Card>> getHand();
    int GetValue() const;
};

class GenericPlayer : public Hand{
    std::string m_name;
    int m_player_score = 0;//очки подсчитываются только при изменениях в руках, в остальное время информация берется отсюда
    uint8_t IsBusted = 0;
public:
    void setName(std::string &name);
    std::string GetName() const;
    virtual bool IsHitting() const = 0; // здесь не уверен, такая же пометка в срр
    void UpdateScore();
    int GetScore() const;
    bool IsBoosted();
    friend bool operator==(GenericPlayer& gp1, GenericPlayer& gp2);
    friend std::ostream& operator<< (std::ostream &out, GenericPlayer& gp);
};

class Player : public GenericPlayer{
public:
    Player(std::string name);
    bool IsHitting() const override;
    void Win() const;
    void Lose() const;
    // void Push() const; //решил не использовать

};

class House : public GenericPlayer{
public:
    House();
    bool IsHitting() const override;
    void Lose() const;
    void FlipFirstCard();
};

//____________________________________________________________________________________________________________/ЗАДАНИЕ 3

class Deck : public Hand{
    std::vector<std::shared_ptr<Card>> m_deck;
public:
    ~Deck();
    Deck& Populate();
    Deck& Shuffle();
    void Deal (Hand& hand);
    void AddltionalCards (GenericPlayer& gp);
};

//____________________________________________________________________________________________________________/ЗАДАНИЕ 4

class Game{
    std::vector<std::shared_ptr<Player>>players;
    Deck m_deck;
    House m_house;
public:
    Game(std::vector<std::string>&names);

    void PrintTable(bool final = false);

    void Play();
};

#endif //LSN_7_BLACKJACK_BLACKJACK_H
