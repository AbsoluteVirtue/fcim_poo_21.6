#include <iostream>

class Iterable
{

protected:
    unsigned int _size;
    // int _list; список заданного типа
};

class Vector : public Iterable
{
    // реализация
};

class Deque : public Iterable
{
    // реализация
};

class Queue : public Vector, public Deque
{
    // реализация
};

class Feed
{
    Queue numbers;
    unsigned int size{0};

public:
    void
    push(int val)
    {
        // реализация
    }

    void
    pop()
    {
        // реализация
    }

    const int &
    head()
    {
        // реализация
    }

    const int &
    tail()
    {
        // реализация
    }

    bool
    empty()
    {
        // реализация
    }
};

class Producer
{
    Deque values;
    unsigned int size{0};

public:
    Producer()
    {
        int val = 0;
        std::cin >> val;

        if (val > 0)
        {
            size = val;
            for (unsigned int i = 0; i < size; i++)
            {
                std::cin >> val;
                values + val;
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
    Vector values;

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

    while (pro.produce(feed))
        ;

    while (con.consume(feed))
        ;

    con.report_status();

    return 0;
}
