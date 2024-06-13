#include <iostream>

class Bool
{
    bool t;
public:
    Bool(const bool pt): t(pt)
    {
    }
    bool getT() const
    {
        return t;
    }
};

Bool operator*(const Bool a, const Bool b) 
{
    return Bool(a.getT() && b.getT());
}
Bool operator+(const Bool a, const Bool b) 
{
    return Bool(a.getT() || b.getT());
}
Bool operator-(const Bool a) 
{
    return Bool(!(a.getT()));
}

std::ostream& operator<<(std::ostream& s, Bool b)
{
    if(b.getT()){
        s << "True";
    } else {
        s << "False";
    }
    
    return s;
}



/* hier die Operatoren
   * (logisches Und)
   + (logisches Oder)
   - (logisches Nicht)
   << (Ausgabe)
   als freie Funktionen einfuegen */



int main()
{
    // statt
    bool w1 = true;
    bool w2 = false;
    bool w3 = false;
    std::cout << (w1&&(w2||(!w3))) << '\n';

    // kann man auch folgendes schreiben:

    Bool b1(true);
    Bool b2(false);
    Bool b3(false);
    std::cout << b1*(b2+(-b3)) << '\n';

    return 0;
}