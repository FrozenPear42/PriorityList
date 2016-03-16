/**
* @autor Wojciech Gruszka
* @email wojciech@gruszka.eu
*
*/
#pragma once
#include <iterator>
#include <stdexcept>

class PriorityList {
    friend std::ostream& operator<<(std::ostream& out, PriorityList& pList);
    class Node;
public:
    template <class Type, class NType> class ListIterator;
    
    typedef ListIterator<long, Node> iterator;
    typedef ListIterator<const long, const Node> constIterator;

    PriorityList(): mHead(nullptr), mTail(nullptr), mSize(0) {}
    PriorityList(const PriorityList& pList);
    PriorityList(std::initializer_list<long> pList);
    PriorityList& operator=(const PriorityList& rhs);

    void pushFront(long pVal);
    void pushBack(long pVal);
    void insert(long pVal, int pIdx);

    void removeByIdx(int pIdx);
    void removeOneByValue(long pVal);
    void removeAllByValue(long pVal);
    void removeByRange(long pLVal,long pRVal);
    void removeAll();
    void removeDuplicates();
    PriorityList unique();

    PriorityList& operator+=(const long pVal);
    PriorityList& operator-=(const long pVal);

    long getByIdx(int pIdx);
    long& operator[](int pIdx);
    int find(long pVal);
    PriorityList::iterator itFind(long pVal);


    PriorityList::iterator begin() const;
    PriorityList::iterator end() const;
    PriorityList::constIterator cBegin() const;
    PriorityList::constIterator cEnd() const;

    int length() const;

    PriorityList operator+(const PriorityList& rhs) const;
    PriorityList operator-(const PriorityList& rhs) const;
    PriorityList& operator +=(const PriorityList& rhs);
    PriorityList& operator-=(const PriorityList& rhs);
    bool operator==(const PriorityList& rhs) const;
    bool operator!=(const PriorityList& rhs) const;
private:
    Node* mHead;
    Node* mTail;
    int mSize;

    void internalInsert(long pData, int pIdx, unsigned int pRefCnt);
    void internalInsert(long pData, int pIdx);
    Node* removeElement(Node* pNode);
    void sortNearNode(Node* pNode);

    class Node {
    public:
        long data;
        unsigned int ref_cnt;
        Node* next;
        Node* prev;
        Node(long d): data(d), ref_cnt(0), next(nullptr), prev(nullptr) {}
        Node(long d, unsigned int cnt): data(d), ref_cnt(cnt), next(nullptr), prev(nullptr) {}
        bool operator>(const Node& rhs) {return ((ref_cnt == rhs.ref_cnt && data > rhs.data) || (ref_cnt > rhs.ref_cnt));}
        bool operator<(const Node& rhs) {return !operator>(rhs);}
    };

public:
    template <class Type, class NType>
    class ListIterator : public std::iterator<std::bidirectional_iterator_tag, long, std::ptrdiff_t, Type*, Type&> {
        friend class PriorityList;
        friend std::ostream& operator<<(std::ostream& out, PriorityList& pList);

    public:
        ListIterator(Node* pNode): node(pNode) {}
        ListIterator& operator++() {
            if(node == nullptr)
            throw std::out_of_range("Iterator out of range");
            node = node->next;
            return *this;
        }
        ListIterator& operator--() {
            if(node == nullptr)
            throw std::out_of_range("Iterator out of range");
            node = node->prev;
            return *this;
        }
        ListIterator operator++(int) {
            ListIterator tmp(*this);
            operator++();
            return tmp;
        }
        ListIterator operator--(int) {
            ListIterator tmp(*this);
            operator--();
            return tmp;
        }
        bool operator==(const ListIterator& rhs) {return node == rhs.node;}
        bool operator!=(const ListIterator& rhs) {return node != rhs.node;}
        Type& operator*() const {return node->data;}
    private:
        Node* node;
        NType* operator->() const { return node; }
        NType* getNode() const { return node; }
    };
};
