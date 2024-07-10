#ifndef BOOKMAP_H
#define BOOKMAP_H

#include "book.h"
#include <string>
#include <map>

class Bookmap
{

private:
    std::map<int, Book>* aMap;

public:
    Bookmap(); 
    ~Bookmap();
    void bookInput(const int ISB, const std::string pTitle);
    void deleteElement(const int ISB);
    std::string getContent() const;
};

Bookmap::Bookmap() 
{
    aMap = new std::map<int, Book>;
}
Bookmap::~Bookmap() 
{
    delete aMap;
}

void Bookmap::bookInput(const int ISB, const std::string pTitle) 
{
    Book aBook(pTitle);
    aMap->insert({ISB, aBook});
}

void Bookmap::deleteElement(const int ISB) 
{
    aMap->erase(ISB);
}

std::string Bookmap::getContent() const
{
    std::string content;
    for(auto iter = aMap->begin(); iter != aMap->end(); iter++) 
    {
        if(iter == std::prev(aMap->end())) {
            content += std::to_string(iter->first) + ": " + iter->second.getTitle();
        } else {
            content += std::to_string(iter->first) + ": " + iter->second.getTitle() + ", ";
        }
    }
    return content;
}

#endif