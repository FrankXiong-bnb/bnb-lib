#ifndef ____bnb_Random_H_
#define ____bnb_Random_H_

_bnb_space_in

template<typename _Ty>
_Ty RandomValue(_Ty left, _Ty right)
{
    static_assert(std::is_integral<_Ty>::value, "The parameter must be an integer");

    if (right < left)
        left ^= right ^= left ^= right;

    return std::uniform_int_distribution<>(left, right)(std::mt19937(std::tr1::_Random_device()));
}

template<> double RandomValue(double left, double right)
{
    if (left > right) {
        double mid = left; left = right; right = mid;
    }
    
    return std::uniform_real_distribution<>(left, right)(std::mt19937(std::tr1::_Random_device()));
}

template<> float RandomValue(float left, float right)
{
    return (float)RandomValue<double>((double)left, (double)right);
}

template<typename _Ty>
void RandomDisrupt(_Ty* arr, _size_t size)
{
    if (1 < size)
    {
        for (_size_t i = 0; i < size - 1; ++i)
        {
            _size_t r = RandomValue(i+1, size-1);
            Swap(arr[i], arr[r]);
        }
    }
}

template<typename _Ty>
_size_t ExtractRandom(const _Ty* src, _size_t size, _Ty* dst, _size_t count, bool bSame = true)
{
    _size_t n = 0;

    if (true)
    {
    }

    return n;
}

class _RandFun
{
public:

    template<typename _Ty>
    _Ty operator () (_Ty left, _Ty right) const { return RandomValue(left, right); }

    template<typename _Ty>
    void operator () (_Ty* arr, _size_t size) const { RandomDisrupt(arr, size); }
};

_bnb_space_out

#endif