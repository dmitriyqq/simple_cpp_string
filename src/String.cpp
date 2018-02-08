//
// Created by dima on 07.02.18.
//
#include <cstring> // only for strlen
#include <algorithm> // only for swap

#include "String.h"

String::String() :
    str_(nullptr),
    length_(0)
{
}

String::String(const char *str){


    length_ = strlen(str); // Функция strlen получает количество символов в строке которую мы передаём в объект

    // выделяем память для динамического массива, где будет храниться наша строка
    // +1 символ так как нужно место в массиве под терминирующий 0
    this->str_ = new char[length_ + 1];

    // копируем символы строки в массив нашего класса
    for (int i = 0; i < length_; i++)
    {
        this->str_[i] = str[i];
    }

    // закрываем строку терминирующим нулём, т.к. у нас есть c_str() нужно поддерживать валидную си строку
    // иначе 0 на конце не нужен, у нас и так есть поле length_
    this->str_[length_] = '\0';
}

String::~String(){
    delete[] this->str_;
}

String::String(String&& other):
    length_(other.length_),
    str_(other.str_)
{

    other.str_ = nullptr;
    other.length_ = 0;
}


String::String(const String &other){

    length_ = strlen(other.str_);
    this->str_ = new char[length_ + 1];

    for (int i = 0; i < length_; i++){
        this->str_[i] = other.str_[i];
    }

    this->str_[length_] = '\0';
}

String& String::operator= (const String &other){
    // здесь логика похожа на ту которая реализована в конструкторе, за исключением того, что нам нужно позаботиться
    // об освобождении ресурсов объекта если до копирования в него новой строки он уже содержал код
    // + страндартный синтаксис перегрузки оператора =
    if(*this != other) { // Если присвоили самому себе, то ничего копировать не нужно
        delete[] str_;

        length_ = strlen(other.str_);
        this->str_ = new char[length_ + 1];

        for (int i = 0; i < length_; i++) {
            this->str_[i] = other.str_[i];
        }

        this->str_[length_] = '\0';

        return *this;
    }
}

String& String::operator=(String&& p){
    std::swap(str_, p.str_);
    std::swap(length_, p.length_);
    return *this;
}

String String::operator+(const String &other)
{
    //создаём новый пустой объект где будим хранить результат конкатенации строк и который будет результатом работы
    // перегруженного оператора +
    String new_str;
    // получаем количество символов в обеих строках для конкатенации

    size_t this_length = strlen(this->str_);
    size_t other_length = strlen(other.str_);

    new_str.length_ = this_length + other_length;

    // выделяем место в динамической памяти под новую строку
    new_str.str_ = new char[this_length + other_length + 1];

    //копируем данные из 2х конкатенируемых строк в новую строку
    int i = 0;
    for (; i < this_length; i++)
    {
    new_str.str_[i] = this->str_[i];
    }

    for (int j = 0; j < other_length; j++, i++)
    {
    new_str.str_[i] = other.str_[j];
    }

    new_str.str_[this_length + other_length] = '\0';

    // возвращаем результат конкатенации
    return new_str;
}


bool String::operator==(const String & other) const {
    if (this->length_ != other.length_)
    {
        return false;
    }

    for (int i = 0; i < this->length_; i++){
        if (this->str_[i] != other.str_[i]){
            return false;
        }
    }

    return true;
}

bool String::operator!=(const String & other) const {
    return !(this->operator==(other));
}

// попытаться извлеч число в системе счисления base из строки
int String::parseInt(int base) const {
    int num = 0, sign = 1, s = 0;

    for(;s<length_ && isspace(s);s++); // Игнор пробелов в начале

    // Обработка знака
    if(str_[s] == '-'){
        sign = -1;
        s++;
    }else if(str_[s] == '+'){
        sign = 1;
        s++;
    }
    // Проверка основания
    if(base < 2 || base > 32) throw std::range_error("Invalid base."); // !TODO exceptions

    // Пытаемся считать число в НАЧАЛЕ строки
    for(int i = s; (i < length_) && isalnum(str_[i]); i++){
        char d, c = str_[i];
        if(isdigit(c))
            d = c -'0'; // Встретилась цифра
        else if(islower(c)){
            d = c - 'a' + (char)10; // Встретилась буква a = 10, b = 11....
        }

        if(d>=0 && d< base){
            num*=base;
            num+=d;
        }else{
            break; // Встетилась цифра/буква, которой нет в системе счисления с основанием base
        }
    }

    return sign*num;
}

// Инверсия строки, возможно лучше чтобы возвращалась инвертированая копия, но зато этот метод не требует доп. памяти
void String::reverse() {
    int l = 0, r = length_-1;
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

// Лексикографическое сравнение (по символам)
bool String::operator>(const String &other) const {

    for (int i = 0; i < std::min(this->length_, other.length_); i++){
        if (this->str_[i] < other.str_[i]){
            return false;
        }
    }

    return this->length_ > other.length_;
}

bool String::operator<(const String &other) const {
    for (int i = 0; i < std::min(this->length_, other.length_); i++){
        if (this->str_[i] > other.str_[i]){
            return false;
        }
    }

    return this->length_ < other.length_;
}


char& String::operator[](int index)
{
    return this->str_[index];
}

char String::operator[](int index) const{
    return this->str_[index];
}

std::istream& operator>>(std::istream &is, String &str) {
    delete str.str_; // удаляем то что было
    constexpr size_t kMaxSize = 5000;

    char buf[kMaxSize]; // буфер на стеке в котором будет введенная строка, благо istream умеет вводить си строки
    is>>buf;

    str.length_=strlen(buf);
    str.str_ = new char[str.length_+1]; // выделяем новую память для строки

    for(int i = 0; i < str.length_; i++){
        str.str_[i] = buf[i];
    }
    str.str_[str.length_] = '\0';
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
            return i;
    }

    return -1;
}

int String::indexOf(char ch, int start) const {
    if(start < length_)
        for(size_t i = start; i < length_; i++){
            if(str_[i] == ch)
                return i;
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
        int c = 0;
        for(int j = 0; j < other.length_; j++){
            if(str_[i+j] == other[j])
                c++; // сколько символов совпадает
        }
        if(c == other.length_) return i; // если все совпадают
    }

    return -1; // если не нашли слово
}


