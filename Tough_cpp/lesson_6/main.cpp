#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <iterator>
#include <algorithm>
#include <future>
#include <random>

//TASK_1__________________________________________________________________________________________________________TASK_1
template <typename T>
void pcout (const T &x)  {
    std::mutex mut;
    std::lock_guard<std::mutex> name{ mut };
    std::cout << x;
}
void task1(){
    std::thread t1{pcout<std::string>, "input_1, "};
    std::thread t2(pcout<std::string>, "input_2, ");
    std::thread t3(pcout<std::string>, "input_3, ");
    t1.join();
    t2.join();
    t3.join();
}

//TASK_2__________________________________________________________________________________________________________TASK_2
struct counter{
    double m_nth;
public:
    counter(int nth) : m_nth(nth) {};
    double getnth() const { return m_nth; }
    void display_progress(int current) const {
        std::mutex mut;
        std::lock_guard<std::mutex> name{ mut };
        std::cout << current / ((m_nth+2) / 100) << "%\n";
    };
};

int foo(counter c, int nth){
    std::vector<int> v;
    int x = 1;
    int dividers = 0;
    int result = 0;
    while(x < nth+2){
        dividers = 0;
        v.emplace_back(++result);
        //dividers = std::count_if(v.begin(), v.end(),[=](int y) { return (result % y) == 0; }); //очень долго
        for(int i=0; i<v.size(); ++i){
            if(result % v[i] == 0)
                ++dividers;
            if(dividers > 2)
                break;
        }

        if(dividers <= 2) {
            ++x;
            std::thread t([=](int i) { c.display_progress(i); }, x);
            t.join();
        }
    }
    return result;
}

void task2(){
    std::cout << "\nTask_2\n";
    counter Counter(10000);// милионного числа ждать очень долго
    std::cout << foo(Counter, Counter.getnth());
}
//TASK_3__________________________________________________________________________________________________________TASK_3

std::mutex mut2;

void push(std::vector<int>& TC, std::mt19937& gen, std::uniform_int_distribution<>& dist){
    std::lock_guard<std::mutex> name{ mut2 };
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    TC.emplace_back(dist(gen));
}

void pop(std::vector<int>& TC){
    if(TC.empty())
        return;
    std::lock_guard<std::mutex> name{ mut2 };
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    TC.erase(std::remove(TC.begin(), TC.end(), *(std::max_element(TC.begin(), TC.end()))));
}

void task3(){
    std::cout << "\n\nTask_3\n";

    int rounds = 20;
    std::random_device rd;
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution<> dist(1, 1000);
    std::vector<int> treasure_chest;
    std::vector<std::pair<std::thread, std::thread>> thr; // <master, thief>
    thr.reserve(rounds);
    for(int i=0; i<rounds; ++i) {
        thr.emplace_back((std::thread(push, std::ref(treasure_chest), std::ref(gen), std::ref(dist))),
                         std::thread(pop, std::ref(treasure_chest))); // <master, thief>
    }
    for(int i=0; i<rounds; ++i) {
        thr[i].first.join();
        thr[i].second.join();
    }
}

//MAIN______________________________________________________________________________________________________________MAIN

int main(){
    task1();
    task2();
    std::thread tr([](){task3();}); // иначе эта функция тормозит остальные
    tr.join();
    std::cout << "Задание 3 выполняется корректно, но вектор не успевает набрать больше 1 элемента";
}
