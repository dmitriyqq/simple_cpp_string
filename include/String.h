//
// Created by dima on 07.02.18.
//

#ifndef STRING_CLASS_CPP_STRING_H
#define STRING_CLASS_CPP_STRING_H

#include <ostream>
#include <istream>

class String
{
    // TODO!
    // operator+= (char) - Надо все переделывать, чтобы реализовать это за О(1)
    // substr - Реальзовать кольцевой хеш...


protected:
    //указатель на массив char, хранит символы, которые мы передали в наш объект
    char *str_ = nullptr;

    size_t length_ = 0;

    int compare(const String& other) const;

    static size_t strlen(const char* str);

    static void swap(char &a, char &b);


public:

    // Конструктор без параметров
    String() = default;

    // Конструктор с резервированием памяти
    explicit String(size_t size);

    // Конструктор с заполнением
    String(size_t size, char ch);

    // Конструктор с параметрами, при создании объекта класса необходимо перелать строку которую он будет хранить
    String(const char *str);

    // конструктор копирования, необходим для создании точной копии объекта класса, но в другой области памяти
    String(const String& other);

    // Деструктор, отвечает за освобождение ресурвов занятых объектом, вызывается при уничтожении объекта класса
    virtual ~String();

    // Move конструктор
    String(String&& other);

    // Первый индекс символа ch в строке, или -1, если такого символа нет
    int firstIndexOf(char ch) const;

    // Индекс начиная с start
    int indexOf(char ch, int start) const;

    //Поиск слова в строке
    int indexOf(const String & other) const;

    // Преобразование числа в строку
    int parseInt(unsigned int base) const;

    // Преобразование
    void reverse();

    // Заполнить строку
    void fill(char ch);

    // Выделяет память
    void reserve(size_t ch);

    //
    void assign(const char * str);

    // Вернуть си-строку
    const char* c_str() const;

    // Длина строки
    size_t length() const;

    // Перегруженый оператор присваивания, вызывается когда необходимо присвоить значение одного объекта другому
    String& operator=(const String& other);

    // Move
    String& operator=(String&& p);

    // Перегруженный оператор сложения, в текущей реализации класса String необходим для конкатенации строк
    String operator+(const String& other);

    // Операторы сравнения
    bool operator==(const String& other) const;

    bool operator!=(const String& other) const;

    bool operator>(const String& other) const;

    bool operator>=(const String& other) const;

    bool operator<=(const String& other) const;

    bool operator<(const String& other) const;

    // Операторы произвольного доступа
    char operator[](size_t index) const;

    char& operator[](size_t index);

    // Выводит строку в консоль, в идеале для этого необходима перегрузка оператора «
    // нах*й принт даешь потоки
    friend std::istream& operator>>(std::istream& is, String& str);

    friend std::ostream& operator<<(std::ostream& os, const String& str);
    // void Print();
    // int Length()


};


#endif //STRING_CLASS_CPP_STRING_H
