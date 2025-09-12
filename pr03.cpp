#include <algorithm>
#include <initializer_list>

class var
{
private:
    size_t _size{0};
    int *_data{nullptr};
public:
    size_t size() const 
    {
        return _size;
    }

    const int *data() const
    {
        return _data;
    }
    
    var() = default;
    
    var(int *p, size_t n) {
        _size = n;
        _data = p;
    }

    var(size_t n) : _size{n}
    {
        _data = new int[n];
    }
    
    ~var()
    {
        delete [] _data;
    }

    var(const var &a) : var(a.size())
    {
        for (size_t i = 0; i < size(); i++)
        {
            _data[i] = a.data()[i];
        }
    }

    var(const std::initializer_list<int>& l) : var(l.size()) {
        std::copy(l.begin(), l.end(), _data);
    }
};

int main()
{
    var a;
    var b = 1;
    var c = b;
    var d = {(int*)c.data(), c.size()};
    var e = {1, 2, 3, 4, 5};
}
