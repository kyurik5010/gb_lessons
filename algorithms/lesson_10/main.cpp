#include <iostream>
#include <cstdlib>

typedef struct Node{
    char par;
    struct Node *next;
} Node;

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

char pop(Stack*stack, char par){
    if(stack->size==0)
    {
        std::cout<<"\nStack is empty";
        return -1; // it should return -1 (to avoid intersecting with any data)
    }
    Node *tmp = stack->head; //temp storage for pointer to head element
    char data = stack->head->par; //storage for par data of the current head element
    stack->head = stack->head->next;
    delete tmp; //avoiding memory leaks
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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
