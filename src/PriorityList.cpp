/**
 * @autor Wojciech Gruszka
 * @email wojciech@gruszka.eu
 * @description PriorityList is an abstract list which tracs number of references tto
 * each of that list elements and sort itself to keep the most accessed items at the beggining.
 * As there may be many items with the same reference count, they are also sorted by value
 * for each reference count.
 * Methods that allows you to insert value at certain position do that, and than reoganise list
 * to match conceptual design. Thereisgarantee that insertevaluewill not get any further
 * than specified position.
 *
 */
#include <unordered_set>
#include <iostream>
#include "PriorityList.hpp"


PriorityList::PriorityList(const PriorityList& pList) : PriorityList() {
    operator+=(pList);
}

PriorityList::PriorityList(std::initializer_list<long> pList) : PriorityList() {
    for(auto it = pList.begin();it != pList.end(); ++it)
        internalInsert(*it, mSize, 0);
}

PriorityList& PriorityList::operator=(const PriorityList& rhs) {
    removeAll();
    operator+=(rhs);
    return *this;
}

/** Inserts specified value at the end of the list with reference counter
 equal zero. Than organise the list. If there were more items with reference
 counter equal to 0, there is no guarantee that this item will remain at the end of the list */
 */
void PriorityList::pushBack(long pVal) {
    internalInsert(pVal, mSize, 0);
}

void PriorityList::pushFront(long pVal) {
    internalInsert(pVal, 0);
}

void PriorityList::insert(long pVal, int pIdx) {
    internalInsert(pVal, pIdx);
}

/** Adds element at the end of the list */
PriorityList& PriorityList::operator+=(const long pVal) {
    pushBack(pVal);
    return (*this);
}

/* Removes specifued value from the list */
PriorityList& PriorityList::operator-=(const long pVal) {
    removeOneByValue(pVal);
    return (*this);
}


/** returns value at specified index, than increments thats value
 reference counter and reorganise the list */
long PriorityList::getByIdx(int pIdx) throw(std::out_of_range){
    return operator[](pIdx);
}

/** returns value at specified index, than increments thats value
 reference counter and reorganise the list */
long& PriorityList::operator[](int pIdx) throw(std::out_of_range) {
    if(pIdx < 0 || pIdx >= mSize)
        throw std::out_of_range("List index out of range");

    auto it = begin();
    for(int i = 0; i != pIdx; ++it, ++i);

    it->ref_cnt++;
    sortNearNode(it.getNode());
    return *it;
}
/** returns index of specified value or -1 if not found, than increments thats value
 reference counter and reorganise the list - there is not guarantee that this value
 will remain at returned index  */
int PriorityList::find(long pVal) {
    int i = 0;
    for(auto it = begin(); it != end(); ++it, ++i)
        if(*it == pVal) {
            it->ref_cnt++;
            sortNearNode(it.getNode());
            return i;
        }
    return -1;
}

/** returns iterator to specified value or to end if value not found, than increments thats value
 reference counter and reorganise the list iterator is pointing found value so no matters how the
 list will be reorganised returned iterator will stil point found value */
PriorityList::iterator PriorityList::itFind(long pVal) {
    auto it = begin();
    for(; it != end(); ++it)
        if(*it == pVal) {
            it->ref_cnt++;
            sortNearNode(it.getNode());
            return it;
        }
    return it;
}


void PriorityList::removeByIdx(int pIdx) throw(std::out_of_range) {
    if(pIdx < 0 || pIdx >= mSize)
        throw std::out_of_range("List index out of range");
    Node* node = mHead;
    for(int i = 0; i != pIdx; ++i, node = node->next);
    removeElement(node);

}

void PriorityList::removeOneByValue(long pVal) {
    Node* node = mHead;
    while(node != nullptr && node->data != pVal)
        node = node->next;
    if(node != nullptr)
        removeElement(node);
}

void PriorityList::removeAllByValue(long pVal) {
    return removeByRange(pVal, pVal);
}

void PriorityList::removeByRange(long pLVal, long pRVal) {
    Node* node = mHead;
    while(node != nullptr) {
        if(node->data >= pLVal && node->data <= pRVal)
            node = removeElement(node);
        else
            node = node->next;
    }
}

void PriorityList::removeAll() {
    Node* node = mHead;
    while(node != nullptr)
        node = removeElement(node);
}

void PriorityList::removeDuplicates() {
    using Set = std::unordered_set<long>;
    Set values;
    Node* node = mHead;
    while (node != nullptr) {
        if(values.find(node->data) != values.end())
            node = removeElement(node);
        else{
            values.insert(node->data);
            node = node->next;
        }
    }
}

/** Returns new list created from that list, but without duplicates */
PriorityList PriorityList::unique() {
    PriorityList list(*this);
    list.removeDuplicates();
    return list;
}


PriorityList::iterator PriorityList::begin() const {
  return PriorityList::iterator(mHead);
}

