#include <iostream>
#include <cstdlib>
#include <cmath>
#define SIZE 10

void print_ar(int *arr, int);
void auto_init(int *arr, int len, int **parr, int len2, int range);
void Qsort(int *arr, int first, int last);
void swap(int *a, int *b);

int main() {
    int *arr = new (std::nothrow) int [SIZE];
    if(!arr) {std::cout << "Memory fault";}
    auto_init(arr, SIZE,nullptr,0,98);
//    int arr[] = {7,10,2,4,8,5,3,9,1,6};
    std::cout << "original array: ";
    print_ar(arr, SIZE);
    int first = 0;
    int last = SIZE-1;
    Qsort(arr, first, last);
    print_ar(arr, SIZE);
    return 0;
}

void Qsort(int *arr, int first, int last)
{
//    std::cout << "\n\nstarting quick sort";
    int F = first; //0
    int L = last; //9
    int P = arr[(first+last)/2]; // arr[4] - 8
    if (last+1 <= 10)
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
    else {//    printf("\nfirst-%d pivot-%d last-%d", arr[F], P, arr[L]);
        do {

            // определить медиану

//        std::cout << "\nruning cycle " << "F-" << F << " L-" << L;
            while (arr[F] < P) { ++F; }
            while (arr[L] > P) { --L; }
            if (arr[F] >= arr[L]) {
//            std::cout << "\nswap " << arr[F] << " <-> " << arr[L];
                swap(&arr[F], &arr[L]);
//            std::cout << "\narr[F] - " << arr[F] << " arr[L] - " << arr[L];
                F++;
                L--;
//            std::cout << "\nF++ - " << arr[F] << " L-- - " << arr[L];
            }
        } while (arr[F] < arr[L]);

//    printf("\nPartition stop -> first-%d pivot-%d last-%d", arr[F], P, arr[L]);
//    print_ar(arr,SIZE);
        if (F < last)
            Qsort(arr, F, last);
        if (L > first)
            Qsort(arr, first, L);
    }
}