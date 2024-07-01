#ifndef BRUCH_H
#define BRUCH_H

#include <string>

class Bruch {

public:
    Bruch(const int pz, const int pn);
    std::string toString() const;
    void add(const Bruch bruch);
    void sub(const Bruch bruch);
    void mult(const Bruch bruch);
    void div(const Bruch bruch);

private:
    int zaehler;
    int nenner;

    void kuerze();
    void normalisiere();
    static int ggt(int a, int b);
};

#endif 