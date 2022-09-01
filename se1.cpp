#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>


class Coordinates
{
private:
    int x{0}, y{0};
    char *desc{nullptr};

public:
    // деструктор
    ~Coordinates()
    {
        delete[] desc;
    }
    // конструктор, вызываемый по умолчанию
    Coordinates() = default;
    // параметризированный конструктор
    Coordinates(const int x, const int y, const char *desc = NULL)
    {
        this->x = x;
        this->y = y;

        if (desc)
        {
            this->desc = new char[strlen(desc) + 1];
            strcpy(this->desc, desc);
        }
    }
    // конструктор копирования (deep copy)
    Coordinates(const Coordinates &other)
    {
        this->x = other.x;
        this->y = other.y;

        if (this->desc == nullptr && other.desc)
        {
            this->desc = new char[strlen(other.desc) + 1];
            strcpy(this->desc, other.desc);
        }
    }
    // свой метод для вывода
    void print() const
    {
        std::cout << ((this->desc) ? this->desc : "") << ": "
                  << this->x << ", "
                  << this->y << std::endl;
    }
    // перегрузка оператора вывода
    friend std::ostream &operator<<(std::ostream &os, const Coordinates &other)
    {
        return os << ((other.desc) ? other.desc : "") << ": "
                  << other.x << ", " << other.y;
    }
    // перегрузка оператора сложения двух объектов
    Coordinates operator+(const Coordinates &other) const
    {
        Coordinates tmp(other.x + x, other.y + y);
        return tmp;
    }
    // перегрузка оператора присваивания (deep copy)
    Coordinates &operator=(const Coordinates &other)
    {
        this->x = other.x;
        this->y = other.y;

        if (other.desc)
        {
            if (this->desc != nullptr)
            {
                delete[] this->desc;
                this->desc = nullptr;
            }
            this->desc = new char[strlen(other.desc) + 1];
            strcpy(this->desc, other.desc);
        }
        return *this;
    }
    // метод, инициализирующий объект из строки
    static void from_string(Coordinates &data, char *str)
    {
        char *temp[3];
        char *token = strtok(str, ",");
        int i = 0;
        while (token != NULL && i < 3)
        {
            temp[i++] = token;
            token = strtok(NULL, ",");
        }

        if (data.desc != nullptr)
        {
            delete[] data.desc;
            data.desc = nullptr;
        }
        data.desc = new char[strlen(temp[0]) + 1];
        strcpy(data.desc, temp[0]);

        data.x = std::stoi(temp[1]);
        data.y = std::stoi(temp[2]);
    }
};

int main(int argc, char const *argv[])
{
    // прямой вызов параметрического конструктора
    Coordinates coord1 = Coordinates(1, 2, "hello");
    // вывод состояния объекта через свой метод явно
    coord1.print();

    Coordinates coord2(10, 20, "world");
    // вывод состояния объекта через перегруженный оператор << неявно
    std::cout << coord2 << std::endl;
    // присваивание по значению (deep copy)
    Coordinates coord3 = coord2;
    // инициализация массива объектов
    std::list<Coordinates> arr = {coord1, coord2, coord3};
    // вывод элементов массива, используя итератор класса list
    for (const Coordinates &coord : arr)
    {
        std::cout << "-->" << coord << std::endl;
    }
    // вызов конструктора по умолчанию неявно
    Coordinates coord4;
    char str[] = "test,100,200";
    // вызов статичного метода класса для инициализации объекта из строки
    Coordinates::from_string(coord4, str);
    // добавление элемента в массив
    arr.push_back(coord4);

    Coordinates coord5 = coord1 + coord2;

    arr.push_back(coord5);

    int i = 1;
    for (const Coordinates &coord : arr)
    {
        std::cout << i++ << "->" << coord << std::endl;
    }
}
