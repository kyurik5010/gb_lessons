#include "BlackJack.h"
#include <cctype>
#include <sstream>

//----------------------------------------------------------------------------------------------------------------------
//Задание 1

void task1(){
    int number, x = 1;
    std::string buf;
    std::stringstream temp;
    while(x) {
        bool attempt = true;
        std::cout << "Введите целое число ";
        std::cin >> buf;
        for (int ind = 0; ind < buf.length(); ++ind) {
            if (!isdigit(buf[ind])) {
                attempt = !attempt;
                break;
            }
        }
        if(!attempt) {
            std::cout << "Попробуйте еще раз\n";
            continue;
        }
        temp << buf;
        temp >> number;
        x = !x;
    }
    std::cout << "Ваше число " << number;
}

//----------------------------------------------------------------------------------------------------------------------
//Задание 2

std::ostream& endll (std::ostream& out)
{
    out << "\n\n" << std::flush;
    return out;
}

//----------------------------------------------------------------------------------------------------------------------
//Задания 3 - 5 в заголовочном


int main() {
    task1();

    Player pl1("Yuri");
    Card c1(2,0);
    Card c2(1,5);
    Card c3(3,2);
    pl1.Add(c1);
    pl1.Add(c2);
    pl1.Add(c3);
    pl1.getHand()[0]->flip();
    pl1.getHand()[1]->flip();
    pl1.getHand()[2]->flip();
    std::cout << endll << "tasks 3-5\n" << pl1 ;
    return 0;
}
