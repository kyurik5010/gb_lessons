#include <iostream>
#include <cstdlib>
#include <cmath>
#define SIZE 49

void print_ar(int *arr, int);
void auto_init(int *arr, int len, int **parr, int len2, int range);
void Qsort(int *arr, int first, int last);
void swap(int *a, int *b);

int main() {
    int *arr = new (std::nothrow) int [SIZE];
    if(!arr) {std::cout << "Memory fault";}
    auto_init(arr, SIZE,nullptr,0,98);
//    int arr[] = {7,10,2,4,8,5,3,9,1,6,15,13,17,11,12,14,16}; // весь закоменченный код - дебаг (штатный на маке не работает)
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
    if ((last-first) <= 10)
    {
//        std::cout<<"\n\nstarting insert sort";
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

//        printf("\n\ninitial points - F/arr[%d]/%d P/arr[%d]/%d L/arr[%d]/%d",F, arr[F], P, arr[P], L, arr[L]);

        if((arr[F]>arr[P])&&(arr[F]<arr[L])) {
            swap(&arr[F], &arr[P]);
//            std::cout << "\nredefined pivot:";
//            std::cout << " F/arr["<<F<<"]/"<< arr[F] << " P/arr["<<P<<"]/"<<arr[P]<<" L/arr["<<L<<"]/"<<arr[L];
//            print_ar(arr,SIZE);
        }
        else if((arr[L]>arr[F])&&(arr[L]<arr[P])) {
            swap(&arr[L], &arr[P]);
//            std::cout << "\nredefined pivot:";
//            std::cout << "\nF-" << arr[F] << " P-" << arr[P] <<" L-" << arr[L];
//            print_ar(arr,SIZE);
        }
        else
//            std::cout << "\n\npivot remains";
        do{
//            std::cout << "\nruning cycle " << " F/arr[" << F << "]/" <<arr[F]<< " L/arr[" << L<<"]/"<<arr[L];
            while (arr[F] < arr[P]) { ++F; }
            while (arr[L] > arr[P]) { --L; }
//            std::cout << "\nstop: F/arr["<<F<<"]/"<<arr[F]<<" > P/arr["<<P<<"]/"<<arr[P]<<" > L/arr["<<L<<"]/"<<arr[L];
            if (arr[F] >= arr[L]) {
//                std::cout << "\nswapping F/arr["<<F<<"]/"<<arr[F]<<" <-> L/arr["<<L<<"]/"<< arr[L];
                swap(&arr[F], &arr[L]);
//                std::cout << "\n swapped F/arr["<<F<<"]-"<<arr[F]<<"     L/arr["<<L<<"]-"<<arr[L];
//                print_ar(arr,SIZE);
                F++;
                L--;

//                std::cout << "\nF++ -> arr["<<F<<"]/"<<arr[F]<<"\nL-- -> arr["<<L<<"]/"<<arr[L];
            }
        } while (arr[F] < arr[L]);

//    printf("\nPartition stop -> first-%d pivot-%d last-%d", arr[F], arr[P], arr[L]);
//    print_ar(arr,SIZE);
        if (F < last)
            Qsort(arr, F, last);
        if (L > first)
            Qsort(arr, first, L);
    }
}
