/* */
#include <iostream>
#include "PriorityList.hpp"

using namespace std;

int main(int argc, const char **argv)
{
  PriorityList list;

  list.pushFront(222);
  list.pushFront(255);
  list.pushFront(314);
  list.pushFront(314);
  list.pushBack(314);
  list.pushBack(222);
  list.pushBack(255);
  cout << list << endl;
  PriorityList list2(list);
  list.removeDuplicates();
  cout << "List1:\n" << list << endl;
  cout << "List2:\n" << list2 << endl;
  PriorityList a =  list2 + list;
  cout << "List2 + List1 =\n" << a << endl;
  a = list2 - list;
  cout << "List2 - List1 =\n" << a << endl;
  cout << "List2 == List1 " << (list2==list) << endl;
  cout << "List1 == List1 " << (list==list) << endl;

  //cout << list.length() << " " << list[0] << endl;
  //cout << "find(271): " << list.find(271) << endl;
  //list.pushFront(271);
  //cout << list.length() << " " << list[0] << endl;
  //cout << list << endl;
  //cout << list.length() << " " << list[2] << endl;
  //cout << list << endl;
  //cout << "find(222): " <<   list.find(222) << endl;
  //cout << "find(222): " <<   list.find(222) << endl;
  //cout << "find(222): " <<   list.find(222) << endl;
  //cout << list << endl;
  //list.removeAllByValue(314);
  //cout << "Remove: " << list.length() << endl;
  //cout << "find(271): " << list.find(271) << endl;
  //cout << "Removing dups:\n";
  //list.removeDuplicates();
  //cout << list << endl;

  return 0;
}
