#include <iostream>
#include <vector>
#include <String.h>
#include <algorithm>
#include <memory>
#include <Exception.h>
int main(){
    try{
    printf("My String class capabilities!\n");

    printf("\n1.\t Concatenation. Let's do simple arithmetics\n");

    String two("2");

    // Ничего не произойдет
    two=two; // Ok
    two = std::move(two); // Ok

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


    String t[10] = {"ABCD", "ABCDE", "ABCD123", "NADYA", "IS", "thebest", ".", "abc", "123", "1"};

    printf("  \nnormal sort:\n");
    // stl сортировка
    std::sort(t, t+10, [](const String &a, const String &b){
        return a<b;
    });

    for(int i = 0; i < 10; i++)
        std::cout<<t[i]<<" ";
    std::cout<<std::endl;

    printf("  \nsort by length:\n");

    std::stable_sort(t, t+10, [](const String &a, const String &b){
        return a.length()<b.length();
    });

    for(int i = 0; i < 10; i++)
        std::cout<<t[i]<<" ";
    std::cout<<std::endl;

    String one("1"), oneone("1");
    printf("\n7.\t Comparisons\n");
    std::cout<<one<<"=="<<two<<" is "<<((one==two) ? "true" : "false")<<std::endl;
    std::cout<<one<<"=="<<oneone<<" is "<<((one==oneone) ? "true" : "false")<<std::endl;
    std::cout<<one<<"<"<<one<<" is "<<((one<one) ? "true" : "false")<<std::endl;
    std::cout<<one<<"<"<<two<<" is "<<((one<two) ? "true" : "false")<<std::endl;
    std::cout<<one<<">"<<oneone<<" is "<<((one>oneone) ? "true" : "false")<<std::endl;
    std::cout<<one<<">"<<two<<" is "<<((one > two) ? "true" : "false")<<std::endl;
    std::cout<<one<<">="<<two<<" is "<<((one >= two) ? "true" : "false")<<std::endl;
    std::cout<<one<<"<="<<two<<" is "<<((one <= two) ? "true" : "false")<<std::endl;
    std::cout<<one<<">="<<oneone<<" is "<<((one >= oneone) ? "true" : "false")<<std::endl;
    std::cout<<one<<"!="<<two<<" is "<<((one!=two) ? "true" : "false")<<std::endl;
    std::cout<<one<<"!="<<oneone<<" is "<<((one!=oneone) ? "true" : "false")<<std::endl;

    printf("\n9.\t Move semantics\n");

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

    printf("\n10.\t parseInt(int base)\n");
    String number("-451  "), binary("1011101"), hex("FFA");
    std::cout<<hex<<"(16) = "<<hex.parseInt(16)<<std::endl;
    std::cout<<one<<"(10) = "<<one.parseInt(10)<<std::endl;
    std::cout<<number<<"(10) = "<<number.parseInt(10)<<std::endl;
    std::cout<<binary<<"(2) = "<<binary.parseInt(2)<<std::endl;
    std::cout<<one<<"(10) = "<<one.parseInt(10)<<std::endl;
    std::cout<<number<<"(10) = "<<number.parseInt(10)<<std::endl;
    std::cout<<binary<<"(2) = "<<binary.parseInt(2)<<std::endl;
    std::cout<<String("  222")<<"(3) = "<<String("  222").parseInt(3)<<std::endl;
    std::cout<<String("   -222")<<"(4) = "<<String("   -222").parseInt(4)<<std::endl;
    std::cout<<String("   1")<<"(5) = "<<String("   1").parseInt(5)<<std::endl;
//    std::cout<<String("  ")<<"(5) = "<<String("  ").parseInt(5)<<std::endl; Error
//    std::cout<<String(" - ")<<"(5) = "<<String(" - ").parseInt(5)<<std::endl; Error
    std::cout<<String(" 7   ")<<"(16) = "<<String(" 7   ").parseInt(16)<<std::endl;
//    std::cout<<String("gg ")<<"(16) = "<<String("gg ").parseInt(16)<<std::endl; Error

    printf("\n11.\t reverse\n");
    String alpha("abcdefg");
    std::cout<<alpha<<" reverse is ";
    alpha.reverse();
    std::cout<<alpha<<std::endl;

    printf("\n12.\t fill\n");
    std::cout<<alpha<<".fill(1) is ";
    alpha.fill('1');
    std::cout<<alpha<<std::endl;


    printf("\n13.\toperator []<<\n");
    String str = "string";
    str[0] = 'S';
    std::cout<<str<<std::endl;


    // Check memory leak
    // Char constructor
    String *die = new String("die");
    // Reserve constructor
    String *str3 = new String(153);
    // Default constructor
    String *kek2 = new String();
    // Copy constructor
    String *kek1 = new String(str);

    delete die;
    delete str3;
    delete kek1;
    delete kek2;

    printf("\n14.\tdelete nullptr and NULL has no effect\n");
    String *nul = new String();
    nul->assign(nullptr);
    delete nul;

    printf("\n15.\toperator>> / operator<<\n>>");
    String input;

    std::cin>>input;
    std::cout<<input<<std::endl;
    //String result;
    //result = str + str2;
    } catch(Exception& e){
        std::cout<<std::endl<<e.what()<<std::endl;
    }
    return 0;
}
