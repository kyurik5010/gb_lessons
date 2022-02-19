#include <iostream>
#include "Quests.h"


int main() {
    Quests q;
    std::cout << "\ncurrent IsDiceRolled - " << q.GetDiceRolled();
    q.func(true);
    std::cout << "\ncurrent IsDiceRolled - " << q.GetDiceRolled();

    return 0;
}
