# include <stdio.h>

int recBinary(int);
int recPower(int, int);

int main(){
    //задание 1
    int x, *bptr = &x;
    printf("\nЗадание 1:\nВведите число: ");
    fflush(stdout);
    scanf("%d", &x);
    recBinary(*bptr);

    //задание 2
    int num=0, power=0, *Nptr = &num, *Pptr = &power;
    printf("\n\nЗадание 2:\nВведите число и степень: ");
    fflush(stdout);
    scanf("%d%d", &num, &power);
    printf("\n%d", recPower(*Nptr, *Pptr));
    printf("\n%d", num);

    //задание

    return 0;
}

int recBinary(int x) // задание 1
{
    int temp;
    if(x==0 || x==1) {
        printf("%d", x);
        return 0; }
    temp = x%2;
    recBinary(x/2);
    printf("%d", temp);
    return 0;
}


int recPower(int num, int power) // задание 2
{
    int k = 0;
    if(power == 1)
        return num;
    k = num * recPower(num, power - 1);
    num = k;
    return num;
}