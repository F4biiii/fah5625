#include "person.h"

Person::Person(const std::string& pName, const std::string& pFirstName, const std::vector<int>& pDateOfBirth) {
    name = pName;
    firstName = pFirstName;
    dateOfBirth = pDateOfBirth;
}

void Person::print() const {
    std::cout << "Name:\t\t\t" << name << std::endl;
    std::cout << "First name:\t\t" << firstName << std::endl;
    std::cout << "Date of birth:\t\t" << dateOfBirth[2] << "." << dateOfBirth[1] << "." << dateOfBirth[0] << std::endl;
}

int Person::age() const {
    return 2024 - dateOfBirth[0];
}