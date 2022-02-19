//
// Created by Юрий Михайлович on 19.02.2022.
//

#include "Game.h"

Game::Game() {IsDiceRolled = false;}
void Game::SetDiceRolled(bool y) { IsDiceRolled = y; }
bool Game::GetDiceRolled() const { return IsDiceRolled; }