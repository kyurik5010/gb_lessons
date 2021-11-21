//
// Created by Юрий Михайлович on 21/11/2021.
//
#include <iostream>
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
    std::cout << "\n";
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}