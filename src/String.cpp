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

    //закрываем строку терминирующим нулём
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
    if (this->str_ != nullptr)
    {
        delete[] str_;
    }

    length_ = strlen(other.str_);
    this->str_ = new char[length_ + 1];

    for (int i = 0; i < length_; i++){
        this->str_[i] = other.str_[i];
    }

    this->str_[length_] = '\0';

    return *this;
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

bool String::operator>(const String &other) const {

    for (int i = 0; i < std::min(this->length_, other.length_); i++){
        if (this->str_[i] < other.str_[i]){
            return false;
        }
    }

    return this->length_ > other.length_;

}

int String::parseInt(int base) const {
    int num = 0, sign = 1, s = 0;

    if(str_[0] == '-'){
        sign = -1;
        s = 1;
    }else if(str_[0] == '+'){
        sign = 1;
        s = 1;
    }

    if(base < 2 || base > 32) return -1; // !TODO exceptions

    for(int i = s; (i < length_) && isalnum(str_[i]); i++){

        auto convert = [](char c){
            c = tolower(c);
            if(isdigit(c))
                return c -'0';
            else if(islower(c)){
                return (c - 'a' + (char)10);
            }
        };

        char d = convert(str_[i]);
        //printf("%c", d);
        if(d>=0 && d< base){
            num*=base;
            num+=d;
        }else{
            return -1;
        }
    }
    return sign*num;
}

void String::reverse() {
    int l = 0, r = length_-1;
    while(l < r){
        std::swap(str_[l++], str_[r--]);
    }
}

void String::fill(char ch) {
    for(int i = 0; i < length_; i++){
        str_[i] = ch;
    }
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
    delete str.str_;
    constexpr size_t kMaxSize = 5000;

    str.str_ = new char[kMaxSize]; // Лучше бы table doubling намутила

    is>>str.str_;
    str.length_=strlen(str.str_);
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

const char *String::c_str() const {
    return str_;
}

size_t String::length() const {
    return length_;
}

int String::indexOf(const String &other) const {
    for(int i = 0; i <= length_-other.length_; i++){
        int c = 0;
        for(int j = 0; j < other.length_; j++){
            if(str_[i+j] == other[j])
                c++;
        }
        if(c == other.length_) return i;
    }
    return -1;
}


