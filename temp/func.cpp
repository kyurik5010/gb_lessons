//#include <iostream>
//#include <vector>
//#include <utility>
//#include <cstdlib>

//using namespace std;


//int main(){
//
//    for(int i = 0; i < 5; i++) {
//        cout << "yes ";
//        for (int k = 0; k < 3; k++)
//            cout << "no ";
//    }
//    return 0;
//}

//unsigned long factorial(unsigned long f) // рекурсивная функция для нахождения n!
//{
//    if (f == 1 || f == 0) // базовое или частное решение
//    {
//        return 1; // все мы знаем, что 1!=1 и 0!=1
//    }
//    // функция вызывает саму себя, причём её аргумент уже на 1 меньше
//    unsigned long result = f * factorial(f - 1);
//    return result;
//}
//int main(int argc, char* argv[])
//{
//    unsigned long n;
//    cout << "Enter n!: ";
//    cin >> n;
//    cout << n << "!" << " = " << factorial(n) << endl;
//    return 0;
//}

//void test(int *arr ,char c[]){
//    int temp;
//    for (int i = 0; i < 6; ++i) {
//        arr[i] = c[i] - '0'; // перевод единичной чар в число
//    }

//    int temp = atoi(c);
//    fgets(temp,80, stdin)
//}

#include <iostream>
#include <string>
#include <stdexcept>

enum Type { A = 0, B, C };

std::ostream& operator << (std::ostream& out, const Type& t)
{
    switch(t) {
        case A: return (out << "A");
        case B: return (out << "B");
        case C: return (out << "C");
    }
    return (out);
}

std::istream& operator >> (std::istream& input, Type& t)
{
    std::string s;
    input >> s;
    if (s == "A") {
        // неявная конвертация в Type
        t = A;
    } else
    if (s == "B") {
        t = B;
    } else
    if (s == "C") {
        t = C;
    } else {
        // здесь можно выкинуть исключение
        throw std::runtime_error("incorrect input");
    }
    return (input);
}

int main(int argc, char *argv[])
{
    using namespace std;
    Type type;
    try {
        cin >> type;
    } catch(std::exception& e) {
        cout << e.what();
        return 1;
    }
    cout << type << "=" << static_cast<int>(type);
    return 0;
}
