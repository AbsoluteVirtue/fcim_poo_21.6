#include <iostream>

template <typename Type>
class Iterable
{

protected:
    unsigned int size_{0};
    Type *list_{nullptr};
};

template <typename Type>
class Vector : public virtual Iterable<Type>
{

public:
    ~Vector()
    {
        delete[] this->list_;
        this->list_ = nullptr;
    }

    Vector()
    {
        this->size_ = 0;
        this->list_ = nullptr;
    }

    Vector(const unsigned int size, const Type val = 0)
    {
        if (size == 0)
            return;

        this->list_ = new int[size];
        for (unsigned int i = 0; i < size; i++)
        {
            this->list_[i] = val;
        }

        this->size_ = size;
    }

    Vector(const std::initializer_list<Type> &il)
    {
        this->size_ = 0;
        this->list_ = nullptr;
        *this = il;
    }

    Vector(const Vector<Type> &other)
    {
        this->size_ = 0;
        this->list_ = nullptr;
        *this = other;
    }

    Vector(Vector<Type> &&other) noexcept
    {
        this->size_ = 0;
        this->list_ = nullptr;
        *this = std::move(other);
    }

    friend std::ostream &
        operator<<(std::ostream &os, const Vector<Type> &obj)
    {
        for (unsigned int i = 0; i < obj.size_; i++)
        {
            os << obj.list_[i] << " ";
        }

        return os;
    }

    friend std::istream &
        operator>>(std::istream &is, Vector<Type> &obj)
    {
        for (unsigned int i = 0; i < obj.size_; i++)
        {
            is >> obj.list_[i];
        }

        return is;
    }

    Vector<Type> &
        operator=(const std::initializer_list<Type> &il)
    {
        delete[] this->list_;

        this->size_ = il.size();
        this->list_ = new Type[this->size_];
        std::copy(il.begin(), il.end(), this->list_);

        return *this;
    }

    Vector<Type> &
        operator=(const Vector<Type> &other)
    {
        if (&other != this)
        {
            delete[] this->list_;

            this->size_ = other.size_;
            this->list_ = new Type[this->size_];
            for (unsigned int i = 0; i < this->size_; i++)
            {
                this->list_[i] = other.list_[i];
            }
        }
        return *this;
    }

