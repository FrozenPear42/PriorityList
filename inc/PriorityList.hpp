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
        Node(const long d): data(d), ref_cnt(0), next(nullptr), prev(nullptr) {}
      };

      template <class Type>
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
        long& operator*() const {return node->data;}
      private:
        Node* node;
      };

      typedef ListIterator<long> iterator;
      typedef ListIterator<const long> constIterator;

      PriorityList(): head(nullptr), tail(nullptr), size(0) {}
      PriorityList(const PriorityList& pList);

      void pushFront(long pVal);
      void pushBack(long pVal);
      void insertBeforeIdx(long pVal, int pIdx);
      void insertAfterIdx(long pVal, int pIdx);

      void removeByIdx(int pIdx);
      void removeOneByValue(long pVal);
      void removeAllByValue(long pVal);
      void removeByRange(long pLVal,long pRVal);
      void removeAll();
      void removeDuplicates();

      long getById(int pIdx) const;
      long& operator[](int pIdx) const;
      int find(long pVal) const;

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

  private:
      Node* head;
      Node* tail;
      int size;
};
