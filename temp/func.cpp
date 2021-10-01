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
     // = {'.','.','.','.','.'}

     char arr[4][5];
     char sym[3] = {47,32,92};
     //char arr_2[] = {'e','d','c','b','a'};
     for(int j = 0; j<4; j++){
         for(int i=0;i<5;i++) {
             //std::swap(arr_1[j], arr_2[j]);
             //arr[j][i] = '.';
             switch(j){
                 case 2: {
                     i = 4;
                     if(i==4)
                         arr[j][i] = 47;
                 }
                     break;
                 case 3:
                     if
             }
             std::cout << arr[j][i];
         }
         cout << endl;
     }


     return 0;
 }