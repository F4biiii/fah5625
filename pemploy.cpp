#include <iostream>
#include <vector>
#include <string>
#include "pemploy.h"

using namespace std;

void print(const string & n, const string & f, const vector <int> & d, const float s){
    cout << "Name:           "<< n <<'\n';
    cout << "Fitst Name:     "<< f <<'\n';
    cout << "Date of birth:  ";
    cout.width(2);
    cout.fill('0');
    cout << d[2]<< '.';
    cout.width(2);
    cout.fill('0');
    cout << d[1]<< '.' << d[0] << '\n';
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "Salary:         ";
    cout << s;


}

void riseSalary(float& s, const float rise){
    s = s * (rise / 100 + 1);
}

// int main (){
//     string name = "Mustermann";
//     string firstname = "Heinz ";

//     vector <int> dateOfBirth = {1990 , 6 , 11};
//     float salary = 4000.0;
//     print(name, firstname, dateOfBirth, salary);
// }