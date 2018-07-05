#ifndef ____bnb_repeat_buffuer_h_
#define ____bnb_repeat_buffuer_h_

namespace bnb
{

    class repeat_buf
    {
        static const unsigned int __maxsize = (1 << 22);

    private:

        unsigned int  _capacity;
        unsigned int   _head;
        unsigned int   _size;
        char*   _data;

        static inline unsigned int getbit(unsigned int n)
        {
            unsigned int bit(1 << 1);
            while (n >>= 1) bit <<= 1;

            return ((__maxsize > bit) ? bit : __maxsize);
        }

    public:

        ~repeat_buf() { if (_data) delete[] _data; }

        repeat_buf(unsigned int n = 0x00) : _head(0), _size(0)
        {
            _capacity = getbit(n);

            _data = new char[_capacity];

            if (_data)
                for (unsigned int i = _capacity; i; _data[--i] = 0);
        }

        repeat_buf(char v, unsigned int n) : _head(0), _size(0)
        {
            _capacity = getbit(n);

            _data = new char[_capacity];

            if (_data)
            {
                _size = (_capacity < n) ? _capacity : n;

                for (unsigned int i = _size; i--; _data[i] = v);
            }
        }

        repeat_buf(const char* str, unsigned int n) : _head(0), _size(0)
        {
            _capacity = getbit(n);

            _data = new char[_capacity];

            if (_data)
            {
                _size = (_capacity < n) ? _capacity : n;

                for (unsigned int i = _size; i--; _data[i] = str[i]);
            }
        }

        repeat_buf(const repeat_buf& buf) : _head(0), _size(buf._size), _capacity(buf._capacity)
        {
            _data = new char[_capacity];

            if (_data)
                for (unsigned int i = _size; i--; _data[i] = buf._data[buf._head + i]);
        }

        repeat_buf& operator = (const repeat_buf& buf)
        {
            if (this != &buf)
            {
                if (_data) delete[] _data;

                _head = 0;
                _size = buf._size;
                _capacity = buf._capacity;

                _data = new char[_capacity];

                if (_data)
                    for (unsigned int i = _size; i--; _data[i] = buf._data[buf._head + i]);
            }

            return *this;
        }

    public:

        unsigned int GetCapacity() const { return _capacity; }

        unsigned int GetSize() const { return _size; }

        unsigned int GetFree() const { return (_capacity - _size - _head); }

        char* GetHead() { return (_data + _head); }

        bool AddData(const char* src, unsigned int n)
        {
            if (_size + n > __maxsize) return false;

            if (_size + n > _capacity)
            {
                unsigned int need = getbit(_size + n);

                char* p = new char[need];
                if (!p) return false;

                unsigned int i = 0;

                for (; i < _size; ++i) p[i] = _data[_head + i];

                for (i = 0; i < n; ++i) p[_size + i] = src[i];

                delete[] _data;

                _data = p;
                _head = 0;
                _size += n;
                _capacity = need;
            }
            else
            {
                Adjust();

                for (unsigned int i = 0; i < n; ++i)_data[_size + i] = src[i];

                _size += n;
            }

            return true;
        }

        bool AddSize(unsigned int n)
        {
            if (_head + _size + n > _capacity) return false;

            _size += n;

            return true;
        }

        void Delete(unsigned int n)
        {
            if (_size > n)
                _size -= n;
            else
                _size = 0;
        }

        bool Extend(bool keep = true)
        {
            unsigned int after = getbit(_capacity);

            if (after > _capacity)
            {
                char* p = new char[after];

                if (p)
                {
                    if (keep)
                        for (unsigned int i = _size; i--; p[i] = _data[_head + i]);
                    else
                        _size = 0;

                    delete[] _data;
                    _data = p;
                    _head = 0;
                    _capacity = after;

                    return true;
                }
            }

            return false;
        }

        void ClearEx()
        {
            if (_data) delete[] _data;

            _head = 0;
            _size = 0;
            _capacity = getbit(1);
            _data = new char[_capacity];

            if (_data)
                for (unsigned int i = _capacity; i--; _data[i] = 0);
        }

        void Clear()
        {
            _head = 0;
            _size = 0;

            if (_data)
                for (unsigned int i = _capacity; i--; _data[i] = 0);
        }

        void Adjust()
        {
            if (_head)
            {
                for (unsigned int i = 0; i < _size; ++i) _data[i] = _data[_head + i];

                _head = 0;
            }
        }

        template<typename _FuncT>
        bool Analyze(_FuncT pfunc, _out char* dst, _in_out unsigned int& bufsize)
        {
            if (pfunc((const char*)(_data + _head), _size, dst, bufsize))
            {
                Delete(bufsize);

                return true;
            }

            return false;
        }

    };  // class RepeatBuffer

}

#endif
