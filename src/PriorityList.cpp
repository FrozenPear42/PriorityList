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

void PriorityList::removeByIdx(int pIdx) {

}

void PriorityList::removeOneByValue(long pVal) {

}

void PriorityList:: removeAllByValue(long pVal) {

}

void PriorityList::removeAll() {

}

PriorityList::iterator PriorityList::begin() const {
  return PriorityList::iterator(head);
}

PriorityList::iterator PriorityList::end() const {
  return PriorityList::iterator(tail->next);
}

PriorityList::constIterator PriorityList::cBegin() const {
  return PriorityList::constIterator(head);
}

PriorityList::constIterator PriorityList::cEnd() const {
  return PriorityList::constIterator(tail->next);
}

int PriorityList::length() const {
  return this->size;
}

PriorityList PriorityList::operator+(const PriorityList& rhs) const {
    PriorityList res(*this);
    res.operator+=(rhs);
    return res;
}

PriorityList& PriorityList::operator+=(const PriorityList& rhs) {
    for(auto it = rhs.cBegin(); it != rhs.cEnd(); it++) {
            //TODO: Add on the end
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
  if(size != rhs.size)
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
