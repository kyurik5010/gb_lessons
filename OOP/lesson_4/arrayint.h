//
// Created by Юрий Михайлович on 23.01.2022.
//

//--------------------------------------------------------------------------------------------
// Задание 1

#ifndef OOP_LSN_4_ARRAYINT_H
#define OOP_LSN_4_ARRAYINT_H
#include <iostream>
#include <cassert>

void swap(int *a, int *b);
void Qsort(int *arr, int first, int last);

class ArrayInt
{
private:
    int m_length;
    int *m_data;

public:
    ArrayInt(): m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length): m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    int getLength() { return m_length; }

    void erase()
    {
        delete[] m_data;

        // Здесь нам нужно указать m_data значение nullptr, чтобы на выходе не было висячего указателя
        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

// Функция resize изменяет размер массива. Все существующие элементы сохраняются. Процесс медленный
    void resize(int newLength)
    {
        // Если массив уже нужной длины — return
        if (newLength == m_length)
            return;

        // Если нужно сделать массив пустым — делаем это и затем return
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // Теперь знаем, что newLength >0
        // Выделяем новый массив
        int *data = new int[newLength];

        // Затем нужно разобраться с количеством копируемых элементов в новый массив
        // Нужно скопировать столько элементов, сколько их есть в меньшем из массивов
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength; //выбор наименьшего значения длины

            // Поочередно копируем элементы
            for (int index=0; index < elementsToCopy ; ++index)
                data[index] = m_data[index];
        }

        // Удаляем старый массив, так как он нам уже не нужен
        delete[] m_data;

        // И используем вместо старого массива новый! Обратите внимание, m_data указывает
        // на тот же адрес, на который указывает наш новый динамически выделенный массив. Поскольку
        // данные были динамически выделенные — они не будут уничтожены, когда выйдут из области видимости
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        // Проверка корректности передаваемого индекса
        assert(index >= 0 && index <= m_length);

        // Создаем новый массив на один элемент больше старого массива
        int *data = new int[m_length+1];

        // Копируем все элементы до index-а
        for (int before=0; before < index; ++before)
            data[before] = m_data[before];

        // Вставляем новый элемент в новый массив
        data [index] = value;

        // Копируем все значения после вставляемого элемента
        for (int after=index; after < m_length; ++after)
            data[after+1] = m_data[after];

        // Удаляем старый массив и используем вместо него новый
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) { insertBefore(value, m_length); }

    void pop_back(){
        int *data = new int[m_length - 1];

        for (int i = 0; i < m_length-1; ++i) {
            data[i] = m_data[i];
        }
        delete[] m_data;
        m_data = data;
        --m_length;
    } /// СДЕЛАТЬ ЭТО ОДНОЙ ФУНКЦИЕЙ ПОП с параметром в виде индекса

    void pop_front(){
        int *data = new int[m_length - 1];

        for (int i = 1; i < m_length; ++i) {
            data[i-1] = m_data[i];
        }
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void Echo(){
        for(int i = 0; i < m_length; ++i)
        {
            if (i < m_length - 1)
                std::cout << m_data[i] << ", ";
            else
                std::cout << m_data[i] << std::endl;
        }
    }

    void Sort(){
        Qsort(m_data, 0, m_length);
    }

    ~ArrayInt()
    {
        delete[] m_data;
        m_data = nullptr; ////////////
    }
};

// сортировка
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Qsort(int *arr, int first, int last)
{
    if ( (last-first) <= 10 )
    {
        int tmp,current;
        for(int min = 1, len=last+1; min < len; ++min)
        {
            tmp = arr[min];
            current = min-1;
            while(current >= 0 && arr[current] > tmp)
            {
                arr[current+1] = arr[current];
                current--;
            }
            arr[current+1] = tmp;
        }
    }
    else {
        int F = first;
        int L = last;
        int P = last-1;

        if( (arr[F] > arr[P]) && (arr[F] < arr[L]) ) {
            swap(&arr[F], &arr[P]);
        }
        else if( (arr[L] > arr[F]) && (arr[L] < arr[P]) ) {
            swap(&arr[L], &arr[P] );
        }
        else
            do{
                while (arr[F] < arr[P]) { ++F; }
                while (arr[L] > arr[P]) { --L; }
                if (arr[F] >= arr[L]) {
                    swap(&arr[F], &arr[L]);
                    F++;
                    L--;
                }
            } while (arr[F] < arr[L]);
        if (F < last)
            Qsort(arr, F, last);
        if (L > first)
            Qsort(arr, first, L);
    }
}

//--------------------------------------------------------------------------------------------
// Задание 2

class MySet{
    int m_size = 0;
    typedef struct Node{
        int key;
        Node* left;
        Node* right;
    }tree_node;
    tree_node* tree = nullptr;
public:
    MySet() = default;

    int getSize() { return m_size; }

    tree_node* Tinsert(tree_node *t, int key){
        tree_node *tn = new tree_node;
        tn -> key = key;
        tn -> left = nullptr;
        tn -> right = nullptr;
        tree_node* parent = t;
        tree_node* current = t;
        if(parent == nullptr) {
            ++m_size;
            return tn;
        }
        else
        {
            while(current->key != key) {
                if(current->key > key) {
                    parent = current;
                    current = parent->left;
                    if (current == nullptr) {
                        parent->left = tn;
                        current = tn;
                        ++m_size;
                    }
                }
                else if(current->key < key){
                    parent = current;
                    current = parent->right;
                    if (current == nullptr) {
                        parent->right = tn;
                        current = tn;
                        ++m_size;
                    }
                }
            }
        }
        return tn;
    }
    void push(int key){
        tree = Tinsert(tree, key);
    }

    tree_node* erase(){
        if(tree)
        {
            delete tree->right;
            delete tree->left;
        }
        return tree;
    }

    ~MySet(){
        erase();
        delete tree;
    }
};

#endif //OOP_LSN_4_ARRAYINT_H



