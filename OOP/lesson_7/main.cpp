#include "BlackJack.h"

void LessonTask(int &&x){
    std::cout << std::endl;
    for (int i = 0; i < 80; ++i)
        std::cout << '_';
    std::cout << "/ ЗАДАНИЕ " << x << " ";
    std::cout << std::endl;
}

//____________________________________________________________________________________________________________/ЗАДАНИЕ 1

class Date{
    int m_day;
    int m_month;
    int m_year;
public:
    Date(){}
    Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}
    int GetDay() const { return m_day; }
    int GetMonth() const { return m_month; }
    int GetYear() const { return m_year; }

    friend std::ostream& operator << (std::ostream& out, Date& date) {
        out << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear();
        return out;
    }
};

void task1(){
    LessonTask(1);
    auto today = std::make_unique<Date>(7,5,1989);
    std::unique_ptr<Date>date(new Date);
    std::cout << today->GetDay() <<" "
              << today->GetMonth() <<" "
              << today->GetYear() <<" "
              << *today << "\n";
    date = std::move(today);
    std::cout << "today is " << ( (!today)? "nullptr" : "not null" ) << "\n"
              <<  "date is " << ( (!date) ? "nullptr" : "not null" ) << "\n\n";
}

//____________________________________________________________________________________________________________/ЗАДАНИЕ 2

Date& compare(Date& d1, Date& d2){
    if(d1.GetYear() != d2.GetYear())
        return ((d1.GetYear() > d2.GetYear())? d1 : d2);
    else if(d1.GetMonth() != d2.GetMonth())
        return ((d1.GetMonth() > d2.GetMonth())? d1 : d2);
    else
        return ((d1.GetDay() > d2.GetDay())? d1 : d2);
}

void SwapDates(std::unique_ptr<Date> &d1, std::unique_ptr<Date> &d2){
    std::unique_ptr<Date>temp(new Date);
    temp = std::move(d1);
    d1 = std::move(d2);
    d2 = std::move(temp);
}

void task2(){
    LessonTask(2);
    auto date1 = std::make_unique<Date>(07,12,2001);
    auto date2 = std::make_unique<Date>(01,01,2022);
    std::cout<<"The latest date is "<<compare(*date1,*date2) << "\n";

    SwapDates(date1, date2);
    std::cout<< "date1 was changed to " << *date1 << "\n"
             << "date2 was changed to " << *date2 << "\n";
}



int main() {
     
    task1();
     
    task2();

//____________________________________________________________________________________________________________/ЗАДАНИЕ 5
// Вариант блекджека разделенного на модули приложен в директории "модульный блекджек"
     
     
    char choice;
    std::string name;
    std::vector<std::string>players;

    while(true)
    {
        std::cout << "\nEnter player's name: ";
        std::cin >> name;
        players.push_back(name);
        std::cout << "\nMore players? (y/n): ";
        std::cin >> choice;
        if(choice == 'y')
            continue;
        else
            break;
    }
    while(true)
    {
        std::cout << "\n\nStarting game..\n";
        Game BlackJack(players);
        BlackJack.Play();
        std::cout << "\n\nWant to play again? (y/n): ";
        std::cin >> choice;
        if(choice == 'y')
            continue;
        else
            break;
    }
    return 0;
}
