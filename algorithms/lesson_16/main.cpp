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

void Mix_encrypt(char *w, int columns) {

    int size = 0;
    while (*w) {
        ++size;
        ++w;
    }
    w -= size; // вернуть указатель на место

    ++columns; // обеспечить запас пространства

    char **table = new char *[columns];
    for (int i = 0; i < columns; ++i)
        table[i] = new char[columns];

    printf("\n");
    for (int r = 0; r < columns; ++r) {
        for (int l = 0; l < columns; ++l) {
            if (*w) {
                table[r][l] = *w;
                ++w;
            } else
                table[r][l] = '_';
        }
    }


    std::cout << "\nThe matrix:\n";
    for (int r = 0; r < columns; ++r) {
        for (int l = 0; l < columns; ++l) {
            printf("%c ", table[r][l]);
        }
        printf("\n");
    }

    for (int r = 0; r < columns; ++r) { // смещение столбцов
        for (int l = 0; l < columns; l += 2) {
            if(table[r][l+1] == '_')
                continue;
            char temp = table[r][l];
            table[r][l] = table[r][l + 1];
            table[r][l + 1] = temp;
        }
    }
    std::cout << "\nThe matrix_2:\n";
    for (int r = 0; r < columns; ++r) {
        for (int l = 0; l < columns; ++l) {
            printf("%c ", table[r][l]);
        }
        printf("\n");
    }

    for (int r = 0; r < columns; r+=2) { // смещение строк
        for (int l = 0; l < columns; ++l) {
            if(table[r+1][l] == '_')
                continue;
            char temp = table[r][l];
            table[r][l] = table[r+1][l];
            table[r+1][l] = temp;
        }
    }
    std::cout<<"\nThe matrix_3:\n";
    for (int r = 0; r < columns; ++r) {
        for (int l = 0; l < columns; ++l) {
            printf("%c ",table[r][l]);
        }
        printf("\n");
    }

    for (int r = 0; r < columns; ++r) {  // запись в обратном порядке и возвращение указателя на место
        for (int l = 0; l < columns; ++l) {
            if (table[r][l] != '_') {
                *w = table[r][l];
                --w;
            }
        }
        delete[] table[r]; // параллельно освобождаю память
    }
    delete[] table;
}

void Mix_decrypt(char *c, int columns){
    //померить размер массива
    //выделить массив с запасом
    //записать в обратном порядке и вернуть указатель на место
    //сместить строки
    //сместить столбцы
    //записать значения в оригинальный массив в прямом порядке
    //освободить память
}

void task_2(){
    printf("\n\nЗадание_2");
    char w[] = "This is some random phrase";
    printf("\nOriginal phrase - ");
    fputs(w, stdout);
    int size = sizeof(w)/sizeof(w[0]) - 1; // минус терминант
    int columns = (int) sqrt(size/1);

    Mix_encrypt(w,columns);
    printf("\nEncrypted phrase - ");
    fputs(w, stdout);

    // дешифровку организовать еще не успел :(
}

int main() {
    //task_1();
    task_2();
    return 0;
}
