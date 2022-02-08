#include "BlackJack.h"

int main() {
    char choice;
    std::string name;
    std::vector<std::string>players;

    while(true)
    {
        std::cout << "Enter player's name: ";
        std::cin >> name;
        players.push_back(name);
        std::cout << "\nMore players? (y/n): ";
        std::cin >> choice;
        if(choice == 'y')
            continue;
        else
            break;
    }
    while(true)
    {
        std::cout << "\n\nStarting game..\n";
        Game BlackJack(players);
        BlackJack.Play();
        std::cout << "\n\nWant to play again? (y/n): ";
        std::cin >> choice;
        if(choice == 'y')
            continue;
        else
            break;
    }
    return 0;
}
