#include <iostream>

// реализация generic-классов
// class Iterable
// class Vector
// class Deque
// class Queue

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

    while (pro.produce(feed))
        ;

    while (con.consume(feed))
        ;

    con.report_status();

    return 0;
}
