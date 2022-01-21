#include <iostream>
//--------------------------------------------------------------------------------------
// Задание 1
class Figure{
public:
    Figure () {}
    virtual double area (double, double) = 0;
    virtual ~Figure() {}
};

class Circle : public Figure{
    double const Pi = 3.1415926535;
public:
    Circle() {}
    double area (double radius, double ignore_this = 0) override {
        return Pi * (radius * radius);
    }
    virtual ~Circle() {}
};

class Parallelogramm : public Figure{
public:
    Parallelogramm() {}
    virtual double area (double height, double width) override {
        return height * width;
    }
    virtual ~Parallelogramm() {}
};

class Rectangle : public Parallelogramm{
public:
    Rectangle() {}
    double area (double side, double width) override {
        return side * width;
    }
    virtual ~Rectangle() {}
};

class Rhombus : public Parallelogramm{
public:
    Rhombus() {}
    double area (double height, double side) override {
        return side * height;
    }
    virtual ~Rhombus() {}
};

class Square : public Parallelogramm{
public:
    Square() {}
    double area (double side, double ignore_this = 0) override {
        return side * side;
    }
    virtual ~Square() {}
};

//--------------------------------------------------------------------------------------
// Задание 2

class car{
    std::string m_company;
    std::string m_model;
public:
    car(std::string company, std::string model) :
                m_company(company), m_model(model) {
        std::cout << "Car " << company << " " << model << "\n";
    }

    ~car() { }
};

class PassengerCar : virtual public car {
public:
    PassengerCar(std::string company, std::string model) : car(company, model) {
        std::cout << "PassengerCar " << company << " " << model << "\n";
    }
    ~PassengerCar() { }
};

class Bus : virtual public car {
public:
    Bus(std::string company, std::string model) : car(company, model) {
        std::cout << "Bus " << company << " " << model << "\n";
    }
    ~Bus() { }
};

class MiniVan : public PassengerCar, Bus {
public:
    MiniVan(std::string company, std::string model) :
    car(company, model), PassengerCar(company, model), Bus(company, model) {
        std::cout << "MiniVan " << company << " " << model << "\n";
    }
    ~MiniVan() { }
};
//--------------------------------------------------------------------------------------
// Задание 3
class fraction{
    int m_x; //  X
    int m_y; //  Y
public:
    fraction(int x, int y) : m_x(x), m_y(y) {}
    friend fraction operator+ (fraction &f1, fraction &f2)
    {
        return fraction ((f1.m_x + f2.m_x), (f1.m_y + f2.m_y));
    }
    friend fraction operator- (fraction &f1, fraction &f2)
    {
        return fraction ((f1.m_x - f2.m_x), (f1.m_y - f2.m_y));
    }
    friend fraction operator* (fraction &f1, fraction &f2)
    {
        return fraction ((f1.m_x * f2.m_x), (f1.m_y * f2.m_y));
    }
    friend fraction operator/ (fraction &f1, fraction &f2)
    {
        return fraction ((f1.m_x * f2.m_y), (f1.m_y * f2.m_x));
    }
    friend bool operator< (fraction &f1, fraction &f2)
    {
        return ((f1.m_x * f2.m_y) < (f2.m_x * f1.m_y));
    }
    friend bool operator<= (fraction &f1, fraction &f2)
    {
        return ((f1.m_x * f2.m_y) <= (f2.m_x * f1.m_y));
    }
    friend bool operator== (fraction &f1, fraction &f2)
    {
        return ((f1.m_x * f2.m_y) == (f2.m_x * f1.m_y));
    }
    friend bool operator> (fraction &f1, fraction &f2)
    {
        return ((f1.m_x * f2.m_y) > (f2.m_x * f1.m_y));
    }
    friend bool operator>= (fraction &f1, fraction &f2)
    {
        return ((f1.m_x * f2.m_y) >= (f2.m_x * f1.m_y));
    }
    void frint (){
        std::cout << "\n" << m_x << "/" << m_y;
    }
    ~fraction() {}
};

//--------------------------------------------------------------------------------------
// Задание 4
class card{
    enum m_suit {diamonds, hearts, spades, cross};
    enum m_value {ace, two, three, four, five, six, seven, eight, nine, ten};
    m_suit s;
    m_value v;
    bool state = false;
public:
    card (int suit, int value) {
        s = static_cast<m_suit> (suit);
        v = static_cast<m_value> (value - 1);
    }
    void flip(){
        state = !state;
    }
    int getValue (){
        return static_cast<int>(v) + 1;
    }
    ~card() {}
};

int main() {
//--------------------------------------------------------------------------------------
// Задание 1
    Circle s;
    std::cout<<s.area(3) << "\n\n";
//--------------------------------------------------------------------------------------
// Задание 2
    car c("company1", "model1");
    PassengerCar p("company2", "model2");
    Bus b("company3", "model3");
    MiniVan m("company4", "model4");
//--------------------------------------------------------------------------------------
// Задание 3
    std::cout << "\n";
    fraction f1(7,5);
    fraction f2(3,6);
    std::cout << (f1 == f2 ? "true " : "false ");
    std::cout << (f1 >= f2 ? "true " : "false ");
    std::cout << (f1 < f2 ? "true " : "false ");
    fraction f3 = f1 + f2;
    f3.frint();
    f3 = f3 * f2;
    f3.frint();
    fraction f4 = f3 / f1;
    f4.frint();

//--------------------------------------------------------------------------------------
// Задание 4
    card c1(0, 3);
    std::cout << "\n\nthe value is " << c1.getValue();
}
