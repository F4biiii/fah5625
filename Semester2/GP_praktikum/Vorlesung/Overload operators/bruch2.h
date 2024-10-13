#ifndef BRUCH2_H
#define BRUCH2_H

#include <string>

class Bruch
{
private:
    int zaehler;
    int nenner;

public:
    Bruch(const int pz, const int pn);
    std::string toString();
    void add(const Bruch bruch);
    void sub(const Bruch bruch);
    void mult(const Bruch bruch);
    void div(const Bruch bruch);
    void kuerze();
    void normalisiere();
    static int ggt(int a, int b);

    void operator+=(const Bruch bruch);
    Bruch operator+(const Bruch bruch);

    int getZaehler() const;
    int getNenner() const;
};

std::ostream& operator<<(std::ostream& s, Bruch b);

#endif
