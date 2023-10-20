#include <algorithm>
#include <iostream>

using std::cout;

struct vec 
{
	char name{};

	~vec() { cout << "dtor vec " << name << " "; }
	vec(char c) : name(c) { cout << "ctor vec " << name << " "; }
};

struct adapter : public vec
{
	char name{};

	~adapter() { cout << "dtor adapter " << vec::name << " "; }
	adapter(char c) : vec(c) { cout << "ctor adapter " << vec::name << " "; }
};

int main(int argc, char const *argv[])
{
	try
	{
		
		cout << "1. ";
		vec a('a');
		cout << "\n";          // 1. ctor vec a

		cout << "2. ";
		vec *b = new vec('b'); // 2. ctor vec b
		cout << "\n";

		cout << "3. ";
		adapter c('c');        // 3. ctor vec c ctor adapter c
		cout << "\n";

        // throw std::runtime_error("memory leak after this point");

		cout << "4. ";
		delete b;              // 4. dtor vec b

	}                          // dtor adapter c dtor vec c dtor vec a
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
}
