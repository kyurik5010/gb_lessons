#include <iostream>
#include <vector>
#include <deque>
#include <random>

//TASK_1__________________________________________________________________________________________________________TASK_1

void insert_sorted(int element, std::vector<int>& vector){
    std::vector<int> v {element};
    auto it = std::lower_bound(vector.begin(), vector.end(), element);
    if(it == vector.end())
    {
        std::cout << "\nNo viable position found;";
        return;
    }
    std::copy(v.begin(), v.end(), std::inserter(vector, it));
}

//TASK_1.2______________________________________________________________________________________________________TASK_1.2
template<typename T, typename _container>
void insert_sorted(T element, _container& cont) {
    _container v{element};
    auto it = std::lower_bound(cont.begin(), cont.end(), element);
    if (it == cont.end()) {
        std::cout << "\nNo viable position found;";
        return;
    }
    std::copy(v.begin(), v.end(), std::inserter(cont, it));
}
//TASK_2__________________________________________________________________________________________________________TASK_2

// сделал в main

//MAIN______________________________________________________________________________________________________________MAIN

int main() {
    std::vector<int> v1 { 1,2,3,4,5,7,8,9 };
    insert_sorted(6, v1);
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>{std::cout,", "});

    std::cout << std::endl;

    std::deque<double> v2 { 1.1,2.1,3.1,4.1,5.1,7.1,8.1,9.1 };
    insert_sorted(6.1, v2);
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<double>{std::cout,", "});

//TASK_2__________________________________________________________________________________________________________TASK_2

    std::cout << "\nTask_2\n";
    double signal{ 100 };
    int signal_length = 100;
    std::random_device rd;
    std::mt19937 gen{ rd() };
    std::normal_distribution<> d{ 2, 5 };

    std::cout << "\n   analogue:" << std::endl;
    std::vector<double> a;
    a.reserve(signal_length);
    generate_n(back_inserter(a), signal, [&] { return d(gen); });
    std::copy(a.begin(), a.end(), std::ostream_iterator<double>{std::cout, ", "});

    std::cout << "\n   digital:" << std::endl;
    std::vector<int> b;
    b.reserve(signal_length);
    std::copy(a.begin(), a.end(), std::back_inserter(b));
    std::copy(b.begin(), b.end(), std::ostream_iterator<int>{std::cout, ", "});


    std::vector<double> final;
    final.reserve(signal_length);
    std::cout << "\n";
    int i = 0;
    std::transform(a.begin(), a.end(), std::back_inserter(final), [&i, &b](double x){
        return pow(static_cast<double>(x - (b[i++])), 2);
    });
    std::cout << "\nresult - " << std::accumulate(final.begin(), final.end(), 0.0);

    //обычный цикл, для проверки результата
//    double re = 0;
//    for(int j=0; j < a.size(); ++j)
//        re += pow(a[j]-b[j], 2);
//    std::cout << "\n" << re;
    return 0;
}
