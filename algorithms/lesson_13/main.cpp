#include <iostream>
#include <cstdlib>

typedef struct Node{
    int dat = 0;
    int meta1 = 0;
    int meta2 = 0;
    struct Node *next;
}Node;

typedef struct Stack{
    int SZ = 0;
    struct Node *tail;
}Stack;

typedef struct Queue{
    int SZ = 0;
    struct Node *head;
    struct Node *tail;
}Queue;

//=========================================== ОБЩИЕ ФУНКЦИИ ============================================================

void q_init(Queue *queue){
    queue->SZ = 0;
    queue->head = NULL;
    queue->tail = NULL;
}

void stack_init(Stack *stack){
    stack->SZ = 0;
    stack->tail = NULL;
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

void stack_push(Stack *stack, int data){
    Node *n = new Node;
    n->dat = data;
    if(stack->SZ == 0) {
        stack->tail = n;
        stack->SZ++;
        n->next = NULL;
    }
    else {
        n->next = stack->tail;
        stack->tail = n;
        stack->SZ++;
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

void stack_pop(Stack *stack){
    Node *temp = stack->tail;
    stack->tail = stack->tail->next;
    stack->SZ--;
    delete temp;
}

void q_print(Queue *q){
    printf("\n");
    Node *itr = q->head;
    while(itr->next){
        printf("%d ", itr->dat);
        itr = itr->next;
    }
    printf("%d ", itr->dat);
} // простой вывод очереди

void stack_print(Stack *stack){
    printf("\n");
    Node *itr = stack->tail;
    while(itr->next) {
        printf("%d ", itr->dat);
        itr = itr->next;
    }
    printf("%d ", itr->dat);
} // вывод значений стека

bool stack_check(Stack *s, int data){
    Node *itr = s->tail;
    while(itr)
    {
        if(itr->dat == data)
            return 1;
        else
            itr = itr->next;
    }
    return 0;
} // проверка стека на повторы

bool q_check(Queue *q, int data){
    Node *itr = q->head;
    while(itr)
    {
        if(itr->dat == data)
            return 1;
        else
            itr = itr->next;
    }
    return 0;
} // проверка очереди на повторы

int* initarr(int size, char c[]){
    int *par = new int [size];
    for (int i = 0; i < size; ++i) {
        par[i] = c[i] - '0'; //перевод символов чар в инт
    }
    return par;
} // заполнение строк матрицы

//=========================================== ЗАДАНИЕ 1 ===============================================================

void dtrav(int **matrix, Queue *q, Stack *s, int size){
    int start = s->tail->dat;
    if(s->tail)
        stack_pop(s);                                      // удаление из стека текущей точки
    q_push(q, start);

    for (int i = 0; i < size; ++i) {
        if(matrix[start][i])
            if(!q_check(q, i) && !stack_check(s, i))  // проверка на пройденные точки и на наличие
                stack_push(s, i);                    // записей в стеке
    }
    if(s->SZ != 0) {
        dtrav(matrix, q, s, size);                               // продолжить
    }
    else {
        printf("\nTraverse complete");
        q_print(q);
    }
} // обход графа

void task_1(){ printf("\nЗадание 1\n");
    Stack *stack = new Stack;
    stack_init(stack);
    const int n = 6;                              //размер матрицы
    Queue *queue = new Queue;
    q_init(queue);
    int **matrix = new int* [n];
    matrix[0] = initarr(n, "011000");
    matrix[1] = initarr(n, "000111");
    matrix[2] = initarr(n, "000001");
    matrix[3] = initarr(n, "100000");
    matrix[4] = initarr(n, "000000");
    matrix[5] = initarr(n, "000010");
    for (int i = 0; i < n; ++i) {                 //вывод матрицы
        for (int j = 0; j < n; ++j) {
            std::cout<<matrix[i][j]<<" ";
        }
        printf(" <\n");
    }
    int start = 1;
    stack_push(stack, start);               //начальная точка
    printf("\nStarting traverse from point %d", stack->tail->dat);
    dtrav(matrix, queue, stack, n);

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
        matrix[i] = NULL;
    }
    delete[] matrix;
    matrix = NULL;

    q_free(queue);                            //очистка стека и очереди для следующего задания
    stack->tail = NULL;

}

//=========================================== ЗАДАНИЕ 2 ===============================================================

int nbr_check(int **matrix, Node *n, int point, int size){
    int nbr = 0;
    Node *itr = n;
    for (int i = 0; i < size; ++i) {
        if (matrix[point][i] != 0 && point != i)
            nbr++;
    }
    if(itr->next)
        itr->next->meta2 = nbr_check(matrix, itr->next, itr->next->dat, size);
    return nbr;
} // счетчик соседей

void meta_print(Queue *q){
    Node *itr = q->head;
    int HRun = 0;
    while(itr){     //поиск максимального значения переменной meta2
        if(itr->meta1 > HRun)
            HRun++;
        itr = itr->next;
    }
    itr = q->head;
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"); // вывод точек графа в порядке уменьшения степени полузахода
    for ( ; HRun >= 1; --HRun) {
        while(itr){
            if(itr->meta1 == HRun)
                printf("\nvertex %d | half run %d | neighbours %d", itr->dat, itr->meta1, itr->meta2);
            itr = itr->next;
        }
        itr = q->head;
    }
}

void dtrav_count(int **matrix, Stack *s, Queue *q, int size){
    int start = s->tail->dat;
    int nbr = 0;                                                 // счетчик соседей
    int edg = 0;                                                 // счетчик ребер
    if(s->tail)
        stack_pop(s);                                      // удаление из стека текущей точки
    q_push(q, start);
    for (int i = 0; i < size; ++i) {
        if(matrix[start][i] != 0) {
            if (!q_check(q, i) && !stack_check(s, i)) {
                stack_push(s, i);
            }                                                     // полузахода равна степени
            edg++;                                                // с учетом того, что связи циклические, степень
        }
    }
    q->tail->meta1 = edg;                                         // запись степени полузахода
    if(s->SZ != 0) {
        dtrav_count(matrix, s, q, size);
    }
    else {
        printf("\nTraverse complete");
        q->head->meta2 = nbr_check(matrix, q->head, q->head->dat, size);// подсчет соседей
        q_print(q);
        meta_print(q);
    }
} // обход с подсчетом

void task_2(){ printf("\n\nЗадание 2\n");
    Stack *s = new Stack;
    stack_init(s);
    Queue *q = new Queue;
    q_init(q);
    const int n = 8;                              //размер матрицы
    int **matrix = new int* [n];
    matrix[0] = initarr(n, "00001001");
    matrix[1] = initarr(n, "01001000");   //ссылается на себя
    matrix[2] = initarr(n, "00011100");
    matrix[3] = initarr(n, "00100000");
    matrix[4] = initarr(n, "11100000");
    matrix[5] = initarr(n, "00100011");
    matrix[6] = initarr(n, "00000110");   //ссылается на себя
    matrix[7] = initarr(n, "10000100");
    for (int i = 0; i < n; ++i) {                 //вывод матрицы
        for (int j = 0; j < n; ++j) {
            std::cout<<matrix[i][j]<<" ";
        }
        printf(" <\n");
    }
    int start = 0;
    stack_push(s, start);              //начальная точка
    printf("\nStarting traverse from point %d", s->tail->dat);
    dtrav_count(matrix, s, q, n);
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
        matrix[i] = NULL;
    }
    delete[] matrix;
    matrix = NULL;

    q_free(q);
    delete q;
    s->tail = NULL;
}

int main() {
    task_1();
    task_2();
    return 0;
}
