#if !defined(RING_H)
#define RING_H

#include <iostream>
using namespace std;

//TODO: update comments

template <typename Key, typename Info>
class Ring
{
    struct Node
    {
        Key identifier;
        Info data;
        
        Node* next;
        Node* prev;
    };

    Node* head;
    unsigned long long count;
    bool isEmpty;
    
    void copyAllElements(const Ring<Key, Info>&);
    void init();
    
public:

    class Iterator
    {
        Node* n;
    public:
        Iterator() {};
        Iterator(const Iterator& rhs) {n = rhs.n;}
        Iterator(Node* r) { n = r;}
        ~Iterator() {}

        Iterator operator++() {n = n->next; return *this; }
        Iterator operator++(int) {Iterator oldPtr = *this; n = n->next; return oldPtr; }
        Iterator operator--() {n = n->prev; return *this; }
        Iterator operator--(int) {Iterator oldPtr = *this; n = n->prev; return oldPtr; }
        Node& operator*() { return *n; }
        Node* operator->() { return n; }
        bool operator==(const Iterator& rhs) const { return n == rhs.n; }
        bool operator!=(const Iterator& rhs) const { return n != rhs.n; }
    };

    class Const_Iterator
    {
        Node* n;
    public:
        Const_Iterator() {};
        Const_Iterator(const Const_Iterator& rhs) {n = rhs.n;}
        Const_Iterator(Node* r) { n = r;}
        ~Const_Iterator() {}

        Const_Iterator operator++() {n = n->next; return *this; }
        Const_Iterator operator++(int) {Const_Iterator oldPtr = *this; n = n->next; return oldPtr; }
        Const_Iterator operator--() {n = n->prev; return *this; }
        Const_Iterator operator--(int) {Const_Iterator oldPtr = *this; n = n->prev; return oldPtr; }
        const Node& operator*() { return *n; }
        const Node* operator->() { return n; }
        bool operator==(const Const_Iterator& rhs) const { return n == rhs.n; }
        bool operator!=(const Const_Iterator& rhs) const { return n != rhs.n; }
    };

    //TODO: Update those with erasure to be head.
    Iterator begin() const { return Iterator(head);}
    Const_Iterator cbegin() const { return Const_Iterator(head); }
    
    Ring();
    Ring(const Ring<Key, Info>&);
    ~Ring(); //NOTE(Stanisz13): complexity: O(n)

    
    bool isRingEmpty() const;
    unsigned long long getCount() const;

    void pushBack(const Key&, const Info&); //NOTE(Stanisz13): complexity: O(1);
    void pushBack(const Node&); //NOTE(Stanisz13): complexity: O(1);
    void popBack(); //NOTE(Stanisz13): complexity: O(n), finding 2nd last element takes time;
    
    void pushFront(const Key&, const Info&);
    void pushFront(const Node&);
    void popFront();

    void print() const;

    void clear();
    
    unsigned long long howManyElements(const Key&, const Info&) const;
    bool isElementPresent(const Key&, const Info&) const; 
    //NOTE(Stanisz13): Here we don't look for any specific Info.
    unsigned long long howManyElements(const Key&) const; 
    bool isElementPresent(const Key&) const;
    
    //NOTE(Stanisz13): This method will remove a first key after
    // 'keysToSkip' keys have been already found.
    void removeElements(const Key& k, int keysToSkip);

    //NOTE(Stanisz13): This method will insert an element consisting of Key and Info after
    // a 'afterWhat' key and after 'keysToSkip' ('afterWhat') keys have been already found.
    void insertElement(const Key& k, const Info& i, const Key& afterWhat,
                       int keysToSkip);
    

    //NOTE(Stanisz13): from sequence: [1, 2, 3, 4] using subsequence(1, 2)
    // will return [2, 3].
    Ring<Key, Info> subring(int startIndex, int endIndex) const;

    //TODO: how should this work?
    void append(const Ring<Key, Info>& o);

    void operator+=(const Ring<Key, Info>& o);
    void operator=(const Ring<Key, Info>& o);
};

#include "ring.cpp"

#endif
