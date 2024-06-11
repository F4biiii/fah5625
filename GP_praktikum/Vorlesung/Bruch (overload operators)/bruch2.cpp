#include "bruch2.h"

Bruch::Bruch(const int pz, const int pn)
{
    zaehler = pz;

    if (pn == 0)
        nenner = 1;
    else
        nenner = pn;
}

std::string Bruch::toString()
{
    return std::to_string(zaehler) + "/" + std::to_string(nenner);
}

void Bruch::add(const Bruch bruch)
{
    zaehler = zaehler * bruch.nenner + bruch.zaehler * nenner;
    nenner = nenner * bruch.nenner;
    normalisiere();
}

void Bruch::sub(const Bruch bruch)
{
    zaehler = zaehler * bruch.nenner - bruch.zaehler * nenner;
    nenner = nenner * bruch.nenner;
    normalisiere();
}

void Bruch::mult(const Bruch bruch)
{
    zaehler = zaehler * bruch.zaehler;
    nenner = nenner * bruch.nenner;
    normalisiere();
}

void Bruch::div(const Bruch bruch)
{
    zaehler = nenner * bruch.nenner;
    nenner = zaehler * bruch.zaehler;
    normalisiere();
}

void Bruch::kuerze()
{
    if (zaehler != 0 && nenner != 0)
    {
        int teiler = ggt(zaehler, nenner);
        zaehler = zaehler / teiler;
        nenner = nenner / teiler;
    }
}

void Bruch::normalisiere()
{
    kuerze();

    if (nenner < 0)
    {
        zaehler = -zaehler;
        nenner = -nenner;
    }
}

int Bruch::ggt(int a, int b)
{
    if (a < 0)
        a = -a;

    if (b < 0)
        b = -b;

    while (a != b)
        if (a > b)
            a = a - b;
        else
            b = b - a;

    return a;
}

void Bruch::operator+=(const Bruch bruch)
{
    zaehler = zaehler * bruch.nenner + bruch.zaehler * nenner;
    nenner = nenner * bruch.nenner;
    normalisiere();
}

Bruch Bruch::operator+(const Bruch bruch)
{
    Bruch b(1, 1);
    b.zaehler = zaehler * bruch.nenner + bruch.zaehler * nenner;
    b.nenner = nenner * bruch.nenner;
    b.normalisiere();
    return b;
}

int Bruch::getZaehler() const
{
    return zaehler;
}

int Bruch::getNenner() const
{
    return nenner;
}

std::ostream& operator<<(std::ostream& s, Bruch b)
{
    std::string a = std::to_string(b.getZaehler()) + "/" + std::to_string(b.getNenner());
    s << a;
    return s;
}
