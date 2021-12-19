#include <iostream>
#include <cstdlib>

//=============================================== односвязный список ==================================================
typedef struct Node{
    int dat = 0;
    struct Node *next;
}Node;

typedef struct Queue{
    int SZ = 0;
    struct Node *head;
    struct Node *tail;
}Queue;

void q_init(Queue *queue){
    queue->SZ = 0;
    queue->head = NULL;
    queue->tail = NULL;
}

void q_push(Queue *q, int data){
    Node *n = new Node;
    n->dat = data;
    if(q->SZ == 0) {
        q->head = n;
        q->tail = n;
        n->next = NULL;
        q->SZ++;
    }
    else {
        q->tail->next = n;
        q->tail = n;
        n->next = NULL;
        q->SZ++;
    }
}

void q_free(Queue *q){
    Node *itr = q->head;
    Node *temp;
    while(itr)
    {
        temp = itr;
        itr = itr->next;
        delete temp;
        q->SZ--;
    }
    q->head = NULL;
    q->tail = NULL;
} // очиста очереди

void q_print(Queue *q){
    printf("\n");
    Node *itr = q->head;
    while(itr->next){
        printf("%d ", itr->dat);
        itr = itr->next;
    }
    printf("%d ", itr->dat);
}

//============================================== ЗАДАНИЕ 1 =============================================================

int count(char *c){
    int x = 0;
    while(*c != 0){     // Списано из примера, который Вы показали на уроке, т.к. еще ни разу не видел такой
        x += (int) *c;  // вариант применения арифметики указателей и хочу сохранить его на будущее.
        ++c;            // В первоначальном решении использовал цикл фор и передавал в функцию размер массива чар
    }
    return x;
}

void task_1(){
    printf("\n%d", count("computer"));
    printf("\n%d\n", count("passowr1/"));
}

//============================================== ЗАДАНИЕ 2 =============================================================

void calc(int *cash, int sum){
    Queue *q = new Queue;
    q_init(q);
    while(*cash != NULL) {
        if(sum >= *cash) {
            sum -= *cash;
            q_push(q, *cash);
        }
        else if(sum < *cash)
            ++cash;
        else if(sum == 0)
            break;
    }

    q_print(q);
    q_free(q);
    delete q;
}

void task_2(){
    int cash[] = {50, 10, 5, 2, 1};
    int price = 73;
    int size = 5;
    printf("\nTo pay %d cents you'll need coins:", price);
    calc(cash, price);
}
//======================================================================================================================
int main() {
    task_1();
    task_2();
    return 0;
}
