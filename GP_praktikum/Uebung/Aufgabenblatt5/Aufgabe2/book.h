#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
private:
    std::string title;
public:
    Book(const std::string pTitle) {
        title = pTitle;
    }

    std::string getTitle() const {
        return title;
    }
};

#endif