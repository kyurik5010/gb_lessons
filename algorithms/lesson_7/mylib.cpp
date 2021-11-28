//
// Created by Юрий Михайлович on 21/11/2021.
//
#include <iostream>
#include <cstdlib>
// вспомнить как задействовать переменные из других компонентов

void print_2dar(int **arr, int SIZE)
{
    std::cout << "\n";
    for(int i=0;i< SIZE;++i)
    {
        for(int j=0;j<SIZE;++j)
        {
            if(j == (SIZE - 1))
                std::cout << arr[i][j] << " ";
            else
                std::cout << arr[i][j] << ",";
        }
    }
    std::cout << "\n";
}

void print_ar(int *arr, int SIZE)
{
    std::cout << "\n";
    for(int i=0;i<SIZE;++i)
    {
        if(i == SIZE-1)
            std::cout << arr[i];
        else
            std::cout << arr[i] << ", ";
    }
//    std::cout << "\n";
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void auto_init(int *arr, int len, int **parr = nullptr, int len2=0, int range=98)
{
    srand(time(0));
    if(!parr)
    {
        for (int i = 0; i < len; ++i)
            arr[i] = rand() % range + 1;
    }
    else if((parr != 0) && (len2 != 0))
    {
        for (int k = 0; k < len; ++k)
            for (int i = 0; i < len2; ++i)
                parr[k][i] = rand() % range + 1;

    }
    else if((parr != nullptr) && (len2 == 0))
        std::cout << "Вы забыли указать размер дочерних массивов";
}
