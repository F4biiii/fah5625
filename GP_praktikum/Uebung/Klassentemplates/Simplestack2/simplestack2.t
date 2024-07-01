#ifndef SIMPLESTACK2_T
#define SIMPLESTACK2_T
#include <cassert>

template<typename T, int maxSize>
class SimpleStack2
{
public:
    // inline defined methods
    bool empty() const
    {
        return number == 0;
    }
    bool full() const
    {
        return number == maxSize;
    }
    auto size() const
    {
        return number;
    }
    void clear()
    {
        number = 0;
    }

    // precondition for top and pop: stack is not empty
    const T& top() const;        // return element on top of stack
    void pop();                  // delete element on top of stack

    // precondition for push: stack is not full
    void push(const T& x);       // push element on top of stack

private:
    int number {0};              // number of element is the stack
    T array[maxSize];            // container for the elements
};

// implementations of top, pop, push
template<typename T, int m>
const T& SimpleStack2<T, m>::top() const
{
    assert(!empty());
    return array[number-1];
}
template<typename T, int m>
void SimpleStack2<T, m>::pop()
{
    assert(!empty());
    --number;
}
template<typename T, int m>
void SimpleStack2<T, m>::push(const T& x)
{
    assert(!full());
    array[number++] = x;
}

#endif
