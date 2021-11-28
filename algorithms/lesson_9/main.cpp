#include <iostream>
#include <cstdlib>
#define SIZE 10

typedef struct{
    int pr;
    int dt;
}Node;

int head;
int tail;
int count;

Node *arr[SIZE];
//============================================= Задание 1 ==============================================================
void init(){
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = NULL;
    }
    head = 0;
    tail = 0;
    count = 0;
}

void put(int priority, int data){
    Node *nd = new Node; //выделение памяти под новый элемент
    nd -> dt = data;
    nd -> pr = priority;
    if (count<SIZE)
    {
        int idx=0;
        for (int i = head; i <= tail; ++i)
        {
            idx = i%SIZE;
            if(arr[idx] == NULL) {
                break;
            }
        }
        arr[idx] = nd;
        tail++;
        count++;
    }
    else{
        std::cout << "\nОчередь переполнена";
        return;}
}

void push(){  // вывод элементов очереди по приоритету
    int idx;
    int tmp = 10;
    int position;
    for (int i = head; i < SIZE; ++i) {
        idx = i;
        if(arr[idx] == NULL)
            continue;
        else
            if((arr[idx]->pr) < tmp)
            {
                position = idx;
                tmp = arr[idx]->pr;
            }
    }
    std::cout << "\n[" << arr[position]->pr<<"-"<<arr[position]->dt<<"] - OUT";
    arr[position] = NULL;
    count--;
}

void printQ(){
    printf("\n[");
    for (int i = 0; i < SIZE; ++i) {
        if(arr[i] != NULL)
            printf(" [%d-%d]",arr[i]->pr,arr[i]->dt);
        else
            printf(" [NULL]");
    }
    printf(" ]");
}

void task_1(){
    init();
    std::cout<<"\ninit complete";
    put(6,6);
    put(5,5);
    put(9,9);
    put(7,7);
    put(2,2);
    put(3,3);
    put(6,62);
    std::cout<<"\nВ очереди "<<count<<" элементов";
    printQ();
    push();
    push();
    push();
    printQ();
    std::cout<<"\nВ очереди "<<count<<" элементов";
    put(1,1);
    put(2,2);
    put(3,3);
    printQ();
    std::cout<<"\nВ очереди "<<count<<" элементов";
    push();
    push();
    printQ();
    std::cout<<"\nВ очереди "<<count<<" элементов";
}
//============================================= Задание 2 ==============================================================
int digits = 20;
int Stack[20];
int coursor = -1;
void push_back(int x)
{
    if(coursor < 20)
    {
        Stack[++coursor] = x;
        return;
    }
    else
        std::cout<<"Stack overflow";
}
void pop()
{
    if(coursor>0)
        std::cout<<Stack[coursor--];
    else
        std::cout << "Stack is empty";

//    for (int i = coursor; i > 0 ; --i) {
//        std::cout<<Stack[]
//    }
}
//int x, i;
//int result[100];
//printf("Provide an integer please ");
//scanf("%i", &x);
//for(i=0;x>=1;i++){
//  result[i] = x % 2;

//  else if(x==1)
//      result[i] = 1;
//  x /= 2;

//int temp;
//if(x==0 || x==1) {
//    printf("%d", x);
//    return 0; }
//temp = x%2;
//binary(x/2);
//printf("%d", temp);

int binary(int x){
    while(x>1) {
        push_back(x % 2);
        binary(x/=2);
    }
    for (int i = 0; i < coursor; ++i) {
        pop();
    }
    return 0;
}

//======================================================================================================================
int main() {
    /** Задание 1 */
//    task_1();

    /** Задание 2 */
    binary(237);
    return 0;
}
