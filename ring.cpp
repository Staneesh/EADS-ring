#include "ring.h"
#define HERE cout<<"HERE"<<endl;
//NOTE(Stanisz13): PRIVATE

template <typename Key, typename Info>
void Ring<Key, Info>::init()
{
    head = new Node;
    count = 0;
    head->next = head;
    head->prev = head;
    isEmpty = 1;
}

template <typename Key, typename Info>
void Ring<Key, Info>::copyAllElements(const Ring<Key, Info>& other)
{
    init();

    if (other.isEmpty) return;
    
    Const_Iterator it = other.cbegin();
    do
    {
        pushBack(*it++);
    }
    while(it != other.cbegin());
}

//NOTE(Stanisz13): PUBLIC

template <typename Key, typename Info>
Ring<Key, Info>::Ring()
{
    init();
}


template <typename Key, typename Info>
Ring<Key, Info>::~Ring()
{
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& other)
{
    copyAllElements(other);
    return;
}

template <typename Key, typename Info>
void Ring<Key, Info>::pushBack(const Key& k, const Info& i)
{
    if (isEmpty)
    {
        head->data = i;
        head->identifier = k;

        isEmpty = 0;
        
        return;
    }


    Node* n = new Node;
    n->identifier = k;
    n->data = i;
    
    Node* oldPrev = head->prev;

    head->prev = n;
    n->next = head;
    oldPrev->next = n;
    n->prev = oldPrev;                       
}

template <typename Key, typename Info>
void Ring<Key, Info>::pushBack(const Node& o)
{
    pushBack(o.identifier, o.data);
}

template <typename Key, typename Info>
void Ring<Key, Info>::popBack()
{
    if (isEmpty) return;

    //NOTE: At least one element, so i will alwaus end up with a smaller structure.
    --count;

    //NOTE: exactly one element.
    if (head->next == head)
    {
        isEmpty = 1;
        return;
    }

    auto oldPrev = head->prev;
    auto newPrev = oldPrev->prev;

    head->prev = newPrev;
    newPrev->next = head;

    delete oldPrev;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::isRingEmpty() const
{
    return isEmpty;
}

template <typename Key, typename Info>
unsigned long long Ring<Key, Info>::getCount() const
{
    return count;
}

template <typename Key, typename Info>
void Ring<Key, Info>::pushFront(const Key& k, const Info& i)
{
    if (isEmpty)
    {
        head->data = i;
        head->identifier = k;

        isEmpty = 0;
        
        return;
    }

    Node* n = new Node;
    n->identifier = k;
    n->data = i;

    Node* oldNext = head->next;

    head->next = n;
    n->prev = head;
    oldNext->prev = n;
    n->next = oldNext;

    ++count;
}

template <typename Key, typename Info>
void Ring<Key, Info>::pushFront(const Node& o)
{
    pushFront(o.identifier, o.data);
}

template <typename Key, typename Info>
void Ring<Key, Info>::popFront()
{
    if (isEmpty) return;

    //NOTE: At least one element, so i will alwaus end up with a smaller structure.
    --count;

    //NOTE: exactly one element.
    if (head->next == head)
    {
        isEmpty = 1;
        return;
    }

    auto oldNext = head->next;
    auto newNext = oldNext->next;

    head->next = newNext;
    newNext->prev = head;

    delete oldNext;
}


template <typename Key, typename Info>
unsigned long long Ring<Key, Info>::howManyElements(const Key& k, const Info& i) const
{
}

template <typename Key, typename Info>
bool Ring<Key, Info>::isElementPresent(const Key& k, const Info& i) const
{
}

template <typename Key, typename Info>
unsigned long long Ring<Key, Info>::howManyElements(const Key& k) const
{
}

template <typename Key, typename Info>
bool Ring<Key, Info>::isElementPresent(const Key& k) const
{
}

template <typename Key, typename Info>
void Ring<Key, Info>::removeElements(const Key& k, int keysToSkip)
{
}

template <typename Key, typename Info>
void Ring<Key, Info>::print() const
{
    if (isEmpty)
    {
        cout<<"Ring is empty."<<endl;
        return;
    }
    
    cout<<"Ring contains:"<<endl;
    Const_Iterator it = cbegin();
    do
    {
        cout<<"    Key:"<<it->identifier<<"  Info:"<<it->data;

        if (it == cbegin())
        {
            cout<<"  <---- HEAD";
        }
        
        cout<<endl;
        ++it;
    }
    while(it != cbegin());

    cout<<endl;
}

template <typename Key, typename Info>
void Ring<Key, Info>::clear()
{
    while(isRingEmpty() == 0)
    {
        popBack();
    }
}

template <typename Key, typename Info>
void Ring<Key, Info>::insertElement(const Key& k, const Info& i, const Key& afterWhat,
                   int keysToSkip)
{
}

template <typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::subring(int startIndex, int endIndex) const
{
}

template <typename Key, typename Info>
void Ring<Key, Info>::append(const Ring<Key, Info>& o)
{
    
}

template <typename Key, typename Info>
void Ring<Key, Info>::operator+=(const Ring<Key, Info>& o)
{
    append(o);
}

template <typename Key, typename Info>
void Ring<Key, Info>::operator=(const Ring<Key, Info>& o)
{
    copyAllElements(o);
}
