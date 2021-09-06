// ДЗ к занятию 3 Калинцев Ю.М.

#include <iostream>
using namespace std;

extern int a, b, c, d;

void task1_4(){
    float temp = a * (b + (static_cast<float>(c) / d));
    cout << "Task 1/4: " << temp << endl << endl;
}

void task_2() {
    task1_4();
    int x;
    cout << "Provide a number - ";
    cin >> x;
    cout << ((x > 21) ? 2 * (x - 21) : (21 - x)) << endl;
}

int main(){ //task_3
    //task_2();

    int ar[3][3][3]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27}, *par;
    //ar[1][1][1] = 111;
//    int i, k, j;
//    for(i = 0;i < 3; i++) {
//        for (j = 0; j < 3; j++) {
//            for (k = 0; k < 3; k++) {
//                ar[i][j][k] = k;
//            }
//            ar[i][j] = j;
//        }
//    }
    par = &ar[0][0][0];
    *par <<= 3;
    //*par++;
    cout << par[7] << endl;
    cout << ar[1][1][1];
    return 0;
}