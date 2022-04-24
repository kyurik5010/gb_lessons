#include <iostream>
#include <list>
#include <vector>
#include <cmath>

//TASK_1__________________________________________________________________________________________________________TASK_1

void AddMean(std::list<double> &lst){
    double m = 0;
    int count = 0;
    for (auto i: lst) {
        m += i;
        ++count;
    }
    lst.emplace_back(m/count);
}

//TASK_2__________________________________________________________________________________________________________TASK_2

std::vector<std::vector<int>> GetMinor(int x, std::vector<std::vector<int>> Arr){ // получение дополнительного минора
    int NewSize = Arr.size()-1;
    std::vector<std::vector<int>> Minor;
    for(int i = 0; i < NewSize; ++i) {
        Minor.emplace_back(NewSize);
    }

    for(int i = 1; i < Arr.size(); ++i) {
        for (int j = 0, k = 0; j <= NewSize; ++j, ++k){
            if(j != x)
                Minor[i-1][k] = Arr[i][j];
            else {
                --k;
                continue;
            }
        }
    }
    //std::cout << "GM: matrice size: " << Minor.size() << std::endl;
    return Minor;
}

int ComputeDeterminant(std::vector<std::vector<int>> a){ //получение определителя
    int Determinant = 0;
    if(a.size() == 3)
        Determinant =
                (a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[0][2] * a[1][0] * a[2][1])
                -
                (a[0][2] * a[1][1] * a[2][0] + a[0][1] * a[1][0] * a[2][2] + a[0][0] * a[1][2] * a[2][1]);
    else if (a.size() == 2 && a[0].size() == 2)
        Determinant = a[0][0] * a[1][1] - a[0][1] * a[1][0];
    else if (a.size() == 1 && a[0].size() == 1)
        Determinant = a[0][0];
    else
        std::cout << "\nCD: Incompatible matrice size";
    //std::cout << "CD: Det: " << Determinant << std::endl;
    return Determinant;
}

int ComputeMatrice(std::vector<std::vector<int>> Arr){//основная функция
    int Determinant = 0;
    if(Arr.size() <= 3) {
        Determinant = ComputeDeterminant(Arr);
    }
    else {
        for (int i = 0; i < Arr.size(); ++i) { //теорема лапласа и рекурсия
            Determinant += Arr[0][i] * (ComputeMatrice(GetMinor(i, Arr))) * pow(-1,(2 + i));
        }
    }
    return Determinant;
}

//TASK_3__________________________________________________________________________________________________________TASK_3
class range{
    std::list<int> lst;
    int _t1;
    int _t2;
public:
    range(int first, int last) : _t1(first), _t2(last) {
        for(int i = _t1; i < _t2; ++i)
            lst.push_back(i);
    }
    auto begin() { return lst.begin(); }
    auto end() { return lst.end(); }
    int& operator++ (int t) { return ++t; }
    int& operator* (int* t) { return *t; }
};

//MAIN______________________________________________________________________________________________________________MAIN
int main() {
    std::cout << "Task_1\n";
    std::list<double> lst {13.7};
    for(int i=0; i<20; ++i)
        AddMean(lst);
    for(auto i: lst)
        std::cout << i << " ";
    std::cout << std::endl;
//____________________________________________________________________________
    std::cout << "\nTask_2";
    std::vector<std::vector<int>> Arr = {{ 1, 7, 1, 6, 8},
                                         { 5, 3, 7, 1, 5},
                                         { 3, 8, 1, 2, 0},
                                         { 7, 4, 6, 1, 2},
                                         { 1, 9, 4, 7, 5}};

    std::cout << "\nDeterminant: " << ComputeMatrice(Arr); //обсчитывает только квадратные матрицы

//____________________________________________________________________________
    std::cout << "\n\nTask_3\n";

    for(int i: range{2, 12})
        std::cout << i << " ";

    return 0;
}
