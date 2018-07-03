#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<list>
#include<iostream>
#include <utility>
#include <map>
#include <algorithm>

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

void test_arr(int (f)[4])
{
    for (int i = 0; i < 4; i++)
    {
        f[i] += 1;
    }
}

#include <Windows.h>

#include "../encrypt/_encrypt.h"

int main()
{
    static const unsigned char _base64_alphabet[64]{
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a,
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x2b, 0x2f
    };

    int xrr[] = { 7,5,6,4,2,1,3,30, 17, 19, 21, 18, 22, 16, 10, 11, 13, 8, 9, 14, 13, 2, 7, 8, 22, 23, 24, 25, 29, 27, 26, 1, 100, 64 };
    char arr[] = "abcdefg";

    std::string s("ABCDEFG");

   //  Permutation(Show<decltype(arr)>, arr, 6, 3);
    // bnb::Permutation(6, 7, [&arr, &s](const unsigned int* st, unsigned int n) { return Show(s.c_str(), st, n); });

    Show(xrr, 34);

    for (unsigned int n = 1; n < 35; ++n) {
        // bnb::QuickSort(xrr, n, [](const int& a, const int& b) { return b < a; });
        // Show(xrr, n);
    }

    // bnb::Combination(5, 2, [&arr, &s](const unsigned int* st, unsigned int n) { return Show(s.c_str(), st, n); });

    // bnb::Combination(5, 3, [&arr, &s](const unsigned int* st, unsigned int n) { return Show(s.c_str(), st, n); });

    /*
    unsigned char _base_mapping[256]{ 0 };
    for (unsigned int i = 0; i < 64; ++i)
        _base_mapping[_base64_alphabet[i]] = i;

    for (int i = 0; i < 256; ++i)
    {
        if (0 == i % 16) std::cout << std::endl;
        printf("0x%02x, ", _base_mapping[i]);
    }
    */

    unsigned char src[] = "khfkshfhaisgiweuqgq* Note: Replace for loop with standard memset if possible.wbghqjbgjqhgwfgqkfhkah* Note: Replacefor loop with standard memset if possible.kfhaskdhfkadsjgfadg* Note: Replace with standard memset if possible.shh* Note: Replace with standard memset if possible.";
    /*
    unsigned char buf1[1024]{ 0 }, buf2[1024]{ 0 };
    bnb::Base64Encrypt(buf1, src, 50);
    std::cout << buf1 << std::endl;

    bnb::Base64Decrypt(buf2, buf1, 68);
    std::cout << buf2 << std::endl;
    */

    unsigned char xxx64[64]{ 0 }, xxx32[32]{ 0 }, xxx16[16]{ 0 };
    bnb::MD5(xxx16, src, sizeof(src) - 1);
    bnb::DigestToSignature(xxx32, xxx16);
    Show(xxx32, 32);

    bnb::SHA256(xxx32, src, sizeof(src) - 1);
    bnb::DigestToSignature(xxx64, xxx32);
    Show(xxx64, 64);

    return 0;
}



