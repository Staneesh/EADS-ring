#include <iostream>
#include "ring.h"

using namespace std;



int main()
{
    Ring<int, string> ringOfBooks;

    ringOfBooks.pushBack(1, "aaa");
    ringOfBooks.pushBack(2, "bbb");
    ringOfBooks.pushBack(3, "ccc");
    ringOfBooks.pushBack(4, "ddd");
    
    Ring<int, string> ringOfBooks2(ringOfBooks);
    ringOfBooks2.print();

    cout<<"Clearing second ring of books..."<<endl;
    ringOfBooks2.clear();
    ringOfBooks2.print();

    cout<<endl;

    
    while (ringOfBooks.isRingEmpty() == 0)
    {
        cout<<"Popping back from the first ring..."<<endl;
        ringOfBooks.popBack();
        ringOfBooks.print();
    }

    cout<<"Pushing FRONT 10 times to the first ring..."<<endl;
    for (unsigned i = 0; i < 10; ++i)
    {
        ringOfBooks.pushFront(5 + i, "eee");
    }

    ringOfBooks.print();

    cout<<"Pushing BACK 10 times to the second ring..."<<endl;
    for (unsigned i = 0; i < 10; ++i)
    {
        ringOfBooks2.pushBack(5 + i, "eee");
    }

    ringOfBooks2.print();
    
        
    return 0;
}
