#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <optional>

using namespace std;

struct Person {//_______________________________________________________________________________Person

    std::string Surname;
    std::string Name;
    optional<std::string> MiddleName;

    friend bool operator== (const Person& p1, const Person& p2);
    friend bool operator< (const Person& p1, const Person& p2);
    friend std::ostream& operator<< (std::ostream &out, const Person& person);

};

bool operator== (const Person& p1, const Person& p2){
    return tie(p1.Name, p1.Surname, p1.MiddleName) ==
           tie(p2.Name, p2.Surname, p2.MiddleName);
}

bool operator< (const Person& p1, const Person& p2){
    return tie(p1.Name, p1.Surname, p1.MiddleName) <
           tie(p2.Name, p2.Surname, p2.MiddleName);
}

std::ostream& operator<< (std::ostream &out, const Person& person){
    out << std::setw(15) << std::left << person.Surname
        << "\t" << std::setw(15) << person.Name
        << "\t" << std::setw(15) << person.MiddleName.value_or("");
    return out;
}



struct PhoneNumber{ //_______________________________________________________________________________PhoneNumber

    int16_t CountryCode;
    int16_t CityCode;
    std::string Number;
    optional<int16_t> AddNumber;


    friend bool operator< (PhoneNumber& ph1, PhoneNumber& ph2);
    friend bool operator== (PhoneNumber& ph1, PhoneNumber& ph2);
    friend std::ostream& operator<< (std::ostream& out, PhoneNumber& ph);
};

bool operator< (PhoneNumber& ph1, PhoneNumber& ph2){
    return tie(ph1.CountryCode, ph1.CityCode, ph1.Number, ph1.AddNumber) <
           tie(ph2.CountryCode, ph2.CityCode, ph2.Number, ph2.AddNumber);
}

bool operator== (PhoneNumber& ph1, PhoneNumber& ph2){
    return tie(ph1.CountryCode, ph1.CityCode, ph1.Number, ph1.AddNumber) ==
           tie(ph2.CountryCode, ph2.CityCode, ph2.Number, ph2.AddNumber);
}

std::ostream& operator<< (std::ostream& out, PhoneNumber& ph){
    std::string temp;// = (ph.AddNumber.value() == 0)? "" : to_string(ph.AddNumber.value());
    if(!ph.AddNumber.has_value())
        temp = "";
    else if(ph.AddNumber.value() == 0)
        temp = "";
    else
        temp = to_string(ph.AddNumber.value());
    out << std::left << "+" << ph.CountryCode << "(" << ph.CityCode << ")" << ph.Number << " "
    << temp;

    return out;
}



class PhoneBook{//_______________________________________________________________________________PhoneBook
     vector<pair<Person, PhoneNumber>> book;
public:
    PhoneBook(ifstream& file){
        std::stringstream buffer;
        std::string line, patronimic, additional;
        while(file){
            Person person;
            PhoneNumber number;
            getline(file,line);
            buffer << line;
            buffer >> person.Surname >> person.Name >> patronimic
                   >> number.CountryCode >> number.CityCode >> number.Number >> additional;
            person.MiddleName.emplace((patronimic == "-")? "" : patronimic);
            number.AddNumber.emplace((additional == "-")? 0 : stoi(additional));
            book.emplace_back(person, number);

            buffer.str("");
            buffer.clear();
            line = "";
        }
    }
    void SortByName() {
        sort(book.begin(), book.end(),
             [](pair<Person, PhoneNumber>sub1, pair<Person, PhoneNumber>sub2)
                    {
                        return tie(sub1.first.Surname, sub1.first.Name, sub1.first.MiddleName) <
                               tie(sub2.first.Surname, sub2.first.Name, sub2.first.MiddleName);
                    }
             );
    }
    void SortByPhone() {
        sort(book.begin(), book.end(),
             [](pair<Person, PhoneNumber>sub1, pair<Person, PhoneNumber>sub2)
             {
                 return sub1.second < sub2.second;
             }
        );
    }

    pair<std::string, PhoneNumber> GetPhoneNumber(const std::string& surname) {
        //пытался вторым элементом пары сделать optional<PhoneNumber>,variant или any
        //но компиллятор не дал. Получается только возвращать како-то номер,
        // либо нужно менять в мейне out << get<1>(answer) на return get<1>(answer)

        // чем вызвано такое поведение?


        int count = 0, last = 0;
        for(int i=0;i<book.size();++i){
            if(book[i].first.Surname == surname) {
                ++count;
                last = i;
            }
        }

        if(count == 1) {
            return {"", book[last].second};
        }
        else if(count >= 2){
            return {"found more than 1", book[0].second};
        }
        else{
            return {"not found", book[0].second};
        }
    }

    void ChangePhoneNumber (Person subscriber, PhoneNumber number) {
        auto temp = make_pair(subscriber, number);
        for (int i = 0; i < book.size(); ++i) {
            if (book[i].first == subscriber) {
                book[i].swap(temp);
            }
        }
    }
    friend std::ostream& operator<< (std::ostream& out, PhoneBook& book);
};

std::ostream& operator<< (std::ostream& out, PhoneBook& book){
    for(auto& line : book.book){
        out << line.first << "\t" << line.second << "\n";
    }
    return out;
}

int main() {
    ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt PhoneBook book(file);
    PhoneBook book(file);

    cout << book;
    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;
    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;

    cout << "-----GetPhoneNumber-----" << endl;
// лямбда функция, которая принимает фамилию и выводит номер телефона человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname) {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer);
        else
            cout << get<0>(answer);
        cout << endl;
    };

// вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
                           PhoneNumber{7, 123, "15344458", nullopt});
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
                           PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;
    return 0;
}
