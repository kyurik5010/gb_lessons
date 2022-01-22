#include <iostream>
#include <string>

//-----------------------------------------------------------------------------------------
// Задание 1

//int students = 0; // возможно я что-то не так понял, но варианта лучше этого не придумал

class Person
{
    std::string m_name;
    std::string m_gender;
    int m_age;
    double m_weight;
public:
    std::string getName() const { return m_name; }
    std::string getGender() const { return m_gender; }
    int getAge() const { return m_age; }
    double getWeight() const { return m_weight; }

    void setName(std::string &name) { m_name = name; }
    void setGender (std::string &gender) { m_gender = gender; }
    void setAge (int &age) { m_age = age; }
    void setWeight (double &weight) { m_weight = weight; }
};

class Student : virtual public Person
{
    static int students;  // -- вот это интересный момент, так можно делать для создания общей переменной для объектов
    int m_year;           // главное инициализировать ее не здесь и не в мэйне, см. ниже
public:

    Student(std::string name, std::string gender, int age, double weight, int year)
    {
        setName(name);
        setGender(gender);
        setAge(age);
        setWeight(weight);
        m_year = year;
        ++students;       // см. выше
    }
    void setYear(int &year) { m_year = year; }
    int getYear() const { return m_year; }
    void transition() { ++m_year; }
    static void resetStudents() { students = 0; }
    static int getStudents ()  { return students; }
    void printInfo()
    {
        std::cout<< getName() << ", age:"
                 << getAge() << ", gender:"
                 << getGender() << ", year of education:"
                 << getYear() << ", weight:"
                 << getWeight() << "\n";
    }
};

int Student::students = 0; // <-----------------------------------------------------  ОЧЕНЬ ВАЖНО !!!!!!!


//-----------------------------------------------------------------------------------------
// Задание 2

class Fruit{
    std::string m_name;
    std::string m_color;
public:
    std::string getName() const { return m_name; }
    std::string getColor() const { return m_color; }
    void setName (std::string &name) { m_name = name; }
    void setColor (std::string &color) { m_color = color; }

};

class Apple: public Fruit{
public:
    Apple(std::string color = "", std::string name = "apple") {
        setName(name);
        setColor(color);
    }

};

class Banana: public Fruit{
public:

    Banana(std::string color = "yellow", std::string name = "banana")
    {
        setColor(color);
        setName(name);
    }
};

class GrannySmith: public Apple{
    std::string parentName = Apple::getName();
public:
    GrannySmith(std::string color = "green", std::string name = "Granny Smith")  {
        std::string newName = name + " " + parentName;
        setName(newName);
        setColor(color);
    }
};
//-----------------------------------------------------------------------------------------

int main()
{
    // Задание 1
    Student::resetStudents();
    Student GB1 {"Anton", "male", 27, 83.5, 2019};
    Student GB2 {"Viktoria", "female", 28, 102.7, 2018};
    Student GB3 {"Alexander", "male", 30, 87.3, 2020};
    GB1.printInfo();
    GB2.printInfo();
    GB3.printInfo();
    std::cout << "number of students: "<< Student::getStudents() << "\n" << std::endl;
    //---------------------------------------------------------------------------------
    // Задание 2
    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
    //---------------------------------------------------------------------------------
    // Task_3.txt

    return 0;
}
