//
// Created by dima on 07.02.18.
//
#include <cstring> // only for strlen
#include <algorithm> // only for swap

#include "String.h"



String::String(size_t size)
{
    reserve(size);
}

String::String(size_t size, char ch){
    reserve(size);
    fill(ch);
}

String::String(const char *str){

    // Функция strlen получает количество символов в строке которую мы передаём в объект
    reserve(strlen(str));

    // копируем символы строки в массив нашего класса
    for (int i = 0; i < length_; i++)
    {
        this->str_[i] = str[i];
    }

}

String::~String(){
    delete[] this->str_;
}

String::String(String&& other):
        length_(other.length_)
{
    str_ = other.str_;

    other.str_ = nullptr;
    other.length_ = 0;
}


String::String(const String &other){

    length_ = strlen(other.str_);
    reserve(length_ + 1);

    for (int i = 0; i < length_; i++){
        this->str_[i] = other.str_[i];
    }

}

String& String::operator= (const String &other){
    // здесь логика похожа на ту которая реализована в конструкторе, за исключением того, что нам нужно позаботиться
    // об освобождении ресурсов объекта если до копирования в него новой строки он уже содержал код
    // + страндартный синтаксис перегрузки оператора =


    if(str_ == other.str_) // Если присвоили самому себе, то ничего копировать не нужно
        return *this;

    delete[] str_;

    length_ = strlen(other.str_);
    reserve(length_);

    for (int i = 0; i < length_; i++) {
        this->str_[i] = other.str_[i];
    }


    return *this;

}

void String::reserve(size_t size) {
    // Удаляем прошлую запись
    delete[] this->str_;

    this->length_ = size;

    // выделяем память для динамического массива, где будет храниться наша строка
    // +1 символ так как нужно место в массиве под терминирующий 0
    this->str_ = new char[size+1];

    if(this->str_ == nullptr){
        throw std::runtime_error("Unable to allocate memory");
    }

    // закрываем строку терминирующим нулём, т.к. у нас есть c_str() нужно поддерживать валидную си строку
    // иначе 0 на конце не нужен, у нас и так есть поле length_
    this->str_[size] = '\0';

}

String& String::operator=(String&& p){
    // Если присвоили самому себе
    if(str_ == p.str_)
        return *this;

    delete[] str_;

    str_ = p.str_;
    length_ = p.length_;

    p.length_ = 0;
    p.str_ = nullptr;

    return *this;
}

String String::operator+(const String &other)
{
    //создаём новый пустой объект где будим хранить результат конкатенации строк и который будет результатом работы
    // перегруженного оператора +
    String new_str;

    new_str.reserve(this->length_ + other.length_);

    //копируем данные из 2х конкатенируемых строк в новую строку
    int i = 0;

    for (; i < this->length_; i++){
        new_str.str_[i] = this->str_[i];
    }

    for (int j = 0; j < other.length_; j++, i++){
        new_str.str_[i] = other.str_[j];
    }

    // возвращаем результат конкатенации
    return new_str;
}

int String::compare(const String &other) const{
    // 1 если меньше, 0 если равны, -1 если больше
    for (int i = 0; i < std::min(this->length_, other.length_); i++){
        if (this->str_[i] < other.str_[i])
            return  1;
        else if(this->str_[i] > other.str_[i])
            return -1;

    }

    if (this->length_ == other.length_)
        return 0;
    else if(this->length_ < other.length_)
        return 1;
    else
        return -1;


}

// Лексикографическое сравнение (по символам)
bool String::operator<(const String &other) const {
    return  compare(other) == 1;
}

bool String::operator>(const String &other) const {
    return  compare(other) == -1;
}

bool String::operator>=(const String &other) const {
    int cmp = compare(other);
    return  (!cmp) || (cmp == -1);
}

bool String::operator<=(const String &other) const {
    int cmp = compare(other);
    return  (!cmp) || (cmp ==  1);
}


bool String::operator==(const String & other) const{
    return !compare(other);
}

bool String::operator!=(const String & other) const {
    return (bool)compare(other);
}

// попытаться извлеч число в системе счисления base из строки
int String::parseInt(unsigned int base) const {
    // Проверка основания
    if(base < 2 || base > 36) throw std::runtime_error("Invalid base");

    int num = 0, sign = 0, s = 0;

    for(;s<length_ && isspace(str_[s]);s++); // Игнор пробелов в начале
    if(s == length_) throw std::runtime_error("Couldn't parse int from string");

    // Обработка знака
    if(str_[s] == '-'){
        sign = -1;
        s++;
    }else if(str_[s] == '+'){
        sign = 1;
        s++;
    }

    // Пытаемся считать число в НАЧАЛЕ строки
    for(int i = s; (i < length_) && isalnum(str_[i]); i++){
        char d = -1, c = tolower(str_[i]);
        if(isdigit(c))
            d = c -'0'; // Встретилась цифра
        else if(islower(c)){
            d = c - 'a' + (char)10; // Встретилась буква a = 10, b = 11....
        }

        if(d>=0 && d< base){
            num *= base;
            num += d;
        }else{
             // Встетилась цифра/буква, которой нет в системе счисления с основанием base
            throw std::runtime_error("Couldn't parse int from string. Unexpected digit out of base range");
        }
    }

    if(!sign){
        return num;
    }else if(num){
        return sign*num;
    }else{
        throw std::runtime_error("Sign should be followed by at least one digit");
    }

}

// Инверсия строки, возможно лучше чтобы возвращалась инвертированая копия, но зато этот метод не требует доп. памяти
void String::reverse() {
    size_t l = 0, r = length_-1;
    while(l < r){
        std::swap(str_[l++], str_[r--]);
    }
}

// Заполнение строки
void String::fill(char ch) {
    for(int i = 0; i < length_; i++){
        str_[i] = ch;
    }
}

char& String::operator[](int index)
{
    return this->str_[index];
}

char String::operator[](int index) const{
    return this->str_[index];
}

std::istream& operator>>(std::istream &is, String &str) {
    delete[] str.str_; // удаляем то что было
    constexpr size_t kMaxSize = 5000;

    String tmp(kMaxSize); // буфер на стеке в котором будет введенная строка, благо istream умеет вводить си строки
    is>>tmp.str_;

    size_t length = strlen(tmp.str_);

    str.reserve(length); // выделяем новую память для строки

    for(int i = 0; i < str.length_; i++){
        str.str_[i] = tmp[i];
    }

    return is;
}

std::ostream& operator<<(std::ostream &os, const String &str){
    os<<'\"';
    for(int i = 0; i < str.length_; i++){
        os<<str.str_[i];
    }
    os<<'\"';
    return os;
}


int String::firstIndexOf(char ch) const {
    for(size_t i = 0; i < length_; i++){
        if(str_[i] == ch)
            return (int)i;
    }

    return -1;
}

int String::indexOf(char ch, int start) const {
    if(start < length_)
        for(size_t i = start; i < length_; i++){
            if(str_[i] == ch)
                return (int)i;
        }

    return -1;
}

// Вернуть си представление строки
const char *String::c_str() const {
    return str_;
}

size_t String::length() const {
    return length_;
}

// поиск слова в строке, можно быстрее, но так проще
int String::indexOf(const String &other) const {
    // перебор позиций
    for(int i = 0; i <= length_ - other.length_; i++){
        int count_match = 0;
        for(int j = 0; j < other.length_; j++){
            if(str_[i+j] == other[j])
                count_match++; // сколько символов совпадает
        }
        if(count_match == other.length_) return i; // если все совпадают
    }

    return -1; // если не нашли слово
}


