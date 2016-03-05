/**
 * @autor Wojciech Gruszka
 * @email wojciech@gruszka.eu
 *
 */
#pragma once
#include <iterator>

class PriorityList {
  public:

      class Node {
      public:
        long data;
        unsigned int ref_cnt;
        Node* next;
        Node* prev;
        Node(long d): data(d), ref_cnt(0), next(nullptr), prev(nullptr) {}
        Node(long d, unsigned int cnt): data(d), ref_cnt(cnt), next(nullptr), prev(nullptr) {}
      };

      template <class Type, class NType>
      class ListIterator : public std::iterator<std::bidirectional_iterator_tag, long, std::ptrdiff_t, Type*, Type&> {
      public:
        ListIterator(Node* pNode): node(pNode) {}
        /* TODO: Overflow check */
        ListIterator& operator++() {node = node->next; return *this;}
        ListIterator operator++(int) {ListIterator tmp(*this); operator++(); return tmp;}
        ListIterator& operator--() {node = node->prev; return *this;}
        ListIterator operator--(int) {ListIterator tmp(*this); operator--(); return tmp;}
        bool operator==(const ListIterator& rhs) {return node == rhs.node;}
        bool operator!=(const ListIterator& rhs) {return node != rhs.node;}
        Type& operator*() const {return node->data;}
        NType* operator->() const { return node;}
      private:
        Node* node;
      };

      typedef ListIterator<long, Node> iterator;
      typedef ListIterator<const long, const Node> constIterator;

      PriorityList(): mHead(nullptr), mTail(nullptr), mSize(0) {}
      PriorityList(const PriorityList& pList);

      void pushFront(long pVal);
      void pushBack(long pVal);
      void insertBeforeIdx(long pVal, int pIdx);//TODO
      void insertAfterIdx(long pVal, int pIdx);//TODO

      void removeByIdx(int pIdx);
      void removeOneByValue(long pVal);
      void removeAllByValue(long pVal);
      void removeByRange(long pLVal,long pRVal);
      void removeAll();
      void removeDuplicates();

      long getByIdx(int pIdx);
      long& operator[](int pIdx);
      int find(long pVal);

      PriorityList::iterator begin() const;
      PriorityList::iterator end() const;
      PriorityList::constIterator cBegin() const;
      PriorityList::constIterator cEnd() const;

      int length() const;

      PriorityList operator+(const PriorityList& rhs) const;
      PriorityList& operator +=(const PriorityList& rhs);
      PriorityList operator-(const PriorityList& rhs) const;
      PriorityList operator-=(const PriorityList& rhs);
      PriorityList& operator=(const PriorityList& rhs);
      bool operator==(const PriorityList& rhs) const;

      friend std::ostream& operator<<(std::ostream& out, PriorityList& pList);

  private:
      Node* mHead;
      Node* mTail;
      int mSize;

      void pushFirstRef(long pData, unsigned int pRefCnt);
      void pushFrontRef(long pData, unsigned int pRefCnt);
      void pushBackRef(long pData, unsigned int pRefCnt);

      void sortNearNode(Node* pNode);
      Node* removeElement(Node* pNode);
};
