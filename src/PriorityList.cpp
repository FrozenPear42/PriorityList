/**
 * @autor Wojciech Gruszka
 * @email wojciech@gruszka.eu
 *
 */
#include "PriorityList.hpp"


int PriorityList::length() {
  return this->size;
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
