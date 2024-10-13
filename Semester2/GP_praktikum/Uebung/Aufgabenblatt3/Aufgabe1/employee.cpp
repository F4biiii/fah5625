#include "employee.h"

std::string Employee::company = "Airbus Defence and Space GmbH";

Employee::Employee(const std::string& pName, const std::string& pFirstName, const std::vector<int>& pDateOfBirth, const float pSalary) : Person(pName, pFirstName, pDateOfBirth) {
    salary = pSalary;
}

std::string Employee::getCompany() {
    return company;
}

float Employee::getSalary() const {
    return salary;
}

void Employee::printEmployee() const {
    print();
    std::cout << "Salary:\t\t\t" << salary  << " Euro" << std::endl;
}

void Employee::riseSalary(const float rise) {
    salary += rise;
}



