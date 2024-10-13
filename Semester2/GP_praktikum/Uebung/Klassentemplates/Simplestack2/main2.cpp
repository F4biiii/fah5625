#include "simplestack2.t"
#include <iostream>
using namespace std;

int main()
{
    SimpleStack2<int,100> an_int_stack;
    int i {100};

    while (!an_int_stack.full())
    {
        an_int_stack.push(i++);     // fill stack with 100, 101, ...
    }

    cout << "number:           " << an_int_stack.size() << '\n';
    cout << "top element:      " << an_int_stack.top() << "\n\n";

    cout << "pop all elements: \n";

    int j = 0;
    while (!an_int_stack.empty())
    {
        i = an_int_stack.top();
        an_int_stack.pop();
        if (j == 4)
        {
            cout << i << '\n';
            j = 0;
        }
        else
        {
            cout << i << '\t';
            j++;
        }
    }
    cout << '\n';
}

