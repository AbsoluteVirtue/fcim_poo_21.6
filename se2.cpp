#include <algorithm>
#include <iostream>
#include <vector>

class Vector
{
    unsigned int size;
    int *list_d{nullptr};
    int list_s[1000];
    std::vector<int> list_v;

public:
    ~Vector()
    {
        delete[] list_d;
        list_d = nullptr;

        list_v.clear();

        size = 0;
    }

    Vector() = delete;

    Vector(unsigned int size, int val = 0)
    {
        this->size = size;

        list_d = new int[size];

        list_v = std::vector<int>(size, val);
    }

    Vector(const Vector &other)
    {
        this->size = other.size;

        this->list_d = new int[other.size];
        std::copy(std::begin(this->list_s), std::end(this->list_s), &this->list_s[0]);

        for (unsigned int i = 0; i < other.size; i++)
        {
            this->list_s[i] = other.list_s[i];
        }

        list_v = other.list_v;
    }

    Vector(Vector &&other)
    {
        this->size = other.size;
        other.size = 0;

        this->list_d = other.list_d;
        other.list_d = nullptr;

        std::move(std::begin(this->list_s), std::end(this->list_s), &this->list_s[0]);

        this->list_v = std::exchange(other.list_v, {});
    }

    friend std::ostream &
    operator<<(std::ostream &os, const Vector &obj)
    {
        for (size_t i = 0; i < obj.size; i++)
        {
            os << obj.list_d[i] << " " << obj.list_v[i] << " " << obj.list_s[i] << "\n";
        }

        return os;
    }
};

int main(int argc, char const *argv[])
{
    Vector v(10);

    Vector b(Vector(10));

    Vector c(std::move(b));

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << c;
    }

    return 0;
}
