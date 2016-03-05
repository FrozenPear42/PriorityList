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

void PriorityList::removeByIdx(int pIdx) {

}

void PriorityList::removeOneByValue(long pVal) {

}

void PriorityList:: removeAllByValue(long pVal) {

}

void PriorityList::removeAll() {

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
