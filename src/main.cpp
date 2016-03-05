/* */
#include <iostream>
#include "PriorityList.hpp"

using namespace std;

int main(int argc, char** argv)
{
    PriorityList list;
    cout << list.length() << endl;
    list.pushFront(314);
    cout << list.length() << " " << list[0] << endl;
    cout << "find(271): " << list.find(271) << endl;
    list.pushFront(271);
    cout << list.length() << " " << list[0] << " " << list[1] << endl;
    cout << "find(271): " << list.find(271) << endl;
  return 0;
}
