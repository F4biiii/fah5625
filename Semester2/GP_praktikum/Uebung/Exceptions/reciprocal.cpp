#include <exception>
#include <iostream>
#include <string>
using namespace std;

class DivError : public exception
{
private:
    string funct;
public:
    DivError(string pFunct) : exception()
    {
        funct = pFunct;
    }

    string getMessage()
    {
        return "DivError: division by 0 in " + funct;
    }
};

float reciprocal(const float x)
{
    if (x != 0.0)
        return 1/x;
    else
        throw "Exception: division by 0 in reciprocal";
        //throw runtime_error("runtime_error: division by 0 in reciprocal");
        //throw DivError("reciprocal");
}

int main()
{
    try
    {
        cout << "reciprocal(2.0): " << reciprocal(2.0) << '\n';
        cout << "reciprocal(0.0): " << reciprocal(0.0) << '\n';
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }
    catch (runtime_error& error)
    {
        cout << error.what() << '\n';
    }
    catch (DivError& error)
    {
        cout << error.getMessage() << '\n';
    }
}
