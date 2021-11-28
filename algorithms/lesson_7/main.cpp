#include <iostream>
#include <cstdlib>
#include <cmath>


void Qsort(int *arr, int first, int last); // задание 1
void Bsort(int *arr, int len); // задание 2
//мои функции
void print_ar(int *arr, int);
void auto_init(int *arr, int len, int **parr, int len2, int range);
void swap(int *a, int *b);

int main() {
    int SIZE = 10;
    int *arr = new (std::nothrow) int [SIZE];
    if(!arr) {std::cout << "Memory fault";}
    auto_init(arr, SIZE,nullptr,0,98);

    print_ar(arr, SIZE);
    int first = 0;
    int last = SIZE-1;
    Qsort(arr, first, last);
    print_ar(arr, SIZE);
    delete[] arr;

    std::cout << "\n\nЗадание 2";
    SIZE = 20;
    int *arr2 = new (std::nothrow) int [SIZE];
    if(!arr2){
        std::cout << "Memory fault";}
    auto_init(arr2, SIZE,nullptr,0,98);
    print_ar(arr2, SIZE);

    Bsort(arr2, SIZE);
    print_ar(arr2, SIZE);
    delete[] arr2;
    return 0;
}

void Qsort(int *arr, int first, int last)
{
    if ((last-first) <= 10)
    {
        int tmp,current;
        for(int min=1, len=last+1;min<len;++min)
        {
            tmp = arr[min];
            current = min-1;
            while(current >= 0 && arr[current] > tmp)
            {
                arr[current+1] = arr[current];
                current--;
            }
            arr[current+1] = tmp;
        }
    }
    else {
        int F = first;
        int L = last;
        int P = last-1;

        if((arr[F]>arr[P])&&(arr[F]<arr[L])) {
            swap(&arr[F], &arr[P]);
        }
        else if((arr[L]>arr[F])&&(arr[L]<arr[P])) {
            swap(&arr[L], &arr[P]);
        }
        else
        do{
            while (arr[F] < arr[P]) { ++F; }
            while (arr[L] > arr[P]) { --L; }
            if (arr[F] >= arr[L]) {
                swap(&arr[F], &arr[L]);
                F++;
                L--;
            }
        } while (arr[F] < arr[L]);
        if (F < last)
            Qsort(arr, F, last);
        if (L > first)
            Qsort(arr, first, L);
    }
}

void Bsort(int *arr, int len)
{
    const int rows = 10; // количество блоков
    int depth = len; // величина блока
    int set[rows][depth+1];
    for (int i = 0; i < len; ++i)
        set[i][depth] = 0; //обнуление последнего элемента - счетчика

    for (int dig = 1; dig < 1000000 ; dig *=10) // проход по разрядам
    {
        for (int i = 0; i < len; ++i) {
            if(arr[i]%2 == 0)  // проверка четности
            {
                int bucket = (arr[i]/dig)%rows;       // /dig - определение разряда; %rows - индексация по блокам
                set[bucket][set[bucket][depth]++] = arr[i];
                // значение элемента arr[i] присваивается элементу с индексом
                // равным значению, на которое ссылается set[bucket][depth],
                // (т.е. на счетчик), т.о. это ссылка на значение последнего
                // элемента блока, которое мы используем для указания позиции
                // в этом же блоке, куда нужно записать число.
                // Затем значение set[bucket][depth] увеличивается на 1.
                arr[i] = -1; // "сброс" значения в оригинальном массиве для последующей перезаписи
            }
        }
//        std::cout << "\n";
//        for (int i = 0; i < len; ++i) {
//            std::cout << arr[i] << ", ";
        
        int itr = 0;
        for (int i = 0; i < rows; ++i) //перебор блоков
        {
            for (int j = 0; j < set[i][depth]; ++j) //проход по блоку
            {
                while(arr[itr] != -1) //пропуск нечетных чисел
                    itr++;
                arr[itr] = set[i][j];
            }
            set[i][depth] = 0; // обнуление счетчика для избежания повторных проходов
        }
    }
}