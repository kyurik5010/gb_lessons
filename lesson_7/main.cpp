#include "mylib.h"
#include <string>
#include <fstream>

#define SIZE 6
#define cHK(a, b) ((a < b && a >= 0) ? "true" : "false")
#define SwapINT(a, b) (a += b, b = a - b, a -= b)

using namespace msp; // для задания 1/5


//==== task_2 ==========================================================================================================

void task_2(){
    int x;
    int y = 10;
    std::cout << "Check a number: ";
    std::cin >> x;
    std::cout << cHK(x, y) << "\n\ntask_3\n\n";
}

//==== task_3 ==========================================================================================================

void task_3(){
    int arr[SIZE];
    for(int i=0;i<SIZE;i++){
        std::cout << "element " << i+1 << " of " << SIZE << ": ";
        std::cin >> arr[i];
    }
    std::cout << "\noriginal array :"; // вывод заданного массива
    for(int i=0;i<SIZE;i++)
        std::cout << arr[i] << ", ";

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE-1;j++) {
            int x = arr[j];
            int y = arr[j + 1];
            if (x > y) {
                SwapINT(x, y); //(x += y, y = x-y, x -= y)
                arr[j] = x;
                arr[j+1] = y;
            }
        }
    }
    std::cout << "\n  sorted array :"; // вывод отсортированного массива
    for(int i=0;i<SIZE;i++)
        std::cout << arr[i] << ", ";
}

//==== task_4 ==========================================================================================================

#pragma pack(push, 1)
struct Employee {
    std::string name;
    int age;
    float salary;
};
#pragma pack(pop)

int main(){
    //task_1 - task_5
    float arr[SIZE];
    init(arr, SIZE);
    printarr(arr, SIZE);
    int x = checksum(arr, SIZE);
    std::cout << "\npositive - " << x << "\nnegative - " << SIZE - x << "\n\n";
    using namespace std;

    task_2();
    task_3();
//    task_4

    Employee *pEmp = new (std::nothrow) Employee;
    pEmp -> name = "JohnSina";
    pEmp -> age = 50;
    pEmp -> salary = 500.51;

    ofstream file("sina.txt");

    if(file.is_open()) {
        std::cout << "\n\nfile created\n";
        file << "name - " << pEmp->name << std::endl;
        std::cout << "name - " << pEmp->name << std::endl;
        file << "age - " << pEmp->age << std::endl;
        std::cout << "age - " << pEmp->age << std::endl;
        file << "salary - " << pEmp->salary << std::endl;
        std::cout << "salary - " << pEmp->salary << std::endl;
    }
    else
        std::cout << "\n\nbad file\n";

    delete pEmp;
    file.close();
    if(!file.is_open())
        std::cout << "\nfile closed\n";

    return 0;

}