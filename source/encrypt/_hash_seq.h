#ifndef ____bnb_Hash_Seq_H_
#define ____bnb_Hash_Seq_H_

namespace bnb
{

    inline unsigned int _hash_seq(const unsigned char *ptr, unsigned int n)
    {
        unsigned int _value = 2166136261u;

        for (unsigned int i = 0; i < n; ++i)
        {
            _value ^= static_cast<unsigned int>(ptr[i]);
            _value *= 16777619u;
        }

        return (_value);
    }

}

#endif // ____bnb_Hash_Seq_H_
