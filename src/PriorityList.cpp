/**
 * @autor Wojciech Gruszka
 * @email wojciech@gruszka.eu
 *
 */
#include <unordered_set>
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
    //TODO: Sort
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
    if(pIdx < 0 || pIdx >= mSize)
        throw std::out_of_range("List index out of range");
    int i = 0;
    Node* node = mHead;
    while(i++ != pIdx)
        node = node->next;
    removeElement(node);

}

void PriorityList::removeOneByValue(long pVal) {
    Node* node = mHead;
    while(node != nullptr && node->data == pVal )
        node = node->next;
    if(node != nullptr && node->data == pVal)
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
    for(auto it = mList.cBegin(); it != mList.cEnd(); it++)
    {
        //FIXME: ERRHERE
        out << it->data << "(" << it->ref_cnt << ")\n";
    }
    return out;
}
