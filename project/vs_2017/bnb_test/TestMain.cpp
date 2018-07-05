#include <iostream>

#include "bnb_IEEEE754.h"

#include "test_base.h"


template<unsigned int x>
void hehe()
{

    std::cout << x << std::endl;
}


union uname {
    constexpr uname(int v) : x(v) { }
    constexpr char getY() const { return y; }

    int x;
    char y;
};


int main()
{
    // test_sort();
    
    // test_math();

    hehe<bnb::t>();

    return 0;
}



