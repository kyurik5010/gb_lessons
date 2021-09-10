/*
 * Домашнее задание к уроку 4
 * Ю.М.Калинцев
 * 08/09/2021
 */

#include <iostream>
using namespace std;

void task_1();
void task_2(int a, int b);
void task_3();
void task_4();


//1. Написать программу, проверяющую что сумма двух (введенных с клавиатуры) чисел лежит в пределах от 10 до 20
//(включительно), если да – вывести строку "true", в противном случае – "false";

void task_1(){
    int a, b;
    cin >> a >> b;

    if (a+b >= 10 && a+b <= 20)
        cout << "task_1 - true\n";
    else
        cout << "task_1 - false\n";

    int *aptr = &a;
    int *bptr = &b;

    task_2(*aptr, *bptr);
}


//2. Написать программу, выводящую на экран строку “true”, если две целочисленные константы, объявленные
// в её начале либо обе равны десяти сами по себе, либо их сумма равна десяти. Иначе "false".

void task_2(int a, int b){
    if ((a == 10 && b == 10) || a+b == 10)
        cout << "task_2 - true\n";
    else
        cout << "task_2 - false\n";
}


//3. Написать программу которая выводит на экран список всех нечетных чисел от 1 до 50.
// Например: "Your numbers: 1 3 5 7 9 11 13 …". Для решения используйте любой С++ цикл.

void task_3(){
    for(int i = 1; i <=50; ) {
        cout << i << ", ";
        i += 2;
    }
}


//4. Написать программу, проверяющую, является ли некоторое число - простым. Простое число — это
//целое положительное число, которое делится без остатка только на единицу и себя само.

void task_4(){
    int x;
    cout << "Provide an integer for a check: ";
    cin >> x;
    int dividers[x];

    for(int j = 0; j <= x ; j++){
        dividers[j] = j;
    }

    size_t counter = 0;
    size_t len = sizeof(dividers) / sizeof(dividers[0]);

    for(int i = 1; i <= len; i++) {
        if (x % dividers[i] == 0)
            counter++;
    }

    if (counter > 2)
        cout << "\n" << x << " is complicated, it has " << counter << " dividers";
    else
        cout << "\n" << x << " is prime";
}


//5. Пользователь вводит с клавиатуры число (год): от 1 до 3000. Написать программу, которая определяет
//является ли этот год високосным. Каждый 4-й год является високосным, кроме каждого 100-го, при этом каждый 400-й –
//високосный. Вывести результаты работы программы в консоль.

int main() { //task_5
    task_1();
    task_3();
    task_4();

    int yr;

    do{
        cout << "provide a year: ";
        cin.get();
        cin >> yr;
    }while(yr < 1 || yr > 3000); // почему то Clion не начинает цикл, а меняет
                                 // введенное отрицательное число в положительное. 
                                 // с мобильника работает без проблем.

        if (((yr % 4 == 0) && (yr % 100 != 0)) || (yr % 400 == 0))
            cout << yr << " is a leap year";
        else
            cout << yr << " is an ordinary year";
    return 0;
}