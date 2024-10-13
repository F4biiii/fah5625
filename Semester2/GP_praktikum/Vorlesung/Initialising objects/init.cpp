#include <iostream>

int show(int v, std::string s)
{
    std::cout << "init of " << s << " with " << v << '\n';
    return v;
}

class Init
{
private:
    int b;
    int c = show(3, "c");
    int a;

public:
    Init(const int pb, const int pa);
};

Init::Init(const int pb, const int pa): b(show(pb, "b"))
{
    a = show(pa, "a");
}

int main()
{
    Init i(2, 1);
    return 0;
}
