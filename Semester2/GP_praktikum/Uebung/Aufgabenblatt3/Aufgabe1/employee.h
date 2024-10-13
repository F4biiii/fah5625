#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <vector>
#include <string>

#include "person.h"

class Employee : public Person {

public:
    Employee(const std::string& pName, const std::string& pFirstName, const std::vector<int>& pDateOfBirth, const float pSalary);
    static std::string getCompany();
    float getSalary() const;
    void printEmployee() const;
    void riseSalary(const float rise);

private:
    static std::string company;
    float salary;

};

#endif