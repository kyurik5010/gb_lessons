#include "BlackJack.h"

// комментарии в первых 3-х заданиях я делал для себя
// 4-е задание выполнено в конце заголовочника


using namespace std;
//---------------------------------------------------------------------------------
//Задание 1

template <class T>
class Pair1{
    const T m_first;
    const T m_second;
public:
    Pair1( T first, T second) : m_first(first), m_second(second){}
    T first() const { return m_first; }     // внимание на const, это нужно для создания константного объекта класса
    T second() const { return m_second; }
};
//---------------------------------------------------------------------------------
//Задание 2

template <class T, class S>
class Pair2{
    T m_first;
    S m_second;
public:
    Pair2( T first, S second) : m_first(first), m_second(second){}
    T first() const { return m_first; }
    S second() const { return m_second; }
    ~Pair2() {}
};
//---------------------------------------------------------------------------------
//Задание 3

template<class T>
class Pair2<T, string>{
    T m_second;
    string m_first;
public:
    Pair2(string first, T second) : m_second(second) , m_first(first) {}
    T second() const { return m_second; }
    string first() const { return m_first; }
    ~Pair2() {}
};

template<class V>       //          параметры <> нужно менять !! Здесь, при наследовании класса Pair2<T, string>
class StringValuePair : public Pair2<V, string>{ //шаблон Pair2 частично специализируется параметром из'V' шаблона
    string m_first;                              //ребенка, т.е. в момент создания ребенка шаблон родителя специализируется
    V m_second;                                  //полностью за счет типа 'V' из шаблона ребенка и стринга которым он
public:                                          //частично специализирован изначально сслыки на источник нет,т.к. получилось случайно
    StringValuePair(string str, V value) : Pair2<V, string>(str, value) {}
    ~StringValuePair() {}    //Конструктор родителя вызывается с такой же кофигурацией, что и при наследовании
};                           // P.S. при вызове конструктора шаблонного класа родителя необходимо
                             // прописывать полное имя родителя, т.е. включая шаблон с нужными параметрами
                             // Pair2<параметр, параметр>(параметр, параметр)
//---------------------------------------------------------------------------------
//Задание 4 в заголовочном

int main() {
    //---------------------------------------------------------------------------------
    //Задание 1

    Pair1<int> p1(6, 9);
    std::cout << "Pair1: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);  // по поводу const см выше
    std::cout << "Pair1: " << p2.first() << ' ' << p2.second() << '\n';
    //---------------------------------------------------------------------------------
    //Задание 2

    Pair2<int, double> d1(6, 7.8);
    std::cout << "Pair2: " << d1.first() << ' ' << d1.second() << '\n';

    const Pair2<double, int> d2(3.4, 5);
    std::cout << "Pair2: " << d2.first() << ' ' << d2.second() << '\n';
    //---------------------------------------------------------------------------------
    //Задание 3

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    //Задание 4 в заголовочном

    return 0;
}
