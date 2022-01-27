#include <cstdlib>
#include <vector>

#include "arrayint.h" // задание 1

//---------------------------------------------------------------------------------------
// Задание 3
class card{
    enum m_suit {diamonds, hearts, spades, cross};
    enum m_value{
        ace = 0,
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,};
    m_suit st;
    m_value vl;
    bool isFacedUp = false;
public:
    card (int suit, int value) {
        st = static_cast<m_suit> (suit);
        vl = static_cast<m_value> (value);
    }
    void flip(){
        isFacedUp = !isFacedUp;
    }
    int getValue (){
        return static_cast<int>(vl);
    }
    void setAce(int power){
        vl = static_cast<m_value>(power);
    };
    ~card() {}
};

class hand{
    std::vector<card*> hnd;
public:
    hand(){ hnd.reserve(5); }

    void Add(card* c){
        hnd.push_back(c);
    }

    void Clear(){
        hnd.clear();
    }

    int GetValue(){
        int score = 0;
        int ace = 0;
        int aces[hnd.size()]; // массив для тузов
        for (int i = 0; i < hnd.size(); ++i) {
            if(!hnd[i]->getValue()) // если туз, то он откладывается и считается отдельно от простых карт
                aces[ace++] = i;
            score += hnd[i]->getValue();
        }

        for (int i = 0; i < ace; ++i) { // считаем тузы
            if(score + 11 <= 21) {
                hnd[aces[i]]->setAce(11); // не уверен можно ли считать тузы каждый раз по-разному, и
                score += 11;                     // и как часто вообще будут подсчитываться очки в руке, поэтому пока так.
            }                                    // Любопытно, что согласно дебагеру 11 присваивается следующим образом:
            else                                 // vl={card::m_value} three|eight
            {
                hnd[aces[i]]->setAce(1);
                score += 1;
            }
        }
        return score;
    }


};

int main() {
    //---------------------------------------------------------------------------------------
    // Задание 1
    srand(time(0));

    ArrayInt v;
    for (int i = 0; i < 20; ++i)
        v.push_back(rand() % 50 + 1); // 50 чтобы была некоторая повторяемость, для 2го задания

    std::cout<< "\nvector length is " << v.getLength() << "\n";
    v.Echo();

    v.Sort();
    std::cout<< "\nsorted vector\n";
    v.Echo();

    v.pop_back();
    std::cout<< "\nvector length is " << v.getLength() << "\n";
    v.Echo();

    v.pop_front();
    std::cout<< "\nvector length is " << v.getLength() << "\n";
    v.Echo();
    //---------------------------------------------------------------------------------------
    // Задание 2
    // в этом задании вместо стандартного контейнера решил использовать вектор, который который дан выше,
    // подсчет веду с помощью своего класса недодерева, который тоже лежит в заголовчном.
    MySet set;
    for (int i = 0; i < v.getLength(); ++i) {
        set.push(v[i]);
    }
    std::cout << "\nnumber of unique integers in the vector - " << set.getSize();
//---------------------------------------------------------------------------------------
// Задание 3
//    card c1(0,0);
//    card c2(1,1);
//    card c3(3,2);
//    hand hnd1;
//    hnd1.Add(&c1);
//    hnd1.Add(&c2);
//    hnd1.Add(&c3);
//    std::cout<<"\n\nyour current score is "<<hnd1.GetValue();

    return 0;
}
