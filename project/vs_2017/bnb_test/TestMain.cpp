#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<list>
#include<iostream>
#include <utility>
#include <map>

#include "bnb_Algorithm.h"


template<typename _Ty>
bool Show(const _Ty& arr, const unsigned int* s, unsigned int n)
{
    static int x = 1;
    std::cout << x++ << ": ";
    for (unsigned int  i = 0; i < n; i++)
    {
        std::cout << arr[s[i]];
    }

    std::cout << std::endl;

    return true;
}

template<typename _Ty>
void Show(const _Ty* s, unsigned int n)
{
    for (unsigned int i = 0; i < n; i++)
    {
        std::cout << " " << s[i];
    }

    std::cout << std::endl;
}

int main()
{
    int xrr[] = { 7,5,6,4,2,1,3,30, 17, 19, 21, 18, 22, 16, 10, 11, 13, 8, 9, 14, 13, 2, 7, 8, 22, 23, 24, 25, 29, 27, 26, 1, 100, 64 };
    char arr[] = "abcdefg";

    std::string s("ABCDEFG");

   //  Permutation(Show<decltype(arr)>, arr, 6, 3);
    // bnb::Permutation(6, 7, [&arr, &s](const unsigned int* st, unsigned int n) { return Show(s.c_str(), st, n); });

    Show(xrr, 34);

    for (unsigned int n = 1; n < 35; ++n) {
        bnb::QuickSort(xrr, n, [](const int& a, const int& b) { return b < a; });
        Show(xrr, n);
    }

    return 0;
}
