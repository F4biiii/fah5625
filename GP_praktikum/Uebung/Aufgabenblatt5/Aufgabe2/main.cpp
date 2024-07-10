#include "bookmap.h"
#include <iostream>

int main() 
{
    Bookmap aBookMap;

    aBookMap.bookInput(1, "BookOne");
    aBookMap.bookInput(2, "BookTwo");
    aBookMap.bookInput(3, "BookThree");
    aBookMap.bookInput(4, "BookFour");
    
    std::cout << aBookMap.getContent() << std::endl;

    return 0;
}