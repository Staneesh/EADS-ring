#include <iostream>
#include "ring.h"

using namespace std;

template<typename Key, typename Info>
void split(const Ring<Key, Info>& source, bool direction,
           Ring<Key, Info>& result1, int sequence1, int rep1,
           Ring<Key, Info>& result2, int sequence2, int rep2)
{
    result1.clear();
    result2.clear();

    if (source.isEmpty()) return;

    if (sequence1 < 0) sequence1 = 0;
    if (sequence2 < 0) sequence2 = 0;
    if (rep1 < 0) rep1 = 0;
    if (rep2 < 0) rep2 = 0;

    auto copy = source;

    if (direction == 0) copy.reverse();
    
    int steps[2] = {sequence1, sequence2};
    int now = 0;
    int repeated1 = 0;
    int repeated2 = 0;

    if (rep1 == 0 || sequence1 == 0) now ^= 1;

    int idx = 0;
    
    while (1)
    {
        if (now == 0) result1 += copy.subring(idx, idx + steps[now] - 1);
        else result2 += copy.subring(idx, idx + steps[now] - 1);

        idx += steps[now];
        if ((unsigned long long)idx > copy.getCount())
        {
            return;
        }
        if (now)
        {
            ++repeated2;
            if (repeated1 >= rep1)
            {
                now ^= 1;
            }
        }
        else
        {
            ++repeated1;
            if (repeated2 >= rep2)
            {
                now ^= 1;
            }
        }

        if (repeated1 >= rep1 && repeated2 >= rep2)
        {
            return;
        }
        
        now ^= 1;        
    }
}
           


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

    
    while (ringOfBooks.isEmpty() == 0)
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

    int keyToFind = 6;
    string infoToFind = "eee";
    
    cout<<"Is element of key ["<<keyToFind<<"] and info ["<<infoToFind<<"] present in the second ring of books?"<<endl;
    cout<<(ringOfBooks2.isElementPresent(keyToFind, infoToFind) ? "YES" : "NO" )<< endl;

    int keyToInsert = 2;
    string infoToInsert = "fff";
    int afterWhat = 13;
    
    cout<<"Inserting key ["<<keyToInsert<<"] and info ["<<infoToInsert<<"] after key ["<<afterWhat<<"]..."<<endl;
    ringOfBooks2.insertElement(keyToInsert, infoToInsert, afterWhat, 0);
    ringOfBooks2.print();

    keyToInsert = 3;
    infoToInsert = "fff";
    afterWhat = 0;

    cout<<"Inserting key ["<<keyToInsert<<"] and info ["<<infoToInsert<<"] after key ["<<afterWhat<<"]..."<<endl;
    ringOfBooks2.insertElement(keyToInsert, infoToInsert, afterWhat, 0);
    ringOfBooks2.print();

    keyToInsert = 4;
    infoToInsert = "fff";
    afterWhat = 14;

    cout<<"Inserting key ["<<keyToInsert<<"] and info ["<<infoToInsert<<"] after key ["<<afterWhat<<"]..."<<endl;
    ringOfBooks2.insertElement(keyToInsert, infoToInsert, afterWhat, 0);
    ringOfBooks2.print();

    int keyToRemove = 6;
    int keysToSkip = 0;
    
    cout<<"Removing key ["<<keyToRemove<<"] after keys to skip ["<<keysToSkip<<"] have been found..."<<endl;
    ringOfBooks2.removeElement(keyToRemove,keysToSkip);
    ringOfBooks2.print();

    cout<<"Adding new nodes with head data..."<<endl;
    ringOfBooks2.pushBack(5, "eee");
    ringOfBooks2.pushBack(5, "eee");
    ringOfBooks2.pushBack(5, "eee");
    ringOfBooks2.pushBack(5, "eee");
    ringOfBooks2.print();

    keyToRemove = 5;
    
    cout<<"Removing ALL keys ["<<keyToRemove<<"]..."<<endl;
    ringOfBooks2.removeElements(keyToRemove);
    ringOfBooks2.print();

    int fromIndex = 1;
    int toIndex = 4;
    cout<<"Creating subring from ["<<fromIndex<<"] to ["<<toIndex<<"]..."<<endl;
    auto sub = ringOfBooks2.subring(fromIndex, toIndex);
    sub.print();

    cout<<"Appending subring to the original ring..."<<endl;
    ringOfBooks2 += sub;
    ringOfBooks2.print();

    Ring<int, string> r1, r2;
    bool dir = 1;
    int seq1 = 1, seq2 = 1;
    int rep1 = 2, rep2 = 2;

    cout<<"Splitting: dir:"<<dir<<" seq1:"<<seq1<<" rep1:"<<rep1<<" seq2:"<<seq2<<" rep2:"<<rep2<<endl;
    split(ringOfBooks2, dir, r1, seq1, rep1, r2, seq2, rep2);
    
    cout<<"R1:"<<endl;
    r1.print();
    cout<<"R2:"<<endl;
    r2.print();

#if 1
    cout<<"ringOfBooks2:"<<endl;
    ringOfBooks2.print();
    cout<<"Removing head..."<<endl;
    Ring<int, string>::Iterator it = ringOfBooks2.begin();
    ringOfBooks2.removeElement(it);
    ringOfBooks2.print();

    cout<<"Trying poorly to remove head..."<<endl;
    it = r1.begin();
    ringOfBooks2.removeElement(it);
    ringOfBooks2.print();
        
    cout<<"Reversing..."<<endl;
    ringOfBooks2.reverse();
    ringOfBooks2.print();
#endif    
    return 0;
}
