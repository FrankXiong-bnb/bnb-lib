#ifndef _bnb_Test_Base_H_
#define _bnb_Test_Base_H_

#include<iostream>

template<typename _Ty>
bool Show(const _Ty& arr, const unsigned int* s, unsigned int n)
{
    static int x = 1;
    std::cout << x++ << ": ";
    for (unsigned int i = 0; i < n; i++)
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

void test_sort();
void test_md5();
void test_sha256();
void test_base64();
void test_rc4();
void test_math();
void test_power();
void test_memory();
void test_string();


#endif
