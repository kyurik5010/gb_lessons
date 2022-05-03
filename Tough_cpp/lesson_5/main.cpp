#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>


//TASK_1__________________________________________________________________________________________________________TASK_1

template<typename iter>
void scrumble(iter begin, iter end){
    std::set<std::string> words;
    std::for_each(begin, end, [&](std::string word){ words.insert(word); });
    std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, " "));
}

void task1(){
    std::stringstream line;
    line << "Never gonna give you up never gonna let you down";
    std::string word;
    std::list<std::string> lst;
    std::vector<std::string> vec;
    while (line){
        line >> word;
        lst.push_back(word);
        vec.push_back(word);
    }
    std::cout << "input iterator:\n";
    scrumble(lst.begin(), lst.end());
    std::cout << "\noutput iterator:\n";
    scrumble(&vec[0], &vec[vec.size()-1]);
}
//TASK_2__________________________________________________________________________________________________________TASK_2

void task2(){
    std::cout << "Enter text here: ";
    std::string text;// = "Using an associative container write a program that will read data from the standard input stream and brake it into individual sentences. It then should sort them by length and write them to the terminal in order with indication of the amount of words used in the sentence. This is a task I would prefer to complete using pairs of keys and sentences. Keys will represent number of words in sentence. These numbers will be computed in the process of text analysis. The keys and data will be put in a map that shall sort them by values of keys.";
    getline(std::cin,text);

    std::string text2 = "";
    int counter = 0;

    std::multimap<int, std::string> dict;

    int it = 0, it2 = 0;
    while(it < text.size()) {

        if(it == 0) {
            it = text.find('.');
            text2.insert(0, text, 0, it + 1);
            it2 = ++(++it);
        }
        else{
            it = text.find('.', it2);
            text2.insert(0, text, it2, it-it2 + 1);
            it2 = ++(++it);
        }

        counter = std::count(text2.begin(), text2.end(), ' ') + 1;
        dict.insert({counter, text2});
        counter = 0;
        text2 = "";
    }
    std::for_each(dict.begin(), dict.end(), [](std::pair<int, std::string> X){
        std::cout << X.first << " words in sentence: '" << X.second <<"'\n";
    });
}

//MAIN______________________________________________________________________________________________________________MAIN
int main() {
    std::cout << "Task_1: \n";
    task1();
    std::cout << "\nTask_2: \n";
    task2();
    return 0;
}
