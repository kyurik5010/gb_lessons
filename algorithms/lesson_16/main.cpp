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
//    int line = (int) sqrt((double) size);
//    char **table = new char *[2];
//    for (int i = 0; i < 2; ++i) {
//        table[i] = new char [columns+1];
//    }
    int size = 0;
    while(*c != 0){
        ++size;
        ++c;
    }
    if (size % 2 != 0)
        
    int len = columns+1;
    char table[2][columns+1];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < columns+1; ++j) {
            table[i]
        }
    }


}

void Mix_decrypt(char *c, int columns){

}

void task_2(){
    printf("\n\nЗадание_2");
    char c[] = "Thisissomesentence";
    int size = sizeof(c)/sizeof(c[0]);
    int columns = size/2;
    printf("\nsize - %d, columns - %d", size, columns);

    // не успел :(
}

int main() {
    task_1();
    task_2();
    return 0;
}
