namespace bnb
{

    inline unsigned int gcd(unsigned int _a, unsigned int _b)
    {
        if (!!!(_a || _b))
            return (0);

        if (_a > _b)
            _a ^= _b ^= _a ^= _b;

        while (_a)
        {
            unsigned int _r = _b % _a;
            _b = _a;
            _a = _r;
        }

        return _b;
    }

}