    Vector<Type> &
        operator=(Vector<Type> &&other) noexcept
    {
        if (&other != this)
        {
            delete[] this->list_;

            this->size_ = other.size_;
            this->list_ = other.list_;

            other.list_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    Vector<Type> &
        operator+(const Type val)
    {
        Type *tmp = new Type[this->size_ + 1];
        for (unsigned int i = 0; i < this->size_; i++)
        {
            tmp[i] = this->list_[i];
        }
        tmp[this->size_] = val;
        ++(this->size_);
        delete[] this->list_;
        this->list_ = tmp;

        return *this;
    }

    friend Vector<Type>
        operator+(const Vector<Type> &lhs, const Vector<Type> &rhs)
    {
        Vector<Type> tmp;
        tmp.size_ = lhs.size_ + rhs.size_;
        tmp.list_ = new Type[tmp.size_];
        for (unsigned int i = 0; i < lhs.size_; i++)
        {
            tmp.list_[i] = lhs.list_[i];
        }

        for (unsigned int i = 0, j = lhs.size_; i < rhs.size_; ++i, ++j)
        {
            tmp.list_[j] = rhs.list_[i];
        }

        return std::move(tmp);
    }

    Type
        operator--(int)
    {
        --(this->size_);
        Type val = this->list_[this->size_];
        Type *tmp = new Type[this->size_];

        for (unsigned int i = 0; i < this->size_; i++)
        {
            tmp[i] = this->list_[i];
        }
        delete[] this->list_;
        this->list_ = tmp;

        return val;
    }

    virtual Type &
        operator[](unsigned int idx);
};

template <typename Type>
Type& 
    Vector<Type>::operator[](const unsigned idx)
{
    return this->list_[(idx < this->size_) ? idx : this->size_ - 1];
}

template <typename Type>
class Deque : public virtual Iterable<Type>
{

public:
    ~Deque()
    {
        delete[] this->list_;
        this->list_ = nullptr;
    }

    Deque()
    {
        this->size_ = 0;
        this->list_ = nullptr;
    }

    Deque(const std::initializer_list<Type> &il)
    {
        this->size_ = 0;
        this->list_ = nullptr;
        *this = il;
    }

    Deque(const Deque<Type> &other)
    {
        this->size_ = 0;
        this->list_ = nullptr;
        *this = other;
    }

    Deque(Deque<Type> &&other) noexcept
    {
        this->size_ = 0;
        this->list_ = nullptr;
        *this = std::move(other);
    }

    Deque<Type> &
        operator=(const std::initializer_list<Type> &il)
    {
        delete[] this->list_;

        this->size_ = il.size();
        this->list_ = new Type[this->size_];
        std::copy(il.begin(), il.end(), this->list_);

        return *this;
    }

    Deque<Type> &
        operator=(const Deque<Type> &other)
    {
        if (&other != this)
        {
            delete[] this->list_;
            this->size_ = other.size_;
            this->list_ = new Type[this->size_];
            for (unsigned int i = 0; i < this->size_; i++)
            {
                this->list_[i] = other.list_[i];
            }
        }
        return *this;
    }

    Deque<Type> &
        operator=(Deque<Type> &&other) noexcept
    {
        if (&other != this)
        {
            delete[] this->list_;

            this->size_ = other.size_;
            this->list_ = other.list_;

            other.list_ = nullptr;
            other.size_ = 0;
        }

        return *this;
    }

    friend std::ostream &
        operator<<(std::ostream &os, const Deque<Type> &obj)
    {
        for (unsigned int i = 0; i < obj.size_; i++)
        {
            os << obj.list_[i] << " ";
        }
        return os;
    }

    friend std::istream &
        operator>>(std::istream &is, Deque<Type> &obj)
    {
        for (unsigned int i = 0; i < obj.size_; i++)
        {
            is >> obj.list_[i];
        }
        return is;
    }

    friend Deque<Type> &
        operator+(const Type val, Deque<Type> &lhs)
    {
        ++lhs.size_;
        Type *tmp = new Type[lhs.size_];
        for (unsigned int i = 1; i < lhs.size_; i++)
        {
            tmp[i] = lhs.list_[i - 1];
        }
        tmp[0] = val;
        delete[] lhs.list_;
        lhs.list_ = tmp;

        return lhs;
    }

    Deque &
        operator+(const Type val)
    {
        Type *tmp = new Type[this->size_ + 1];
        for (unsigned int i = 0; i < this->size_; i++)
        {
            tmp[i] = this->list_[i];
        }
        delete[] this->list_;
        this->list_ = tmp;
        tmp[this->size_] = val;
        ++(this->size_);

        return *this;
    }

    Type
        operator--(int)
    {
        if (0 == this->size_)
            throw std::out_of_range("size is 0");

        --(this->size_);
        Type val = this->list_[this->size_];
        Type *tmp = new Type[this->size_];

        for (unsigned int i = 0; i < this->size_; i++)
        {
            tmp[i] = this->list_[i];
        }
        delete[] this->list_;
        this->list_ = tmp;

        return val;
    }

    void
        operator--()
    {
        if (0 == this->size_)
            return;

        Type *tmp = new Type[this->size_ - 1];

        for (unsigned int i = 0, j = 1; j < this->size_; i++, j++)
        {
            tmp[i] = this->list_[j];
        }
        --(this->size_);
        delete[] this->list_;
        this->list_ = tmp;
    }

    const Type &
        operator~()
    {
        return this->list_[(this->size_ > 0) ? this->size_ - 1 : 0];
    }

    const Type &
        operator*()
    {
        return this->list_[0];
    }

    virtual Type &
        operator[](unsigned int idx);
};

template <typename Type>
Type &
    Deque<Type>::operator[](const unsigned int idx)
{
    return this->list_[(idx < this->size_) ? idx : this->size_ - 1];
}

template <typename Type>
class Queue : public Vector<Type>, public Deque<Type>
{

public:
    template <typename Type_>
    friend std::istream &
        operator>>(std::istream &is, Queue<Type_> &obj) = delete;
    template <typename Type_>
    friend Queue
        operator+(Queue lhs, const Queue<Type_> &rhs) = delete;
    template <typename Type_>
    friend Queue
        operator+(Queue lhs, const Vector<Type> &rhs) = delete;
    Type
        operator--(int) = delete;

    Queue() {}
    Queue(const Vector<Type> &obj) : Vector<Type>(obj) {}
    Queue(const Deque<Type> &obj) : Deque<Type>(obj) {}
    Queue(const std::initializer_list<Type> &il) : Vector<Type>(il) {}

    using Vector<Type>::operator+;
        Queue &operator+=(const Type val)
    {
        *this + val;

        return *this;
    }

    void
        operator--()
    {
        if (0 == this->size_)
            return;

        Type *tmp = new Type[this->size_ - 1];

        for (unsigned int i = 0, j = 1; j < this->size_; i++, j++)
        {
            tmp[i] = this->list_[j];
        }
        delete[] this->list_;
        --(this->size_);
        this->list_ = tmp;
    }

    const Type &
        operator~() const
    {
        return *(this->list_ + (this->size_ - 1));
    }

    const Type &
        operator*() const
    {
        return *(this->list_);
    }
};

class Feed
{
    Queue<std::string> numbers;
    unsigned int size{0};

public:
    void
        push(std::string val)
    {
        numbers += val;
        ++size;
    }

    void
        pop()
    {
        if (size > 0)
        {
            --numbers;
            --size;
        }
    }

    const std::string &
        head() { return *numbers; }

    const std::string &
        tail() { return ~numbers; }

    bool
        empty() const { return size == 0; }
};

class Producer
{
    Deque<std::string> values;
    unsigned int size{0};

public:
    Producer()
    {
        unsigned int val = 0;
        std::cin >> val;

        if (val > 0)
        {
            size = val;
            std::string inserted;
            for (unsigned int i = 0; i < size; i++)
            {
                std::cin >> inserted;
                values + inserted;
            }
        }
    }

    bool
        produce(Feed &feed)
    {
        if (!size)
            return false;

        feed.push(values--);
        --size;

        return true;
    }
};

class Consumer
{
    Vector<std::string> values;

public:
    Consumer() {}

    bool
        consume(Feed &feed)
    {
        if (feed.empty())
            return false;

        values + feed.head();
        feed.pop();

        return true;
    }

    void
        report_status()
    {
        std::cout << values;
    }
};

int main(int argc, char const *argv[])
{
    Producer pro;
    Consumer con;
    Feed feed;

    while (pro.produce(feed));

    while (con.consume(feed));

    con.report_status();

    return 0;
}
