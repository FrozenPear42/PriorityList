/* */
#include <vector>
#include "PriorityList.hpp"
#include "Test.hpp"

int main(int argc, const char **argv)
{
    std::vector<Test> tests;

    tests.push_back(Test("initialization list", [](Test& self){
        PriorityList list = {1, 2, 3, 4, 5};
        log_obj(list);
        assert(list.length() == 5);
        assert(list.find(1) != -1);
        assert(list.find(2) != -1);
        assert(list.find(3) != -1);
        assert(list.find(4) != -1);
        assert(list.find(5) != -1);
        return true;
    }));


    tests.push_back(Test("push front", [](Test& self){
        PriorityList list = {1, 2, 3, 4, 5};
        log_obj(list);
        eval(list.pushFront(11));
        log_obj(list);
        assert(list.length() == 6);
        eval(list.pushFront(11));
        log_obj(list);
        assert(list.length() == 7);
        return true;
    }));


    //TODO: REWRITE TEST
    tests.push_back(Test("self sorting", [](Test& self){
        PriorityList list = {1, 2, 3, 4, 5};
        log_obj(list.find(4));
        log_obj(list);
        assert(list.find(4) == 0);
        log_obj(list.find(2));
        log_obj(list);
        log_obj(list.find(2));
        log_obj(list);
        assert(list.find(2) == 1);
        return true;
    }));


    tests.push_back(Test("add element", [](Test& self){
        PriorityList list;
        log_obj(list);
        eval(list += 111);
        eval(list += 123);
        eval(list += 111);
        log_obj(list);
        assert(list.length() == 3);
        eval(list -= 111);
        log_obj(list);
        assert(list.length() == 2);
        return true;
    }));

    tests.push_back(Test("compare", [](Test& self){
        PriorityList list1 = {1, 2, 3, 4, 5};
        PriorityList list2 = {5, 4, 3, 2, 1};
        log_obj(list1);
        log_obj(list2);
        assert(list1 == list2);
        eval(list1.pushFront(5));
        log_obj(list1);
        log_obj(list2);
        assert(list1 != list2);
        eval(list2.pushBack(5));
        log_obj(list1);
        log_obj(list2);
        assert(list1 != list2);
        return true;
    }));

    tests.push_back(Test("length", [](Test& self){
        PriorityList list = {-15555, 0, 1222};
        log_obj(list);
        assert(list.length() == 3);
        eval(list.pushBack(11));
        log_obj(list);
        assert(list.length() == 4);
        eval(list.removeOneByValue(0));
        log_obj(list);
        assert(list.length() == 3);
        eval(list.removeAll());
        log_obj(list);
        assert(list.length() == 0);
        return true;
    }));

    tests.push_back(Test("copy constructor", [](Test& self){
        PriorityList list1 = {1, 2, 3, 4, 5};
        PriorityList list2(list1);
        log_obj(list1);
        log_obj(list2);
        assert(list1 == list2);
        return true;
    }));

    tests.push_back(Test("assigment operator", [](Test& self){
        PriorityList list1 = {1, 2, 3, 4, 5};
        PriorityList list2;
        log_obj(list1);
        log_obj(list2);
        eval(list2 = list1);
        log_obj(list1);
        log_obj(list2);
        assert(list1 == list2);
        return true;
    }));

    //TODO: Improve test
    tests.push_back(Test("remove duplicates", [](Test& self){
        PriorityList list = {1, 1, 2, 3, 55, -11, 5, -11, 2, 1, 1, 3, 2, 11};
        log_obj(list);
        assert(list.length() == 14);
        eval(list.removeDuplicates());
        log_obj(list);
        assert(list.length() == 7);
        return true;
    }));

    tests.push_back(Test("list sum", [](Test& self){
        PriorityList list1 = {1, 2, 3, 4, 5};
        PriorityList list2 = {6, 7, 8, 9, 10};
        PriorityList list3;
        log_obj(list1);
        log_obj(list2);
        log_obj(list3);
        eval(list3 = list1 + list2);
        log_obj(list1);
        log_obj(list2);
        log_obj(list3);
        assert(list3.length() == 10);
        return true;
    }));

    tests.push_back(Test("list subtract", [](Test& self){
        PriorityList list1 = {1, 2, 3, 4, 5};
        PriorityList list2 = {1, 5, 6, 7};
        PriorityList list3;
        log_obj(list1);
        log_obj(list2);
        log_obj(list3);
        eval(list3 = list1 - list2);
        log_obj(list1);
        log_obj(list2);
        log_obj(list3);
        assert(list3.length() == 3);
        eval(list3 = list2 - list1);
        log_obj(list1);
        log_obj(list2);
        log_obj(list3);
        assert(list3.length() == 2);

        return true;
    }));



    for(Test& test : tests)
        test.run();


    return 0;
}
