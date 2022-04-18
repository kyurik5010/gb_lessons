#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include "timer.h"
//TASK_1__________________________________________________________________________________________________________TASK_1
template< typename T >
void Swap(T &ptr1, T &ptr2){
    T temp = std::move(&*ptr1);
    ptr1 = std::move(&*ptr2);
    ptr2 = std::move(temp);
}

void task1(){
    std::cout << "TASK_1\n";
    int a = 1, b = 2;
    int *ptr1 = &a, *ptr2 = &b;
    std::cout << *ptr1 << "(" << &*ptr1 << "), " << *ptr2 << "(" << &*ptr2 << ")" << std::endl;
    Swap(ptr1, ptr2);
    std::cout << *ptr1 << "(" << &*ptr1 << "), " << *ptr2 << "(" << &*ptr2 << ")" << std::endl;
}

//TASK_2__________________________________________________________________________________________________________TASK_2

template< typename T >
void SortPointers(std::vector<T*> &vec){
    std::sort(vec.begin(), vec.end(), [](T *ptr1, T *ptr2){ return *ptr1 < *ptr2; });
}

void task2(){
    std::vector<int*> arr;
    std::cout << "\nTASK_2\noriginal vector: \n";
    for(int i = 0; i < 20; ++i){
        arr.emplace_back(new int (rand()% 100));
        std::cout << *arr[i] << " ";
    }
    SortPointers(arr);
    std::cout << "\nsorted vector: \n";
    for(int i = 0; i < 20; ++i){
        std::cout << *arr[i] << " ";
        delete arr[i];
    }
}

//TASK_3__________________________________________________________________________________________________________TASK_3

void VowelCounter1();
void VowelCounter2();
void VowelCounter3();
void VowelCounter4();

void task3(){
    std::cout << "\n\nTASK_3\n";

    VowelCounter1();// count_if и find
    VowelCounter2();// count_if и цикл for
    VowelCounter3();// цикл for и find
    VowelCounter4();// 2 цикла for
}

void VowelCounter1(){
    std::ifstream file ("file.txt");
    std::string line;
    std::string n = "aeiouy";
    int vowels = 0;
    Timer timer("VowelCounter1 (count_if и find)");

    while(file){
        getline(file,line);
        vowels += std::count_if(line.begin(), line.end(), [&](char x){
            return n.find(x) != std::string_view::npos;});
    }
    timer.print();
    std::cout << " found " << vowels << " vowels\n";
}


void VowelCounter2(){
    std::ifstream file ("file.txt");
    std::string line;
    std::string n = "aeiouy";
    int vowels = 0;

    Timer timer("VowelCounter2 (count_if и цикл for)");
    while(file){
        getline(file,line);
        vowels += std::count_if(line.begin(), line.end(), [=](char x){
                for(int i = 0; i < n.length(); ++i)
                    return n[i] == x;}
                    ); //что-то не так с возвращением значений из лямбды (не всегда возвращает), но я не вижу где ошибка
    }                  //а из-за этого неверно подсчитывается количество гласных (в дебаге работа не просматривается к сожалению)
    timer.print();
    std::cout << " found " << vowels << " vowels\n";
}

void VowelCounter3(){
    std::ifstream file ("file.txt");
    std::string line;
    std::string n = "aeiouy";
    int vowels = 0;

    Timer timer("VowelCounter3 (цикл for и find)");
    while(file){
        getline(file,line);
        //int len = sizeof(line) / sizeof(line[0]);
        for(int i  = 0; i < line.length(); ++i) {
            std::string::iterator it = std::find(n.begin(),n.end(),line[i]);
            if(it != n.end())
                ++vowels;
        }
        line = "";
    }

    timer.print();
    std::cout << " found " << vowels << " vowels\n";
}

void VowelCounter4(){
    std::ifstream file ("file.txt");
    std::string line;

    std::string n = "aeiouy";
    int vowels = 0;

    Timer timer("VowelCounter4 (2 цикла for)");
    while(file){
        getline(file,line);

        for(int i = 0;i < line.length(); ++i){
            for(int k = 0; k < n.length(); ++k){
                if (line[i] == n[k])
                    ++vowels;
            }
        }
        line = "";
    }

    timer.print();
    std::cout << " found " << vowels << " vowels\n";
}

//__________________________________________________________________________________________________________________MAIN
int main() {

//    task1();
//    task2();
    task3();


    return 0;
}
