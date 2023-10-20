#include <iostream>
#include <sstream>

class BaseData
{
protected:
    std::string sizes{"default"};
};

class DataCopyLeft : public BaseData
{
    // в этом классе - своя копия BaseData::sizes
};

class DataCopyRight : public BaseData 
{
    // в этом классе - своя копия BaseData::sizes
};

class DataCopy : public DataCopyLeft, public DataCopyRight
{
protected:
    std::string sizes{"default"};

public:
    DataCopy()
    {
        // изменение DataCopyLeft::BaseData::sizes, DataCopyRight::BaseData::sizes не меняется
        DataCopyLeft::sizes = "changed for DataCopyLeft";
        std::stringstream strs;
        strs << "left sizes: " << DataCopyLeft::sizes << ", right sizes: " << DataCopyRight::sizes;
        sizes = strs.str();
    }
    std::string get_sizes()
    {
        return sizes;
    }
};

class DataRefLeft : public virtual DataCopy
{

public:
    void check_mro()
    {
        std::cout << "called DataRefLeft.check_mro\n";
    }
};

class DataRefRight : public virtual DataCopy
{

public:
    void check_mro()
    {
        std::cout << "called DataRefRight.check_mro\n";
    }
};

class DataRef : public DataRefLeft, public DataRefRight
{

public:
    std::string get_sizes()
    {
        // изменение DataCopy::sizes, меняется для обоих базовых классов с виртуальным наследованием
        DataRefLeft::sizes = "changed for DataRefLeft";
        std::stringstream strs;
        strs << "left sizes: " << DataRefLeft::sizes << ", right sizes: " << DataRefRight::sizes;
        return strs.str();
    }

    void get_mro()
    {
        // костыль для избежания двойственности вызовов
        DataRefLeft::check_mro();
    }
};

int main(int argc, char const *argv[])
{
    DataCopy dc;
    std::cout << dc.get_sizes() << "\n";

    DataRef dr;
    std::cout << dr.get_sizes() << "\n";

    // dr.check_mro(); // не компилируется, так как метод с таким прототипом есть в обоих базовых классах
    dr.get_mro();

    return 0;
}
