//
// Created by Юрий Михайлович on 19/09/2021.
//
#include <iostream>
#include <cstdlib>

using namespace std;
//=====================================================================================================================
//Создайте проект из 2х cpp файлов и заголовочного (main.cpp, mylib.cpp, mylib.h) во втором модуле mylib
// объявить 3 функции: для инициализации массива (типа float), печати его на экран и подсчета количества
// отрицательных и положительных элементов. Вызывайте эти 3-и функции из main для работы с массивом.
//=====================================================================================================================

namespace msp {
    void init(float arr[], size_t size) {
        srand(time(0));
        for(int i=0;i<size;i++)
            arr[i] = static_cast<float>(rand() % 200-100) / 1.15;
    }

    void printarr(float arr[], size_t size) {
        for(int i=0;i<size;i++)
            cout << arr[i] << ", ";
    }

    int checksum(float arr[], size_t size) {
        int count = 0;
        for(int i=0;i<size;i++)
            count += (arr[i]>0) ? 1 : 0;
        return count;
    }
}