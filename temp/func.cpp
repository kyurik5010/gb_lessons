#include <iostream>
#include <vector>
#include <utility>

using namespace std;


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
 int main(){
     int x = 4;
     x %= 10;
     cout << x;
     return 0;
 }