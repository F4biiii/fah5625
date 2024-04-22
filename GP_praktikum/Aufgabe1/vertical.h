#ifndef VERTICAL_H
#define VERTICAL_H

#include "ufosim.h"

#include <string>
#include <vector>


class Vertical
{
private:
    static const std::string type;
    std::string id;
    Ufosim* sim;
public:
    // constructor
    Vertical(const std::string& pId);
    // destructor
    ~Vertical();

    // getter
    static std::string getType();
    const std::string& getId() const;
    std::vector<float> getPosition() const;
    float getFtime() const;
    // functions
    void flyToDest(const float x, const float y, const float height, const int speed) const;
    static float angle(const float x1, const float y1, const float x2, const float y2);
    };

#endif
