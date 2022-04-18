#include <iostream>
#include <locale>


int main(){
    setlocale(LC_ALL, "Russian");
    std::string a = "коза";
    std::string n = "о";
    for (auto i : a)
        if (n[0] == i)
            std::cout << i;
    return 0;
}