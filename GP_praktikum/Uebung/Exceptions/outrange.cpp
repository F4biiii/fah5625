#include <exception>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s = "abc";

    try
    {
        s.at(4) = 'x';
    }
    catch (out_of_range& error)
    {
        cout << error.what() << '\n';
    }
}
