/**
 * @autor Wojciech Gruszka
 * @email wojciech@gruszka.eu
 *
 */
#include "PriorityList.hpp"

PriorityList::PriorityList(const PriorityList& pList)
{
    PriorityList();
    operator+=(pList);
}

void PriorityList::pushBack(long pVal) {
    pushBackRef(pVal, 0);
}

void PriorityList::pushFront(long pVal) {
    pushFrontRef(pVal, 0);
}

long PriorityList::getByIdx(int pIdx) {
    return operator[](pIdx);
}

long& PriorityList::operator[](int pIdx) {
    if(pIdx < 0 || pIdx >= mSize)
        throw std::out_of_range("List index out of range");
    int i = 0;
    Node* node = mHead;
    while(i != pIdx) {
        i++;
        node = node->next;
    }
    node->ref_cnt++;

    return node->data;
}

int PriorityList::find(long pVal) {
    int i = 0;
    for(auto it = begin(); it != end(); it++, i++)
        if(*it == pVal) {
            it->ref_cnt++;
            return i;
        }
    return -1;
}

void PriorityList::removeByIdx(int pIdx) {
//TODO
}

void PriorityList::removeOneByValue(long pVal) {
//TODO
}

void PriorityList:: removeAllByValue(long pVal) {
//TODO
}

void PriorityList::removeAll() {
//TODO
}

PriorityList::iterator PriorityList::begin() const {
  return PriorityList::iterator(mHead);
}

PriorityList::iterator PriorityList::end() const {
  return PriorityList::iterator(mTail->next);
}

PriorityList::constIterator PriorityList::cBegin() const {
  return PriorityList::constIterator(mHead);
}

PriorityList::constIterator PriorityList::cEnd() const {
  return PriorityList::constIterator(mTail->next);
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
    for(auto it = rhs.cBegin(); it != rhs.cEnd(); it++) {
            pushBackRef(it->data, it->ref_cnt);
    }
    return *this;
}

PriorityList PriorityList::operator-(const PriorityList& rhs) const {
    PriorityList res(*this);
    res.operator-=(rhs);
    return res;
}

PriorityList PriorityList::operator-=(const PriorityList& rhs) {
    for(auto it = rhs.cBegin(); it != rhs.cEnd(); it++)
        this->removeOneByValue(*it);
    return *this;
}

PriorityList& PriorityList::operator=(const PriorityList& rhs) {
    this->removeAll();
    this->operator+=(rhs);
    return *this;
}

bool PriorityList::operator==(const PriorityList& rhs) const {
  if(mSize != rhs.length())
    return false;

    auto li = cBegin();
    auto ri = rhs.cBegin();
    for(;li != cEnd() && ri != rhs.cEnd(); li++, ri++)
          if(*li != *ri)
            return false;
    if(li == cEnd() && ri == rhs.cEnd())
      return true;
    return false;
 }

 void PriorityList::pushFirstRef(long pData, unsigned int pRefCnt) {
     Node* node = new Node(pData, pRefCnt);
     mHead = node;
     mTail = node;
     mSize++;
 }

 void PriorityList::pushFrontRef(long pData, unsigned int pRefCnt) {
     if(mSize == 0)
        return pushFirstRef(pData, pRefCnt);
    Node* node = new Node(pData, pRefCnt);
    node->next = mHead;
    mHead->prev = node;
    mHead = node;
    mSize++;
 }

 void PriorityList::pushBackRef(long pData, unsigned int pRefCnt) {
     if(mSize == 0)
        return pushFirstRef(pData, pRefCnt);
    Node* node = new Node(pData, pRefCnt);
    node->prev = mTail;
    mTail->next = node;
    mTail = node;
    mSize++;
 }
