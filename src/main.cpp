/* */
#include <vector>
#include "PriorityList.hpp"
#include "Test.hpp"

int main(int argc, const char **argv)
{
    std::vector<Test> tests;

    tests.push_back(Test("initialization list", [](Test& self){
        PriorityList list = {1, 2, 3, 4, 5};
        self.out << "list: " << list << '\n';
        assert(list.length() == 5);
        assert(list.find(1) != -1);
        assert(list.find(2) != -1);
        assert(list.find(3) != -1);
        assert(list.find(4) != -1);
        assert(list.find(5) != -1);
        return true;
    }));

    tests.push_back(Test("length", [](Test& self){
        PriorityList list = {-15555, 0, 1222};
        self.out << "list: " << list << '\n';
        assert(list.length() == 3);
        eval(list.pushBack(11));
        self.out << "list: " << list << '\n';
        assert(list.length() == 4);
        eval(list.removeOneByValue(0));
        self.out << "list: " << list << '\n';
        assert(list.length() == 3);
        eval(list.removeAll());
        self.out << "list: " << list << '\n';
        assert(list.length() == 0);
        return true;
    }));

    tests.push_back(Test("copy constructor", [](Test& self){
        PriorityList list1 = {1, 2, 3, 4, 5};
        PriorityList list2(list1);
        self.out << "list1: " << list1 << '\n';
        self.out << "list2: " << list2 << '\n';
        assert(list1 == list2);
        return true;
    }));

    tests.push_back(Test("assigment operator", [](Test& self){
        PriorityList list1 = {1, 2, 3, 4, 5};
        PriorityList list2;
        self.out << "list1: " << list1 << '\n';
        self.out << "list2: " << list2 << '\n';
        eval(list2 = list1);
        self.out << "list1: " << list1 << '\n';
        self.out << "list2: " << list2 << '\n';
        assert(list1 == list2);
        return true;
    }));

    tests.push_back(Test("remove duplicates", [](Test& self){
        PriorityList list = {1, 1, 2, 3, 55, -11, 5, -11, 2, 1, 1, 3, 2, 11};
        self.out << "list: " << list << '\n';
        assert(list.length() == 14);
        eval(list.removeDuplicates());
        self.out << "list: " << list << '\n';
        assert(list.length() == 7);
        return true;
    }));



    for(Test& test : tests)
        test.run();
    /*
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
    */
    return 0;
}
