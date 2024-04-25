#ifndef UFO_H
#define UFO_H

#include "ufosim.h"

#include <vector>

class Ufo
{
private:
    std::string id;
protected:    
    Ufosim* sim;
public:
    // constructor
    Ufo(const std::string& pId);
    // destructor
    virtual ~Ufo();

    // getter
    const std::string& getId() const;
    std::vector<float> getPosition() const;
    float getFtime() const;
    // methods
    virtual void flyToDest(const float x, const float y, const float height, const int speed) const = 0;
    static float angle(const float x1, const float y1, const float x2, const float y2);
};

#endif