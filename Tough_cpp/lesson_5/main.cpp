#include <iostream>
#include <set>
#include <list>
/**
Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, и выводящую в консоль список уникальных слов (если слово повторяется больше 1 раза, то вывести его надо один раз). Продемонстрировать работу функции, передав итераторы различных типов.
 */

template<typename it>
void scrumble(it begin, it end){

    std::set<std::string> words;
    std::for_each(begin, end, [=](std::string word){
        words.std::insert(word);
    });
    //for_each
}

int main() {
    std::string line = "Never gon'a give you up never gon'a let you down";
    scrumble(line.begin(), line.end());

    return 0;
}
