#include <iostream>
#include <cstdlib>

typedef struct Node{
    char par;
    int dat;
    struct Node *next;
} Node;



//=============================================== задание 1 ============================================================

typedef struct Stack{
    Node *head;
    int size;
} stack;

void init(Stack *stack){
    stack->head = NULL;
    stack->size = 0;
}

void push(Stack *stack, char par)
{
    Node *node = new(std::nothrow) Node;
    node->par = par;
    node->next = stack->head;
    stack->head = node;
    stack->size++;
}

char pop(Stack*stack){
    if(stack->size==0)
    {
        std::cout<<"\nStack is empty";
        return -1; // it should return -1 (to avoid intersecting with any data)
    }
    Node *tmp = stack->head; //temp storage for pointer to head element
    char data = stack->head->par; //storage for par data of the current head element
    stack->head = stack->head->next;
    delete tmp;
    stack->size--;
    return data; // can be used as "std::cout<<pop();" it prints out data and pops the head element
}

void printOLCN(Node *n){
    if(n == NULL) {
        std::cout << " []";
        return;
    }
    std::cout<<" ["<<n->par<<"]";
}

void printOLCS(Stack *stack){
    printf("\n");
    Node *current = stack->head;
    if (current == NULL)
        printOLCN(current);
    else
    {
        do{
            printOLCN(current);
            current = current->next;
        }while(current != NULL);
    }
    std::cout<<"\nStack size = "<<stack->size;
}

void parcheck(Stack *stack,char *x){
    printf("\n         -  -  -          ");
    int i=0;
    while(x[i] != '\0')
    {
        switch(x[i]) {
            case '(' :
                push(stack,x[i]);
                break;
            case '{' :
                push(stack,x[i]);
                break;
            case '[' :
                push(stack,x[i]);
                break;
            case ')' :
                if(stack->head->par != '(') {
                    std::cout << "\nошибка последовательности - " << x[i];
                }
                pop(stack);
                break;
            case '}' :
                if(stack->head->par != '{') {
                    std::cout << "\nошибка последовательности - " << x[i];
                }
                pop(stack);
                break;
            case ']' :
                if(stack->head->par != '[') {
                    std::cout << "\nошибка последовательности - " << x[i];
                }
                pop(stack);
                break;
            default :
                break;
        }
        ++i;
    }
    if(stack->size > 0) {
        printf("\nлишняя открывающая скобка - ");
        Node *itr = stack->head;
        while (itr != NULL)
        {
            printf("%c ", itr->par);
            itr = itr->next;
            pop(stack);
        }
    }
}

void task_1(){
    printf("\n========================== Задание 1");
    Stack *stack = new Stack;
    init(stack);
    char x[] = "(((((}";
    parcheck(stack, x);
    char y[] = "{({}[]";
    parcheck(stack, y);
    char z[] = "(){}[]";
    parcheck(stack, z);
    char d[] = "(2+2){3/3}[4*5]";
    parcheck(stack, d);
}
//=================================================== Задание 2 ========================================================

typedef struct Queue{
    Node *head;
    Node *tail;
    int size;
} Queue;

void Qinit(Queue *queue){
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

void push(Queue *queue, int data){
    Node *node = new Node;
    if (queue->size == 0) {
        queue->head = node;
        queue->tail = node;
        node->next = NULL;
        node->dat = data;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
        node->next = NULL;
        node->dat = data;
    }
    queue->size++;
}

void Qprint(Queue *first){
    Node *itr = first->head;; //= new Node;
    printf("\n");
    do{
        printf(" %d", itr->dat);
        itr = itr->next;
    }while(itr->next != NULL);
    printf(" %d", itr->dat);
}

void Qcopy(Queue *first , Queue *second)
{
    Qinit(second);
    Node *itr = first->head;
    do{
        push(second, itr->dat);
        itr = itr->next;
    }while(itr->next != NULL);
    push(second, itr->dat);
    Qprint(second);
}

void task_2(){
    printf("\n========================== Задание 2");
    Queue *fq = new Queue;
    Qinit(fq);
    push(fq, 1);
    push(fq, 2);
    push(fq, 3);
    push(fq, 4);
    push(fq, 5);
    Qprint(fq);
    printf("\n fq size - %d", fq->size);
    Queue *nq = new Queue;
    Qcopy(fq, nq);
    printf("\n nq size - %d", nq->size);
}
//=================================================== Задание 3 ========================================================

void Qcheck(Queue *q)
{
    Node *itr = q->head;
    int tmp;
    do
    {
        tmp = itr->dat;
        itr = itr->next;
        if(tmp > itr->dat)
        {
            printf("\nОчередь не отсортирована");
            return;
        }
    }while(itr->next != NULL);
    printf("\nОчередь отсортирована");
}

void task_3(){
    printf("\n\n========================== Задание 3");
    Queue *sorted = new Queue;
    Qinit(sorted);
    push(sorted, 1);
    push(sorted, 2);
    push(sorted, 3);
    push(sorted, 4);
    push(sorted, 5);
    Queue *not_sorted = new Queue;
    Qinit(not_sorted);
    push(not_sorted, 1);
    push(not_sorted, 2);
    push(not_sorted, 3);
    push(not_sorted, 4);
    push(not_sorted, 1);
    
    Qprint(sorted);
    Qcheck(sorted);
    Qprint(not_sorted);
    Qcheck(not_sorted);
}

int main() {
    task_1();
    task_2();
    task_3();

    return 0;
}
