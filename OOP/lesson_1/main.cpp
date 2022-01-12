#include <iostream>
#include <cstdint>
//------------------------------------------------------------------------------------------------------------------
// Задание 1

class Power{
    int x;
    int y;
public:
    void set(int a, int b){
        x = a;
        y = b;
    }
    int calculate() {
        for (int i = 1, temp = x; i < y; i++)
            x *= temp;
        return x;
    }
};

//------------------------------------------------------------------------------------------------------------------
// Задание 2
class RGBA
{
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;
public:
    RGBA(int _m_red = 0, int _m_green = 0, int _m_blue = 0, int _m_alpha = 255)
    {
        m_red = static_cast <uint8_t> (_m_red);
        m_green = static_cast <uint8_t> (_m_green);
        m_blue = static_cast <uint8_t> (_m_blue);
        m_alpha = static_cast <uint8_t> (_m_alpha);
    }
    void print()
    {
        std::cout << "\n  red - " << static_cast <unsigned short> (m_red) << "\n"
                  << "green - " << static_cast <unsigned short> (m_green) << "\n"
                  << " blue - " << static_cast <unsigned short> (m_blue) << "\n"
                  << "alpha - " << static_cast <unsigned short> (m_alpha) << "\n";
    }
    ~RGBA() = default;

};

//------------------------------------------------------------------------------------------------------------------
// Задание 3

class Stack
{
    int stack[10]{};
    int size = 0;
    int *itr = stack;  // итератор
public:
    Stack () = default; // такой синтаксис для "тривиального конструктора" так мне посоветовал clion. Это правильно?
    bool push (int item)
    {
        if(size < 10)
        {
            *(itr++) = item;
            ++size;
        }
        else
        {
            std::cout << "Stack is full";
            return false;
        }
        return true;
    }
    bool pop()
    {
        int temp;
        if(size > 0)
        {
            temp = *itr;
            *(itr--) = 0;
            --size;
        }
        else
        {
            std::cout << "Stack is empty";
            return false;
        }
        return temp;
    }
    void reset()
    {
        int i = 0;
        while(i < 10) //с учетом заранее определенного размера стека решил, что 10 - не магическое число
        {
            *(itr++) = 0;
            ++i;
        }
        size = 0;
        itr = stack;
    }
    void print()
    {
        std::cout << "\n(";
        for (int i = 0; i < size; ++i)
            std::cout << stack[i] << ((i == size-1)? "" : ", ");
        std::cout << ")";
    }
    ~ Stack() = default; // Это тоже подсказал clion, обозвав "тривиальным деструктором"
};


int main() {
    //------------------------------------------------------------------------------------------------------------------
    // Задание 1
    Power pow;
    pow.set(5, 6);
    std::cout << pow.calculate() << std::endl;
    //------------------------------------------------------------------------------------------------------------------
    // Задание 2
    RGBA color(255,0,255);
    color.print();
    //------------------------------------------------------------------------------------------------------------------
    // Задание 3
    Stack stack;
    stack.reset();
    stack.print();
    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();
    stack.pop();
    stack.print();
    stack.pop();
    stack.pop();
    stack.print();

    return 0;
}
