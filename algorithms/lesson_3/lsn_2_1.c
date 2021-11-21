#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hand_test();
void auto_test();

int main() {
    char choice;
    srand((unsigned) time(NULL) / 3);
    printf("Тестировать автоматически? (y/n) ");
    fflush(stdout);

    do {
        fflush(stdout);
        scanf("%c", &choice);
    }while(choice != 'n' && choice != 'y');

    switch(choice) {
        case 'y' :
            auto_test();
            break;
        case 'n' :
            hand_test();
            break;
    }
    return 0;
}

void auto_test(){
    int *ptr;
    ptr = (int*) calloc(10, sizeof(int));
    for(int i=0;i<10;++i)
    {
        ptr[i] = rand() % 100;
        //printf("%d ",ptr[i]);
    }
    for(int i=0;i<10;++i)
    {
        int dividers = 0;
        for(int k=1;k<=ptr[i];++k)
        {
            if( !(ptr[i]%k) )
            {
                dividers += 1;
                if(dividers>2)
                {
                    printf("\n%d сложное число", ptr[i]);
                    break;
                }
                if( k==ptr[i] && dividers<=2 )
                    printf("\n%d простое число <", ptr[i]);
            }
        }
    }
    free(ptr);
}

void hand_test(){

    printf("введите через пробел любое количество цифр\nв конце поставьте любую букву\n");
    fflush(stdout);
    int x, dividers;
    while(scanf("%d", &x))
    {
        dividers = 0;
        for(int i=1;i<=x;++i)
        {
            if(!(x%i)){
                dividers += 1;
                if(dividers>2)
                {
                    printf("%d сложное число\n", x);
                    break;
                }
                if( i==x && dividers<=2 )
                    printf("%d простое число <\n", x);
            }
        }
    }
}