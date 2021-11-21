# include <stdio.h>

int recBinary(int);
int recPower(int, int);
int recPow_2(int, int);

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

    //задание 2.2
    printf("\n\nЗадание 2.2:\nВведите число и степень: ");
    fflush(stdout);
    scanf("%d%d", &num, &power);
    printf("\n%d", recPow_2(*Nptr, *Pptr));
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
    if(power == 1)
        return num;
    return num * recPower(num, power - 1);
}

int recPow_2(int num, int pow)  // задание 2.2
{
    if(pow == 1)
        return num;
    if(!(pow%2))
        return recPow_2(num*num, pow/2);
    else
        return num * recPow_2(num, pow - 1);
}