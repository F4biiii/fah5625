#include "simplestack1.t"
#include <iostream>
using namespace std;

int main()
{
    SimpleStack1<int> an_int_stack;
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
    cout << "\n\n";

    SimpleStack1<double> a_double_stack;
    double d {1.00234};

    while (!a_double_stack.full())   // fill stack
    {
        d = 1.1 * d;
        a_double_stack.push(d);
    }

    // a_double_stack.push(1099.986); // error: stack is full

    cout << "pop 4 elements:\n";
    for (int j = 0; j < 4; ++j)
    {
        cout << a_double_stack.top() << '\t';
        a_double_stack.pop();
    }
    cout << "\n\n";

    cout << "remaining: " << a_double_stack.size() << " elements\n\n";

    cout << "clear stack\n";
    a_double_stack.clear();
    cout << "remaining: " << a_double_stack.size() << " elements\n";

    // a_double_stack.pop(); // error: stack is empty
}
