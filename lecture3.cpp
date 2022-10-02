#include <iostream>

class color
{
};

class point
{
};

// 1. Пример без наследования
enum kind
{
    circle,
    triangle,
    square
};

class c_shape
{
    kind k;
    point center;
    color col;
public:
    c_shape(kind x) : k(x) {}
    void draw()
    {
        switch (k)
        {
        case circle:
            std::cout << "я - кружочек\n";
            break;
        case triangle:
            std::cout << "я - треугольник\n";
            break;
        case square:
            std::cout << "я - квадратик\n";
        }
    }
};

// 2. Наследование с подтипами (subtyping)
class cpp_shape
{
    // дополнительное поле kind не нужно
    point center;
    color col;
public:
    virtual void draw() = 0; // = 0 отмечает метод как чисто виртуальный, а сам класс - как абстрактный
};

class cpp_square : public cpp_shape
{
    int w, x, y, z;
    int n;
public:
    void draw() override
    {
        std::cout << "я - треугольник\n";
    }
};

class cpp_triangle : public cpp_shape
{
    int x, y, z;
    float a, b, c;
public:
    void draw() override
    {
        std::cout << "я - квадратик\n";
    }
};

class cpp_circle : public cpp_shape
{
    int radius;
public:
    void draw() override
    {
        std::cout << "я - кружочек\n";
    }
};

void draw_all(cpp_shape **array, int size)
{
    for (int i = 0; i < size; ++i)
        array[i]->draw();
}

// 3. Наследование с композицией (containment)
class deque
{
public:
    void push_front() { std::cout << "добавил в начало\n"; }
    void push_back() { std::cout << "добавил в конец\n"; }
    void pop_front() { std::cout << "убрал с начала\n"; }
    void pop_back() { std::cout << "убрал с конца\n"; }
};

class stack
{
    deque data;
public:
    void push_back()
    { 
        std::cout << "я - стэк, ";
        data.push_back(); 
    }
    void pop_back()
    { 
        std::cout << "я - стэк, ";
        data.pop_back(); 
    }
};

int main(int argc, char const *argv[])
{
    c_shape a(kind::square);
    a.draw();

    // полиморфизм подтипов
    cpp_shape *x[3] = {new cpp_circle(), new cpp_triangle(), new cpp_square()};
    draw_all(x, 3);

    // адаптер
    stack s;
    s.push_back();
    s.pop_back();
}
