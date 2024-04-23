#ifndef VERTICAL_H
#define VERTICAL_H

#include "ufosim.h"
#include "ufo.h"

#include <string>
#include <vector>


class Vertical : public Ufo
{
public:
    // constructor
    Vertical(const std::string& pId);
    // destructor
    ~Vertical();

    void flyToDest(const float x, const float y, const float height, const int speed) const override;
};

#endif
