#if !defined(RING_H)
#define RING_H

#include <iostream>
using namespace std;

//TODO: handle iterators as args
//TODO: handle improper iterators as params
//TODO: use subring in split.

//NOTE: This structure is a doubly-linked ring without a sentinel.
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
    
    void copyAllElements(const Ring<Key, Info>&);
    void init();
    
public:

    class Iterator
    {
        Node* n;
        Node* h;
    public:
        Iterator() {};
        Iterator(const Iterator& rhs) {n = rhs.n; h = rhs.h;}
        Iterator(Node* rhs) {n = rhs; h = rhs;}
        ~Iterator() {}

        Iterator operator++() {n = n->next; return *this; }
        Iterator operator++(int) {Iterator oldPtr = *this; n = n->next; return oldPtr; }
        Iterator operator--() {n = n->prev; return *this; }
        Iterator operator--(int) {Iterator oldPtr = *this; n = n->prev; return oldPtr; }
        Node& operator*() { return *n; }
        Node* operator->() { return n; }
        bool operator==(const Iterator& rhs) const { return (n == rhs.n); }
        bool operator!=(const Iterator& rhs) const { return (n != rhs.n); }
    };

    class Const_Iterator
    {
        Node* n;
        Node* h;
    public:
        Const_Iterator() {};
        Const_Iterator(const Const_Iterator& rhs) {n = rhs.n; h = rhs.h;}
        Const_Iterator(Node* rhs) {n = rhs; h = rhs;}
        ~Const_Iterator() {}

        Const_Iterator operator++() {n = n->next; return *this; }
        Const_Iterator operator++(int) {Const_Iterator oldPtr = *this; n = n->next; return oldPtr; }
        Const_Iterator operator--() {n = n->prev; return *this; }
        Const_Iterator operator--(int) {Const_Iterator oldPtr = *this; n = n->prev; return oldPtr; }
        const Node& operator*() { return *n; }
        const Node* operator->() { return n; }
        bool operator==(const Const_Iterator& rhs) const { return (n == rhs.n); }
        bool operator!=(const Const_Iterator& rhs) const { return (n != rhs.n); }
    };

    Iterator begin() const { return Iterator(head);}
    Const_Iterator cbegin() const { return Const_Iterator(head); }
    
    Ring();
    Ring(const Ring<Key, Info>&); //NOTE: complexity: O(n)
    ~Ring(); //NOTE: complexity: O(n). Performs clear and frees 'head' memory.

    
    bool isEmpty() const;
    unsigned long long getCount() const;

    void pushBack(const Key&, const Info&); //NOTE: complexity: O(1);
    void pushBack(const Node&); //NOTE: complexity: O(1);
    void popBack(); //NOTE: complexity: O(1) thanks to 'prev' pointer

    //NOTE: complexities equal to the ones above 
    void pushFront(const Key&, const Info&);
    void pushFront(const Node&);
    void popFront();

    void print() const;

    //NOTE: clears the structure by consecutive popBacks.
    void clear();
    
    //NOTE: returns 1 iff there exists an element of a given Key AND Info. 0 otherwise.
    bool isElementPresent(const Key&, const Info&) const; 
    //NOTE: counts elements of a given Key AND Info.
    unsigned long long howManyElements(const Key&, const Info&) const;

    //NOTE: Here we don't look for any specific Info.
    unsigned long long howManyElements(const Key&) const; 
    bool isElementPresent(const Key&) const;
    
    //NOTE: This method will remove a first key after
    // 'keysToSkip' keys have been already found.
    void removeElement(const Key&, int keysToSkip);

    //NOTE: this method will remove ALL nodes of a given Key. 
    void removeElements(const Key&);
    
    //NOTE: This method will insert an element consisting of Key and Info after
    // a 'afterWhat' key and after 'keysToSkip' ('afterWhat') keys have been already found.
    void insertElement(const Key& k, const Info& i, const Key& afterWhat,
                       int keysToSkip);
    

    //NOTE: from ring: [1, 2, 3, 4] using subring(1, 2)
    // will return [2, 3].
    Ring<Key, Info> subring(int startIndex, int endIndex) const;

    //NOTE: pushes back all nodes from o to this structure.
    void append(const Ring<Key, Info>& o);

    void operator+=(const Ring<Key, Info>& o);
    void operator=(const Ring<Key, Info>& o);
};

#include "ring.cpp"

#endif
