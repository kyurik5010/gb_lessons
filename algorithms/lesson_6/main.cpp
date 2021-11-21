#include <iostream>
#include <cstdlib>
#include <cmath>
#define SIZE 3

void print_2dar(int **arr, int);
void print_ar(int *arr, int);
void double_sort(int **arr);
void TPK(int *arr);
void swap(int *a, int *b);

int main() {
    srand(time(0));
    int **arr = new (std::nothrow) int * [SIZE];
    for(int i=0;i<3;++i)
        arr[i] = new int [SIZE];

    if(arr == nullptr){
        std::cout << "memory fault";
        return 1;}

    for(int i=0;i<SIZE;++i)
    {
        for(int j=0;j<SIZE;++j)
            arr[i][j] = rand() % 100;
    }
/*
    arr[0][0] = 8;
    arr[0][1] = 4;
    arr[0][2] = 5;
    arr[1][0] = 7;
    arr[1][1] = 3;
    arr[1][2] = 9;
    arr[2][0] = 1;
    arr[2][1] = 6;
    arr[2][2] = 2;
*/ // debug
    std::cout << "\noriginal array: ";
    print_2dar(arr, SIZE);
    double_sort(arr);
    std::cout << "\n  sorted array: ";
    print_2dar(arr, SIZE);


    for(int i=0;i<SIZE;++i)
        delete[] arr[i];
    delete[] arr;

    // задание 2
#define SIZE 11
    int *tpk = new (std::nothrow) int[SIZE];
    if(tpk == nullptr){
        std::cout << "memory fault";
        return 1;}
    for(int i=0;i<SIZE;++i)
        tpk[i] = rand() % 100+1;

    //debug
//    for(int i=0;i<SIZE;++i)
//        tpk[i] = i+1;
//    print_ar(tpk, SIZE);
    TPK(tpk);

    delete[] tpk;
    return 0;
}

//задание 1
void double_sort(int **arr)
{
    int TL = SIZE*SIZE; // total length

    for(int step=0;step<TL;++step)
    {
        for (int j = 0, i=0,k=1; j < TL+1; ++j) // k & i - iterators; TL+1 для пропуска шага
        {
            if(k>2)
            {
                k=0;
                ++i;
                continue;
            }
            if (k==0 && (arr[i][k] < arr[i-1][2]))
                // почему-то мне дает вставить этот блок в предыдущий и таким образом избежать костылей
                // вроде continue, пропсука шага и TL+1 в условии цикла (выдает рантайм ошибку SIGSEGV)
                swap(&arr[i][k], &arr[i - 1][2]);
            else if (k>0 && (arr[i][k] < arr[i][k - 1]))
                swap(&arr[i][k], &arr[i][k - 1]);
            ++k; // это тоже из-за continue >_<
        }
    }
}

//задание 2
void TPK(int *arr){
    for(int i=SIZE;i>0;--i)
    {
        for (int k = SIZE - 1; k > 0; --k)
            if (arr[k] > arr[k - 1])
                swap(&arr[k], &arr[k - 1]);
    }
    print_ar(arr, SIZE);
    for(int i=0;i<SIZE;++i)
    {
        double x = sqrt(fabs(arr[i])) + 5 * pow(arr[i], 3);
        if(x>400)
            printf("\nрезультат элемента %d > 400 (tpk[%d] == %f)",i,i,x);
    }
}