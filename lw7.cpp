#include <iostream>
#include <deque>
#include <queue>
#include <vector>

// реализация generic-классов
typedef std::vector<std::string> Vector;
typedef std::deque<std::string> Deque;
typedef std::queue<std::string> Queue;

class Feed
{
    Queue numbers;
    unsigned int size{0};

public:
    void
    push(std::string val)
    {
        numbers.push(val);
        ++size;
    }

    void
    pop()
    {
        if (size > 0)
        {
            numbers.pop();
            --size;
        }
    }

    const std::string &
    head() { return numbers.front(); }

    const std::string &
    tail() { return numbers.back(); }

    bool
    empty() const { return size == 0; }
};

class Producer
{
    Deque values;
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
                values.push_back(inserted);
            }
        }
    }

    bool
    produce(Feed &feed)
    {
        if (!size)
            return false;

        feed.push(values.back());
        values.pop_back();
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

        values.push_back(feed.head());
        feed.pop();

        return true;
    }

    void
    report_status()
    {
        for (auto it : values)
            std::cout << it << " ";
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
}
