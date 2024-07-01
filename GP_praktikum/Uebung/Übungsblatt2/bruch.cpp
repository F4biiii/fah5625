#include "bruch.h"

    Bruch::Bruch(const int pz, const int pn) {
        zaehler = pz;
        if(pn != 0) {
            nenner = pn;
        } else {
            nenner = 1;
        }
    }
    
    std::string Bruch::toString() const {
        return std::to_string(zaehler) + "/" + std::to_string(nenner);
    }

    void Bruch::add(const Bruch bruch) {
        zaehler = zaehler * bruch.nenner + bruch.zaehler * nenner;
        nenner = nenner * bruch.nenner;
        normalisiere();
    }

    void Bruch::sub(const Bruch bruch) {
        zaehler = zaehler * bruch.nenner - bruch.zaehler * nenner;
        nenner = nenner * bruch.nenner;
        normalisiere();
    }

    void Bruch::mult(const Bruch bruch) {
        zaehler*=bruch.zaehler;
        nenner*=bruch.nenner;
        normalisiere();
    }

    void Bruch::div(const Bruch bruch) {
        zaehler*=bruch.nenner;
        zaehler*=bruch.zaehler;
        normalisiere();
    }

    void Bruch::kuerze() {
        int a = ggt(zaehler, nenner);
        zaehler/=a;
        nenner/=a;
    }

    void Bruch::normalisiere() {
        kuerze();
        if(nenner<0) {
            nenner*=-1;
            zaehler*=-1;
        }
    }

    int Bruch::ggt(int a, int b) {
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

