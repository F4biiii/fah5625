#include <iostream>
#include <vector>

using namespace std;

void print(const string& pName, const string& pFirstName, const vector<int>& pBirthday, const float pSalary)
{
    cout << "Name:\t\t\t" << pName << endl;
    cout << "First name:\t\t" << pFirstName << endl;
    cout << "Date of birth:\t\t" << pBirthday[2] << "." << pBirthday[1] << "." << pBirthday[0] << endl;
    cout << "Salary:\t\t\t" << pSalary  << " Euro" << endl;
}   


int main() {
    string name = "Alster";
    string firstName = "Ingrid";
    
    vector<int> dateOfBirth = {1990, 06, 11};


    cout.width(2); // Breite
    cout.fill('0'); // fuehrende Nullen
    cout.setf(ios::fixed); // Gleitpunktausgabe mit Punkt
    cout.precision(2); // Anzahl der Nachkommastellen
    print(name, firstName, dateOfBirth, 4000.00);

    return 0;
}