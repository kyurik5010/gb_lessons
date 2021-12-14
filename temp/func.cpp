#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>

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

void test(int *arr ,char c[]){
    int temp;
    for (int i = 0; i < 6; ++i) {
        arr[i] = c[i] - '0'; // перевод единичной чар в число
    }

//    int temp = atoi(c);
//    fgets(temp,80, stdin)
}

 int main(){
    int arr[6];
    test(arr, "010011");
     for (int i = 0; i < 6; ++i) {
         cout << arr [i] << endl;
     }

     return 0;
 }