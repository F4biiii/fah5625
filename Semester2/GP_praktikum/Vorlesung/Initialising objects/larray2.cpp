#include <cassert>
#include <iostream>
#include "larray2.h"

Larray::Larray(const int pNumber)
{
    number = pNumber;
    ptr = new float[number];
    for (int i = 0; i < number; i++)
        ptr[i] = 0.0;
    std::cout << "  with constructor\n";
}
Larray::Larray(const Larray& larr)
{
    number = larr.number;
    ptr = new float[number];
    for (int i = 0; i < number; i++)
        ptr[i] = larr.ptr[i];
    std::cout << "  with copy constructor\n";
}
Larray::Larray(Larray&& larr)
{
    number = larr.number;
    ptr = larr.ptr;
    larr.ptr = nullptr;
    std::cout << "  with moving constructor\n";
}
Larray& Larray::operator=(const Larray& larr)
{
    number = larr.number;
    ptr = new float[number];
    for (int i = 0; i < number; i++)
        ptr[i] = larr.ptr[i];
    std::cout << "  with assignment operator\n";
    return *this;
}
float Larray::get_elem(const int i) const
{
    assert(i < number);
    return ptr[i];
}
void Larray::set_elem(const int i, const float e)
{
    assert(i < number);
    ptr[i] = e;
}
Larray::~Larray()
{
    delete[] ptr;
}

Larray makeALarray()
{
    Larray lar(1000);
    lar.set_elem(999, -1.5);
    return lar;
}

int main()
{
    std::cout << "constructing lar1:\n";
    Larray lar1(1000);
    lar1.set_elem(999, -1.5);
    //std::cout << "  lar1[999]: " << lar1.get_elem(999) << '\n';

    std::cout << "constructing lar2 from lar1:\n";
    Larray lar2(lar1);
    //std::cout << "  lar2[999]: " << lar2.get_elem(999) << '\n';

    std::cout << "constructing lar3 from lar2:\n";
    Larray lar3(0);
    lar3 = lar2;
    //std::cout << "  lar3[999]: " << lar3.get_elem(999) << '\n';

    std::cout << "constructing lar4:\n";
    Larray lar4(makeALarray());
    //std::cout << "  lar4[999]: " << lar4.get_elem(999) << '\n';
}
