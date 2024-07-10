#include <iostream>
#include "employee.h"

int main() {

    std::string name = "Heseler";
    std::string fName = "Fabian";
    std::vector<int> birthday = {2005, 22, 11};
    float salary = 4000.00;
    Employee fabi(name, fName, birthday, salary);
    fabi.print();
    std::cout << std::endl;
    fabi.printEmployee();

    return 0;
}