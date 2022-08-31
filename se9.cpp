#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
    // https://leetcode.com/problems/complex-number-multiplication/

    std::string a = "1+2i", b = "1+3i";
    std::istringstream aiss(a), biss(b);
    std::ostringstream oss;
    int areal, breal, aimag, bimag;
    char buf;

    aiss >> areal >> buf >> aimag >> buf;
    biss >> breal >> buf >> bimag >> buf;

    oss << areal * breal - aimag * bimag << '+' << areal * bimag + aimag * breal << 'i';

    std::cout << oss.str();

    std::cout << "\n";

    // https://leetcode.com/problems/simplify-path/

    std::string tmp, res;
    std::vector<std::string> v;
    std::stringstream ss("/a/./b/../../c/");
    while (std::getline(ss, tmp, '/'))
    {
        if (tmp == "" || tmp == ".")
            continue;
        if (tmp == ".." && !v.empty())
            v.pop_back();
        else if (tmp != "..")
            v.push_back(tmp);
    }
    for (auto s : v)
        res += "/" + s;

    std::cout << (res.empty() ? "/" : res);
}
