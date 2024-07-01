#include "bruch.h"

#include <iostream>

using namespace std;

int main() {
    Bruch bruch1(1, 8);
    Bruch bruch2(3, 8);

    bruch1.add(bruch2);
    
    cout << endl <<  "Ergebnis: " << bruch1.toString() << endl;

    return 0;
}
