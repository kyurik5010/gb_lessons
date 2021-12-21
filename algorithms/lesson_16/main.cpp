#include <iostream>
#include <cstdlib>
#include <cmath>

//=================================================  ЗАДАНИЕ 1 =========================================================
void Cesar_encrypt(char *c, int key){
    while(*c != 0){
        *c -= key;
        ++c;
    }
}

void Cesar_decrypt(char *c, int key){
    while(*c != 0){
        *c += key;
        ++c;
    }
}

void task_1(){
    char c[] = "password";
    printf("Задание_1 \nOriginal word  - %s",c);
    int key = 12;
    Cesar_encrypt(c,key); // шифрование
    printf("\nEncripted word - %s",c);
    Cesar_decrypt(c,key); // дешифровка
    printf("\nDecripted word - %s",c);

}
//=================================================  ЗАДАНИЕ 2 =========================================================

void Mix_encrypt(char *c, int columns){
    char **table = new char *[columns];
    for (int i = 0; i < columns; ++i)
        table[i] = new char [columns];
    int size = 0;
    while(*c){
        ++size;
        ++c;
    }
    int i = 1, k = 0, j = 0;
    while(i<=columns*columns)
    {
        if(i%columns == 0 && k < columns) {
            ++k;
            j = 0;
        }
        else
            break;
        if(*c == 0) {
            table[k][j] = '_';
            ++j;
            ++i;
            continue;
        }
        table[k][j] = c[i-1];
        ++i;
        ++j;
    }
    std::cout<<"\nThe matrix:\n";
    for (int r = 0; r < columns; ++r) {
        for (int l = 0; l < columns; ++l) {
            printf("%c",table[r][l]);
        }

    }
}

void Mix_decrypt(char *c, int columns){

}

void task_2(){
    printf("\n\nЗадание_2");
    char c[] = "This is some random phrase";
    printf("\nOriginal phrase - ");
    fputs(c, stdout);
    fflush(stdout); // just in case
    int size = sizeof(c)/sizeof(c[0]) - 1; // минус терминант
    double temp = sqrt(size/1);
    int columns;
    if(temp - (int) temp != 0)
        columns = (int) temp+1; // для квадратного массива
    else
        columns = (int) temp;
    printf("\nsize - %d, columns - %d", size, columns);
    //printf("\n%f", sqrt(size/1) - (int)sqrt(size/1));
    Mix_encrypt(c,columns);
    // не успел :(
}

int main() {
    task_1();
    task_2();
    return 0;
}
