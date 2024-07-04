#include <iostream>

int main()
{
    int number = 1000;

    try
    {
        char* store = new char[number * 1000000000L];
        std::cout << number << " GB reserved without problems.\n";
        delete [] store;
    }
    catch(const std::bad_alloc& exc)
    {
        std::cerr << number << " GB could not be reserved! "
                  << exc.what() << '\n';
    }
}
