//
// Created by Юрий Михайлович on 19.02.2022.
//
#pragma once
#ifndef DACHI_CASE_GAME_H
#define DACHI_CASE_GAME_H


class Game{
private:
    bool IsDiceRolled;
public:
    Game();
    void SetDiceRolled(bool y);
    bool GetDiceRolled() const;
};



#endif //DACHI_CASE_GAME_H
