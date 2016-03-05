/* */
#include <iostream>
#include "PriorityList.hpp"

using namespace std;

int main(int argc, char** argv)
{
    PriorityList list;
    cout << list.length() << endl;
    list.pushFront(222);
    cout << list.length() << endl;
    list.pushFront(222);
    cout << list.length() << endl;
  return 0;
}
