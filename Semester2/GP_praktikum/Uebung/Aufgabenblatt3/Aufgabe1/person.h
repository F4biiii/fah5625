#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream>

class Person {

public:
    Person(const std::string& pName, const std::string& pFirstName, const std::vector<int>& pDateOfBirth);
    void print() const;
    int age() const;

private:
    std::string name;
    std::string firstName;
    std::vector<int> dateOfBirth;
};

#endif
