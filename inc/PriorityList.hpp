/**
 * @autor Wojciech Gruszka
 * @email wojciech@gruszka.eu
 *
 */
#pragma once

class PriorityList {
    public:
        PriorityList();
        PriorityList(const PriorityList&);

        void pushFront(long pVal);
        void pushBack(long pVal);
        void insertBefore(long pVal, int pIdx);
        void insertAfter(long pVal);

        void removeById(int pIdx);
        void removeByValue(long pVal);
        void removeByRange(long pLVal,long pRVal);
        void removeDuplicates();

        T getById(int pIdx);
        T& operator[](int pIdx);
        int find(long pVal);

        int length();

        PriorityList operator+(const PriorityList& rhs) const;
        PriorityList operator-(const PriorityList& rhs) const;
        PriorityList& operator=(const PriorityList& rhs) const;
        bool operator==(const PriorityList& rhs) const;
    private:
      class Node {
      public:
        T data;
        unsigned int ref_cnt;
        Node* next;
        Node* prev;
        Node(const long d): data(d), ref_cnt(0), next(nullptr), prev(nullptr);
      };
      Node* head;
      Node* tail;
};
