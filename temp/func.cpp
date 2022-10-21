#include <iostream>
#include <locale>
#include <math.h>


int main(){

    int a = 0;
    int b = 1;
    int c = 2;

    double d = pow(b, 2) - (4*a*c);

    double res1, res2;
//
//    if (a == 0)
//    {
//        if (b != 0)
//            std::cout << "a = 0; уравнение вырождается в линейное:\n"
//                      << "x = " << -1.*c/b << std::endl;
//        else if (c == 0)
//            std::cout << "Все коэффициенты равны нулю; x - любое число." << std::endl;
//        else
//            std::cout << "Нет решений." << std::endl;
//    }
//    else
//    {
//        if(d > 0)
//        {
//            std::cout << "два корня: ";
//            res1 = ((-b + sqrt(d)) / (2 * a));
//            res2 = ((-b - sqrt(d)) / (2 * a));
//            std::cout << res1 << " и " << res2 << std::endl;
//        }
//        else if(d < 0)
//        {
//            std::cout << "Корней нет";
//        }
//        else
//        {
//            std::cout << "Корень: " << (-b / (a * 2));
//        }
//    }
//


    std::cout << -1. * 5 / 2;
    return 0;
}