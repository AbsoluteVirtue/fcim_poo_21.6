/*
Лабораторная работа 6 - Контейнеры

Для заданного варианта реализовать шаблонный класс контейнера (generic container) на основании предыдущей лабораторной работы. Уже реализованные в предыдущих лабораторных работах методы при необходимости изменить согласно требованиям варианта. Добавить реализацию методов, которые должны присутствовать в классе, но отсутствовали в интерфейсе до этого момента. Все варианты должны реализовывать конструктор по умолчанию, конструктор копирования, оператор присваивания (operator=), а также набор статических операций: операторы сравнения (operator==, operator!=, operator<, operator>, operator<=, operator>=), оператор ввода (operator>>), оператор вывода (operator<<).
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
// остальные необходимые библиотеки здесь

// полная реализация контейнера здесь

// код для проверки правильности выполнения задания:
#ifdef ARRAY
int main()
{
    array<int> a1 = {3, 2, 1};
    array<int> a2 = a1;

    std::sort(a1.begin(), a1.end());

    for (auto n : a1)
        std::cout << n << " ";

    std::reverse_copy(a2.begin(), a2.end(),
                      std::ostream_iterator<int>(std::cout, " "));
}
#endif

#ifdef VECTOR
int main()
{
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};

    v.push_back(8);
    v.push_back(9);

    for (int n : v)
        std::cout << n << " ";
    std::cout << "\n";

    v.pop_back();

    v.erase(v.begin());

    v.insert(v.end(), 10);

    v.erase(v.begin() + v.size() - 1, v.end());

    for (auto it = v.begin(); it != v.end();)
    {
        if (*it % 2)
            it = v.erase(it);
        else
            ++it;
    }

    for (int n : v)
        std::cout << n << " ";
}
#endif

#ifdef FORWARD_LIST
int main(int argc, char const *argv[])
{
    forward_list<int> fl1{1, 2, 3, 4, 5};
    forward_list<int> fl2(fl1.begin(), fl1.end());

    for (; !fl1.empty(); fl1.pop_front())
    {
        std::cout << fl1.front() << " ";
    }

    assert(fl1.empty());

    auto itbegin = fl2.begin();
    fl2.insert_after(itbegin, 0);
    fl2.pop_front();
    assert(0 == fl2.front());
}
#endif

#ifdef LIST
int main(int argc, char const *argv[])
{
    list<int> l = {2, 4, 6, 8};

    l.push_front(1);
    l.push_back(9);

    auto it = std::find(l.begin(), l.end(), 6);
    if (it != l.end())
        l.insert(it, 5);

    for (int n : l)
        std::cout << n << " ";
}
#endif

#ifdef PRIORITY_QUEUE
int main()
{
    priority_queue<int> pq1;
    pq1.push(5);
    assert(1 == pq1.size());

    priority_queue<int> pq2{pq1};
    assert(pq1.size() == pq2.size());

    priority_queue<int> pq3({3, 1, 4, 1, 5});
    assert(5 == pq3.size());

    for (; !pq3.empty(); pq3.pop())
        std::cout << pq3.top() << " ";
}
#endif

#ifdef DEQUE
int main(int argc, char const *argv[])
{
    deque<int> q;
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    for (; q.size(); q.pop_front())
        std::cout << q.front() << " ";

    deque<int> s;
    s.push_front(1);
    s.push_front(2);
    s.push_front(3);
    for (; s.size(); s.pop_back())
        std::cout << s.back() << " ";
}
#endif

#ifdef QUEUE
int main()
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    for (; q.size(); q.pop())
        std::cout << q.front() << " ";
}
#endif

#ifdef STACK
int main()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    for (; s.size(); s.pop())
        std::cout << s.top() << " ";
}
#endif

#ifdef SET
int main(int argc, char const *argv[])
{
    set<int> s1;

    s1.insert(3);
    s1.insert(3);
    assert(1 == s1.count(3));

    set<int> s2 = {1, 2, 3, 4, 1, 2, 3, 4};
    assert(4 == s2.size());

    for (auto it = s2.begin(); it != s2.end();)
    {
        if (*it % 2)
            it = s2.erase(it);
        else
            ++it;
    }
    assert(0 == s2.erase(1));
}
#endif

#ifdef UNORDERED_MAP
int main(int argc, char const *argv[])
{
    unordered_map<std::string, std::string> u = {
        {"RED", "#FF0000"},
        {"GREEN", "#00FF00"},
        {"BLUE", "#0000FF"}};

    for (auto n : u)
        std::cout << n.first << ": " << n.second << " ";
    std::cout << std::endl;

    u["BLACK"] = "#000000";
    u["WHITE"] = "#FFFFFF";

    for (auto n : u)
        std::cout << n.first << ": " << n.second << " ";
}
#endif
