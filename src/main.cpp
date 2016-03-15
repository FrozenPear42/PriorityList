/* */
#include <vector>
#include "PriorityList.hpp"
#include "Test.hpp"

int main(int argc, const char **argv)
{
    std::vector<Test> tests;

    tests.push_back(Test("initialization list", []{
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

    tests.push_back(Test("push front", []{
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
    tests.push_back(Test("self sorting", []{
        return false;
    }));


    tests.push_back(Test("-=/+= operators for items", []{
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

    tests.push_back(Test("remove element - less used", []{
        PriorityList list;
        log_obj(list);
        eval(list += 111);
        eval(list += 123);
        eval(list += 111);
        log_obj(list);
        eval(for(int i = 0; i < 10; ++i) list.find(111));
        assert(list.length() == 3);
        eval(list -= 111);
        log_obj(list);
        assert(list.length() == 2);
        return true;
    }));

    tests.push_back(Test("compare", []{
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

    tests.push_back(Test("length", []{
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

    tests.push_back(Test("copy constructor", []{
        PriorityList list1 = {1, 2, 3, 4, 5};
        PriorityList list2(list1);
        log_obj(list1);
        log_obj(list2);
        assert(list1 == list2);
        return true;
    }));

    tests.push_back(Test("assigment operator", []{
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
    tests.push_back(Test("remove duplicates", []{
        PriorityList list = {1, 1, 2, 3, 55, -11, 5, -11, 2, 1, 1, 3, 2, 11};
        log_obj(list);
        assert(list.length() == 14);
        eval(list.removeDuplicates());
        log_obj(list);
        assert(list.length() == 7);
        return true;
    }));

    tests.push_back(Test("remove duplicates - unique", []{
        PriorityList list = {1, 1, 2, 3, 55, -11, 5, -11, 2, 1, 1, 3, 2, 11};
        log_obj(list);
        assert(list.length() == 14);
        eval(PriorityList list2 = list.unique());
        log_obj(list);
        log_obj(list2);
        assert(list.length() == 14);
        assert(list2.length() == 7);
        return true;
    }));


    tests.push_back(Test("list sum", []{
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

    tests.push_back(Test("list subtract", []{
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

    tests.push_back(Test("iterator overflow", []{
        PriorityList list = {1};
        log_obj(list);
        eval(auto it = list.end());
        except(it++);
        eval(it = list.begin());
        eval(it--);
        except(it--);
        return true;
    }));

    tests.push_back(Test("remove by range", []{
        PriorityList list = {1,2,3,4,5,6,7,8,9,10,11,-11,-12,-13,0,4};
        log_obj(list);
        assert( list.length() == 16 );
        eval(list.removeByRange(3, 5));
        log_obj(list);
        assert(list.length() == 12);
        eval(list.removeByRange(0, 10));
        log_obj(list);
        assert(list.length() == 4);
        eval(list.removeByRange(-10, 10));
        log_obj(list);
        assert(list.length() == 4);
        eval(list.removeByRange(-10000, 10000));
        log_obj(list);
        assert(list.length() == 0);
        return true;
    }));

    tests.push_back(Test("insert", []{
        PriorityList list;
        log_obj(list);
        eval(list.insert(11, 3));
        log_obj(list);
        eval(list.insert(12, 3));
        log_obj(list);
        eval(list.insert(13, 3));
        log_obj(list);
        eval(list.insert(15, 0));
        log_obj(list);
        assert(list.length() == 4)
        eval(list.insert(16, 1));
        log_obj(list);
        assert(list.length() == 5);
        assert(list.find(16) != -1);
        return true;
    }));



    for(Test& test : tests)
        test.run();

    TEST_OUT << "\nSUMMARY: \n";
    for(Test& test : tests){
        if(!test.success)
            TEST_OUT << COLOR_RED "Test: " << test.mName << " failed!\n" COLOR_RESET;
        else
            TEST_OUT << COLOR_GREEN "Test: " << test.mName << " succeed!\n" COLOR_RESET;
    }


    return 0;
}
