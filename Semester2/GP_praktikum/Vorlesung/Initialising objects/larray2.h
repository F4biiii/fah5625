#ifndef LARRAY2_H
#define LARRAY2_H

class Larray
{
private:
    int number;
    float *ptr;
public:
    Larray(const int pNumber);
    Larray(const Larray& larr);             // copy constructor
    Larray(Larray&& larr);                  // moving constructor
    Larray& operator=(const Larray& larr);  // assignment operator
    float get_elem(const int i) const;
    void set_elem(const int i, const float e);
    ~Larray();
};

#endif
