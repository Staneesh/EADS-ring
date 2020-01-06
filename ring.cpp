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
}

template <typename Key, typename Info>
void Ring<Key, Info>::copyAllElements(const Ring<Key, Info>& other)
{
    init();

    if (other.isEmpty()) return;
    
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
    clear();
    delete head;
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
    if (count == 0)
    {
        head->data = i;
        head->identifier = k;
        ++count;
           
        return;
    }
    ++count;
    

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
void Ring<Key, Info>::pushBack(const Iterator& i)
{
    pushBack(i->identifier, i->data);
}

template <typename Key, typename Info>
void Ring<Key, Info>::pushBack(Const_Iterator& i)
{
    pushBack(i->identifier, i->data);
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Node Ring<Key, Info>::popBack()
{
    if (count == 0) return Node();

    //NOTE: At least one element, so i will alwaus end up with a smaller structure.
    --count;

    //NOTE: exactly one element.
    if (head->next == head)
    {
        return *head;
    }

    auto oldPrev = head->prev;
    auto newPrev = oldPrev->prev;

    head->prev = newPrev;
    newPrev->next = head;

    auto res =  *oldPrev;
    delete oldPrev;

    return res;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::isEmpty() const
{
    return count == 0;
}

template <typename Key, typename Info>
unsigned long long Ring<Key, Info>::getCount() const
{
    return count;
}

template <typename Key, typename Info>
void Ring<Key, Info>::pushFront(const Key& k, const Info& i)
{
    if (count == 0)
    {
        head->data = i;
        head->identifier = k;
        ++count;
        
        return;
    }

    ++count;
    
    Node* n = new Node;
    n->identifier = k;
    n->data = i;

    Node* oldNext = head->next;

    head->next = n;
    n->prev = head;
    oldNext->prev = n;
    n->next = oldNext;
}

template <typename Key, typename Info>
void Ring<Key, Info>::pushFront(const Node& o)
{
    pushFront(o.identifier, o.data);
}


template <typename Key, typename Info>
void Ring<Key, Info>::pushFront(const Iterator& o)
{
    pushFront(o->identifier, o->data);
}


template <typename Key, typename Info>
void Ring<Key, Info>::pushFront(Const_Iterator& o)
{
    pushFront(o->identifier, o->data);
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Node Ring<Key, Info>::popFront()
{
    if (count == 0) return Node();

    //NOTE: At least one element, so i will alwaus end up with a smaller structure.
    --count;

    //NOTE: exactly one element.
    if (head->next == head)
    {
        return *head;
    }

    auto oldNext = head->next;
    auto newNext = oldNext->next;

    head->next = newNext;
    newNext->prev = head;

    auto res = *oldNext;
    delete oldNext;
    return res;
}


template <typename Key, typename Info>
unsigned long long Ring<Key, Info>::howManyElements(const Key& k, const Info& i) const
{
    unsigned long long res = 0;
    if (isEmpty()) return res;

    
    Const_Iterator it = cbegin();

    do
    {
        if (it->identifier == k && it->data == i) ++res;

        ++it;
    }
    while(it != cbegin());

    return res;        
}

template <typename Key, typename Info>
bool Ring<Key, Info>::isElementPresent(const Key& k, const Info& i) const
{
    return howManyElements(k, i) > 0;
}


template <typename Key, typename Info>
bool Ring<Key, Info>::isElementPresent(const Const_Iterator& i) const
{
    if (i.getH() != head) return 0;

    if (isEmpty()) return 0;

    
    Const_Iterator it = cbegin();

    do
    {
        if (it == i) return 1;

        ++it;
    }
    while(it != cbegin());

    return 0;           
}


template <typename Key, typename Info>
bool Ring<Key, Info>::isElementPresent(const Const_Iterator& s, const Const_Iterator& i) const
{
    if (i.getH() != head || s.getH() != head) return 0;

    if (isEmpty()) return 0;

    
    Const_Iterator it = s;

    do
    {
        if (it == i) return 1;

        ++it;
    }
    while(it != cbegin());

    return 0;           
}

template <typename Key, typename Info>
unsigned long long Ring<Key, Info>::howManyElements(const Key& k) const
{
    unsigned long long res = 0;
    if (isEmpty()) return res;

    
    Const_Iterator it = cbegin();

    do
    {
        if (it++->identifier == k) ++res;
    }
    while(it != cbegin());

    return res;    
}

template <typename Key, typename Info>
bool Ring<Key, Info>::isElementPresent(const Key& k) const
{
    return howManyElements(k) > 0;
}

template <typename Key, typename Info>
void Ring<Key, Info>::removeElement(const Key& k, int keysToSkip)
{
    if (isEmpty()) return;

    if (keysToSkip < 0) keysToSkip = 0;
    
    Iterator it = begin();

    int keysAlreadySeen = 0;
    
    do
    {
        if (it++->identifier == k)
        {
            if (keysAlreadySeen++ >= keysToSkip)
            {
                --count;
                
                auto oldPrev = it->prev;

                if (oldPrev == head)
                {
                    if (count == 1)
                    {
                        return;
                    }

                    head = head->next;
                }
                
                auto newPrev = oldPrev->prev;
                
                newPrev->next = &*it;
                it->prev = newPrev;

                delete oldPrev;
                
                return;
            }
        }
    }
    while(it != begin());
}

template <typename Key, typename Info>
void Ring<Key, Info>::removeElement(Iterator& i)
{
    if (i.getH() != head) return;
    
    if (isEmpty()) return;

    Iterator it = begin();
    
    do
    {
        if (it++ == i)
        {
            auto oldPrev = it->prev;

            --count;
            
            if (oldPrev == head)
            {
                if (count == 1)
                {
                    return;
                }

                head = head->next;
            }
                
            auto newPrev = oldPrev->prev;
                
            newPrev->next = &*it;
            it->prev = newPrev;

            delete oldPrev;
            
            return;
        }
        
    }
    while(it != begin());
}

template <typename Key, typename Info>
void Ring<Key, Info>::removeElements(const Key& k)
{
    if (isEmpty()) return;
    
    Iterator it = begin();

    do
    {
        if (it++->identifier == k)
        {
            --count;

            bool itToMove = 0;
            
            auto oldPrev = it->prev;

            if (oldPrev == head)
            {
                if (count == 1)
                {
                    return;
                }

                head = head->next;
                itToMove = 1;
            }
                
            auto newPrev = oldPrev->prev;
                
            newPrev->next = &*it;
            it->prev = newPrev;

            if (itToMove) ++it;

            delete oldPrev;
        }
    }
    while(it != begin());
}

template <typename Key, typename Info>
void Ring<Key, Info>::print() const
{
    if (count == 0)
    {
        cout<<"Ring is empty."<<endl;
        return;
    }
    
    cout<<"Ring (of size "<<count<<") contains:"<<endl;
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
    while(isEmpty() == 0)
    {
        popBack();
    }
}

template <typename Key, typename Info>
void Ring<Key, Info>::insertElement(const Key& k, const Info& i, const Key& afterWhat,
                   int keysToSkip)
{
    if (isEmpty()) return;

    if (keysToSkip < 0) keysToSkip = 0;
    
    Iterator it = begin();

    int keysAlreadySeen = 0;
    
    do
    {
        if (it++->identifier == afterWhat)
        {
            if (keysAlreadySeen++ >= keysToSkip)
            {
                Node* n = new Node;
                n->identifier = k;
                n->data = i;

                auto oldPrev = it->prev;

                oldPrev->next = n;
                n->prev = oldPrev;
                it->prev = n;
                n->next = &*it;

                ++count;
                return;
            }
        }
    }
    while(it != begin());
}

template <typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::subring(int startIndex, int endIndex) const
{
    Ring<Key, Info> res;

    if (isEmpty()) return res;

    if ((unsigned long long)startIndex >= count || endIndex < 0) return res;
    
    if (startIndex < 0) startIndex = 0;
    if ((unsigned long long)endIndex >= count) endIndex = count - 1;
    if (startIndex > endIndex) return res;

    Const_Iterator it = cbegin();
    int i = 0;
    do
    {
        if (i >= startIndex && i <= endIndex)
        {
            res.pushBack(*it);
        }
        ++it;
        ++i;
    }
    while(it != cbegin());

    return res;
}

template <typename Key, typename Info>
void Ring<Key, Info>::reverse()
{
    Ring< Key, Info> tmp;

    while (isEmpty() == 0)
    {
        tmp.pushBack(popBack());
    }

    while (tmp.isEmpty() == 0)
    {
        pushFront(tmp.popBack());
    }
}

template <typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::subring(const Const_Iterator& start, const Const_Iterator& end) const
{
    Ring<Key, Info> res;

    if (isEmpty()) return res;

    if (start.getH() != head || end.getH() != head) return res;

    if (isElementPresent(start, end) == 0) return res;
    
    Const_Iterator it = start;
    do
    {
        res.pushBack(*it++);
    }
    while(it != end);

    return res;
}

template <typename Key, typename Info>
void Ring<Key, Info>::append(const Ring<Key, Info>& o)
{
    if (o.isEmpty()) return;
    
    Const_Iterator it = o.cbegin();

    do
    {
        pushBack(*it);
        ++it;
    }
    while (it != o.cbegin());
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