PriorityList::iterator PriorityList::end() const {
    if(mTail != nullptr)
        return PriorityList::iterator(mTail->next);
    return PriorityList::iterator(nullptr);
}

PriorityList::constIterator PriorityList::cBegin() const {
  return PriorityList::constIterator(mHead);
}

PriorityList::constIterator PriorityList::cEnd() const {
    if(mTail != nullptr)
        return PriorityList::constIterator(mTail->next);
    return PriorityList::constIterator(nullptr);
}

int PriorityList::length() const {
  return this->mSize;
}

PriorityList PriorityList::operator+(const PriorityList& rhs) const {
    PriorityList res(*this);
    res.operator+=(rhs);
    return res;
}

PriorityList& PriorityList::operator+=(const PriorityList& rhs) {
    for(auto it = rhs.cBegin(); it != rhs.cEnd(); ++it) {
            internalInsert(it->data, mSize, it->ref_cnt);
    }
    return *this;
}

PriorityList PriorityList::operator-(const PriorityList& rhs) const {
    PriorityList res(*this);
    res.operator-=(rhs);
    return res;
}

PriorityList& PriorityList::operator-=(const PriorityList& rhs) {
    for(auto it = rhs.cBegin(); it != rhs.cEnd(); ++it)
        removeOneByValue(*it);
    return *this;
}

bool PriorityList::operator==(const PriorityList& rhs) const {
  if(mSize != rhs.length())
    return false;

    auto li = cBegin();
    auto ri = rhs.cBegin();
    for(;li != cEnd() && ri != rhs.cEnd(); ++li, ++ri)
          if(li->data != ri->data || li->ref_cnt != ri->ref_cnt)
            return false;

    if(li == cEnd() && ri == rhs.cEnd())
      return true;
    return false;
 }

 bool PriorityList::operator!=(const PriorityList& rhs) const {
     return !(operator==(rhs));
 }

void PriorityList::internalInsert(long pData, int pIdx) {
  if ((pIdx < mSize) && (pIdx >= 0)) {
    Node *node = mHead;

    for (int i = 0; i < pIdx; ++i, node = node->next);
    return internalInsert(pData, pIdx, 1 + node->ref_cnt);
  } else return internalInsert(pData, pIdx, 0);
}

 void PriorityList::internalInsert(long pData, int pIdx, unsigned int pRefCnt) {
     Node* node = new Node(pData, pRefCnt);
     if(mSize == 0) {
         mHead = node;
         mTail = node;
     }
     else if(pIdx == 0) {
         node->next = mHead;
         mHead->prev = node;
         mHead = node;
     } else if(pIdx >= mSize) {
         node->prev = mTail;
         mTail->next = node;
         mTail = node;
     } else {
         auto it = begin();
         for(int i = 0; i != pIdx; ++i, ++it);

         node->next = it.getNode();
         node->prev = it->prev;
         it->prev->next = node;
         it->prev = node;
     }
     mSize++;
     sortNearNode(node);
 }


void PriorityList::sortNearNode(PriorityList::Node *pNode) {
    if(pNode == nullptr)
        return;

    Node* ptr = pNode->prev;

    if(ptr == nullptr) //if pNode is at the beggingng of the list
        return;

    while(ptr != nullptr && (*ptr)<(*pNode))
        ptr = ptr->prev;

    if(ptr == pNode->prev) // No need to sort
        return;

    if(pNode->next != nullptr){
        pNode->next->prev = pNode->prev;
        pNode->prev->next = pNode->next;
    } else {
        pNode->prev->next = nullptr;
        mTail = pNode->prev;
    }

    if(ptr == nullptr) { //have to move pNode to the begining of the list
        pNode->next = mHead;
        pNode->prev = nullptr;
        mHead->prev = pNode;
        mHead = pNode;
    } else { //have to move pNode right after ptr
        pNode->next = ptr->next;
        pNode->prev = ptr;
        ptr->next->prev = pNode;
        ptr->next = pNode;
    }
}

PriorityList::Node* PriorityList::removeElement(PriorityList::Node* pNode) {
    if(pNode == nullptr)
        return nullptr;
    if(pNode->next == nullptr) {
         if(pNode->prev == nullptr) {
            mHead = nullptr;
            mTail = nullptr;
        } else {
            mTail = pNode->prev;
            pNode->prev->next = nullptr;
         }
     } else if (pNode->prev == nullptr) {
        mHead = pNode->next;
        pNode->next->prev = nullptr;
     }else {
        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;
     }
     mSize--;

     Node* next = pNode->next;
     delete pNode;
     return next;
 }

std::ostream& operator<<(std::ostream& out, PriorityList& mList)
{
    for(auto it = mList.cBegin(); it != mList.cEnd(); ++it)
    {
        out << it->data << "(" << it->ref_cnt << "), ";
        //out << it->data << "(" << it->ref_cnt << ")["<< it.getNode() << ", " << it->prev << ", " << it->next << "], ";
    }
    return out;
}
