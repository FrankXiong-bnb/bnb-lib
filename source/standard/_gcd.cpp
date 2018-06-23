namespace bnb
{

    unsigned int gcd(unsigned int _a, unsigned int _b)
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

    unsigned int lcm(unsigned int _a, unsigned int _b)
    {
        if (!!!(_a || _b))
            return (0);

        return (_a * _b / gcd(_a, _b));
    }

}
