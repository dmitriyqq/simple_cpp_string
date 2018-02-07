#include <iostream>
#include <vector>
#include <String.h>
#include <algorithm>

int main(){

    printf("My String class capabilities!\n");

    printf("\n1.\t Concatenation. Let's do simple arithmetics\n");

    String two("2");
    String four= two + two;

    std::cout<<two<<"+"<<two<<"="<<four<<std::endl;

    printf("\n2.\t length\n");
    String what_is_my_length("123456789");

    std::cout<<"length of "<<what_is_my_length<<" is "<<what_is_my_length.length()<<std::endl;

    printf("\n3.\t index of 'x'\n");
    String where_is_x("abcXxXx");

    std::cout<<"first index of 'x' in "<<where_is_x<<" is "<<where_is_x.firstIndexOf('x')<<std::endl;

    printf("\n4.\t index of 'x', start from 6 \n");
    String where_is_x_again("xabcXxXx");

    std::cout<<"index of 'x', start from 6 in "<<where_is_x_again<<" is "<<where_is_x_again.indexOf('x', 6)<<std::endl;

    printf("\n5.\t index of word \"wear\"\n");
    String some_string("Why Java programmers wear glasses? Because they can't C#!!!");

    std::cout<<"index of \"wear\" in "<<some_string<<" is "<<some_string.indexOf("wear")<<std::endl;

    printf("\n6.\t let's do some sorting, and check operator<\n");
    std::vector <String> v;
    const char* t[10] = {"ABCD", "ABCDE", "ABCD123", "NADYA", "IS", "thebest", ".", "abc", "123", "1"};
    for(int i = 0; i < 10; i++)
        v.emplace_back(t[i]);

    printf("  \nnormal sort:\n");
    std::sort(begin(v), end(v), [](const String &a, const String &b){ return a<b;});
    for(auto& e: v) std::cout<<e<<" ";
                    std::cout<<std::endl;

    printf("  \nsort by length:\n");
    std::stable_sort(begin(v), end(v), [](const String &a, const String &b){ return a.length()<b.length();});
    for(auto& e: v) std::cout<<e<<" ";
    std::cout<<std::endl;

    String one("1"), oneone("1");
    printf("\n7.\t Equality<\n");
    std::cout<<one<<"=="<<two<<" is "<<((one==two) ? "true" : "false")<<std::endl;
    std::cout<<one<<"=="<<oneone<<" is "<<((one==oneone) ? "true" : "false")<<std::endl;

    printf("\n8.\t Inequality<\n");
    std::cout<<one<<"!="<<two<<" is "<<((one!=two) ? "true" : "false")<<std::endl;
    std::cout<<one<<"!="<<oneone<<" is "<<((one!=oneone) ? "true" : "false")<<std::endl;

    printf("\n9.\t Move semantics<\n");

    auto swap = [](String& a, String& b){
        // no more copies!
        String tmp(std::move(a));
        a = std::move(b);
        b = std::move(tmp);
        return;
    };

    std::cout<<"one = "<<one<<"two ="<<two<<std::endl;
    swap(one, two);
    std::cout<<"swap(one, two)"<<std::endl;
    std::cout<<"one = "<<one<<"two ="<<two<<std::endl;

    printf("\n10.\toperator>> / operator<<\n>>");

    String input;

    std::cin>>input;
    std::cout<<input<<std::endl;
    //String result;
    //result = str + str2;

    return 0;
}
