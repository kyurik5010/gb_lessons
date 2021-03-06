#include <iostream>
#include <cstdlib>

#pragma pack(push, 1) //немного сэкономит память
typedef struct Node{
    int key;
    Node* left;
    Node* right;
}tree_node;
#pragma pack(pop)

tree_node* Tinsert(tree_node *t, int key){ //t это корень дерева, отправная точка для начала перебора
    tree_node *tn = new tree_node;
    tn -> key = key;
    tn -> left = NULL;
    tn -> right = NULL;
    tree_node* parent = t;
    tree_node* current = t;
    if(parent == NULL) {
        //printf("root - %d", tn->key);
        return tn;
    }
    else
    {
//        std::cout<<"\nroot exists";
        while(current->key != key) {
            if(current->key > key) {
//                std::cout<<"\nparent key > new key";
                parent = current;
//                std::cout<<"\nparent = current";
                current = parent->left;
//                std::cout<<"\ncurrent = parent->left";
                if (current == NULL) {
//                    std::cout<<"\ncurrent == NULL";
                    parent->left = tn;
//                    std::cout<<"\nparent->left = tn, tn->key = "<<parent->left->key;
                    current = tn;
//                    std::cout<<"\ncurrent->key = "<<current->key;
//                    printf("\nleaf - %d, parent - %d", tn->key,parent->key); // return tn;?
                }
            }
            else if(current->key < key){
//                std::cout<<"\nparent key < new key";
                parent = current;
                current = parent->right;
                if (current == NULL) {
//                    std::cout<<"\ncurrent == NULL";
                    parent->right = tn;
//                    std::cout<<"\nparent->right = tn, tn->key = "<<parent->right->key;
                    current = tn;
//                    std::cout<<"\ncurrent->key = "<<current->key;
//                    printf("\nleaf - %d, parent - %d", tn->key,parent->key); // return tn;?
                }
            }
        }
    }
    return tn;
}

void Tprint(tree_node *t){  // печать дерева, "#n" - лист
    tree_node *itr = t;
    if(itr != NULL)
    {
        std::cout<<itr->key;
        if(itr->right || itr->left)
        {
            std::cout << "(";
            if (itr->right)
                Tprint(itr->right);
            else
                std::cout<<"N";
            std::cout << ",";
            if (itr->left)
                Tprint(itr->left);
            else
                std::cout<<"N";
            std::cout<<")";
        }
        else
            std::cout<<"n";
    }
    else
        std::cout<<"N";
}

//================================================= Задание 1 ==========================================================

int node_counter(tree_node *t)  // счетчик узлов
{
    int nodes = 0;
    if(t)
    {
        if(t->right || t->left) {
            ++nodes;
            nodes += node_counter(t->right);
            nodes += node_counter(t->left);
        }
        else
            return nodes;
    }
    return nodes;
}

bool isBalanced(tree_node *t) // проверка баланса в деревьях
{
    int right = node_counter(t->right);
    int left = node_counter(t->left);
    //printf("\nright-%d, left-%d, sum-%d",right,left,right+left);
    if(right>left)
        return (right-left <= 2);
    else
        return (left-right <= 2);
}

tree_node* Tdelete(tree_node *t){  // освобождение памяти
    if(t)
    {
        delete Tdelete(t->right);
        delete Tdelete(t->left);
    }
    //std::cout<<"\n node "<<t->key<<" deleted";
    return t;
}
void tpass(tree_node *t){ //для дебага
    std::cout<<"\ntesting";
    std::cout<<"\nt->key = "<<t->key
             <<"\nt->right->key = "<<t->right->key
             <<"\nt->left->key = "<<t->left->key;
    tree_node *tree = t;
    std::cout<<"\nassigned to pointer *tree"
             <<"\ntree->key = "<<tree->key
             <<"\ntree->right->key = "<<tree->right->key
             <<"\ntree->left->key = "<<tree->left->key;
    std::cout<<"\ntesting NULL ...";
    if(t)
        std::cout<<"\nt != NULL";
    if(tree)
        std::cout<<"\ntree != NULL";
    if(t->right)
        std::cout<<"\nt-right != NULL";
    if(t->left)
        std::cout<<"\nt-left != NULL";
    if(tree->right)
        std::cout<<"\ntree-right != NULL";
    if(tree->left)
        std::cout<<"\ntree-left != NULL";
    std::cout<<"\ngoing tree->right";
    tree = tree->right;
    std::cout<<"\ngoing tree->right";
    tree = tree->right;
    std::cout<<"\ntesting tree->right";
//    if(tree->right == NULL) {  //                      (interrupted by signal 11: SIGSEGV)
//        std::cout << "\ntree->right == NULL";
//    }
}

double task_1(){
    double count = 0;
    tree_node *ntree;
    for (int i = 0; i < 50; ++i) {
        ntree = Tinsert(NULL, rand()% 98+1);
        for (int j = 0; j < 10000; ++j) {
            Tinsert(ntree, rand()% 98+1);
        }
        //std::cout<<"tree nr."<<i+1<<" created, root-"<<ntree->key<<"\n";
        count += (isBalanced(ntree))? 1 : 0;
        delete Tdelete(ntree);
        ntree = NULL;
    }
    return count/0.5;
}

//================================================= Задание 2 ==========================================================

int Tsearch(tree_node *t, int item){
    tree_node *itr = t;
    while(itr) {
        if(itr->key != item)
            itr = (itr->key > item) ? itr->left : itr->right;
        else
            return item;
    }
    return 0;
}

void task_2(){
    int key, item;
    int max = 20;
    tree_node *tree = Tinsert(NULL, rand()% 98+1);
    for (int i = 0; i < max; ++i) {
        Tinsert(tree, rand()% 98+1);
        if(i==max-1) {
            key = rand() % 98 + 1;
            Tinsert(tree, key);
        }
    }
    Tprint(tree);
    item = rand()% 98+1;
    std::cout << "\nsearching item "<<item;
    if(Tsearch(tree,item))
        std::cout << "\nitem was found - " << item;
    else
        std::cout << "\nitem "<<item<<" was not found";
    delete Tdelete(tree);
}

int main() {
    srand(time(0));
    std::cout<<"\n"<<task_1()<<"% from 50 trees were balanced\n\n";
    task_2();
// прошу подсказать правильно ли у меня организовано удаление деревьев Tdelete()
    return 0;
}
