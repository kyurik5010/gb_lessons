#include "mylib.h"
#include <string>
#include <fstream>
#define SIZE 6
#define cHK(a, b) ((a < b && a >= 0) ? "true" : "false")
#define SwapINT(a, b) (a += b, b = a - b, a -= b)
using namespace msp;

//=====================================================================================================================
//Описать макрокоманду (через директиву define), проверяющую, входит ли переданное ей число (введенное с
//клавиатуры) в диапазон от нуля (включительно) до переданного ей второго аргумента (исключительно) и возвращает
// true или false, вывести на экран «true» или «false».
//=====================================================================================================================

void task_2(){
    int x;
    int y = 10;
    std::cin >> x;
    std::cout << cHK(x, y) << "\n\ntask_3\n\n";
}
//=====================================================================================================================
//3. Задайте массив типа int. Пусть его размер задается через директиву препроцессора #define. Инициализируйте его через
//ввод с клавиатуры. Напишите для него свою функцию сортировки (например Пузырьком). Реализуйте перестановку
//элементов как макрокоманду SwapINT(a, b). Вызывайте ее из цикла сортировки.
//=====================================================================================================================

void task_3(){
    int arr[SIZE];
    for(int i=0;i<SIZE;i++){
        std::cout << "element " << i+1 << " of " << SIZE << ": ";
        std::cin >> arr[i];
    }
//    std::cout << "\noriginal array :"; // вывод заданного массива
//    for(int i=0;i<SIZE;i++)
//        std::cout << arr[i] << ", ";

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
//    std::cout << "\n  sorted array :"; // вывод отсортированного массива
//    for(int i=0;i<SIZE;i++)
//        std::cout << arr[i] << ", ";
}
//=====================================================================================================================
//4. * Объявить структуру Сотрудник с различными полями. Сделайте для нее побайтовое выравнивание с помощью
//директивы pragma pack. Выделите динамически переменную этого типа. Инициализируйте ее. Выведите ее на экран и ее
//размер с помощью sizeof. Сохраните эту структуру в текстовый файл.
//=====================================================================================================================

#pragma pack(push, 1)
struct Employee {
    string name;
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
    pEmp -> salary = 500,50;

    ofstream file("sina.txt");

    if(file.is_open()) {
        std::cout << "\n\nfile created";
        file << "name - " << pEmp->name << std::endl;
        file << "age - " << pEmp->age << std::endl;
        file << "salary - " << pEmp->salary << std::endl;
    }
    else
        std::cout << "\n\nbad file\n";

    delete pEmp;
    file.close();
    if(!file.is_open())
        std::cout << "\nfile closed\n";

    return 0;

}

