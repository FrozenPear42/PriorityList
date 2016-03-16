/**
* @autor Wojciech Gruszka
* @email wojciech@gruszka.eu
*
*/
#pragma once
#include <functional>
#include <exception>
#include <iostream>

#define COLOR_RED "\x1B[31m"
#define COLOR_GREEN "\x1B[32m"
#define COLOR_YELLOW "\x1B[33m"
#define COLOR_BLUE "\x1B[34m"
#define COLOR_RESET "\x1B[0m"

#define OK_TAG      "[" COLOR_GREEN  "OK"   COLOR_RESET "]   "
#define FAIL_TAG    "[" COLOR_RED    "FAIL" COLOR_RESET "] "
#define EVAL_TAG    "[" COLOR_YELLOW "EVAL" COLOR_RESET "] "
#define LOG_TAG     "[" COLOR_BLUE   "LOG"  COLOR_RESET "]  "

#ifndef TEST_OUT
#define TEST_OUT std::cout
#endif

#define assert(expr) try{                                           \
if(!(expr)) {                                                       \
    TEST_OUT << FAIL_TAG #expr << "\n";                             \
    return false;                                                   \
} else {                                                            \
TEST_OUT << OK_TAG #expr << "\n";                                   \
}                                                                   \
}catch(std::exception& e){                                          \
    TEST_OUT << FAIL_TAG #expr": " << e.what() << "\n";             \
    return false;                                                   \
}catch(...){                                                        \
    TEST_OUT << FAIL_TAG #expr ": Unknown exception!" << "\n";      \
    return false;                                                   \
}

#define expect(expr) try{                                           \
    expr;                                                           \
    TEST_OUT << FAIL_TAG #expr": Expected exception!\n";            \
    return false;                                                   \
}catch(std::exception& e) {                                         \
    TEST_OUT << OK_TAG #expr << " Expected: " << e.what() << "\n";  \
}catch(...) {                                                       \
    TEST_OUT << OK_TAG #expr << " Expected: exception" << "\n";     \
}                                                                   \


#define eval(expr) expr; TEST_OUT << EVAL_TAG #expr "\n";

#define log(comment, data) TEST_OUT << LOG_TAG << comment << ": " << data << "\n";
#define log_obj(obj) TEST_OUT << LOG_TAG << #obj ": " << obj << "\n";

class Test {
public:
    bool run() {
        TEST_OUT << "Running test: " << mName << "\n";
        try {
            success = mExpression();
        } catch(std::exception& e) {
            success = false;
            TEST_OUT << COLOR_RED "Exception: " << e.what() << "\n" COLOR_RESET;
        } catch(...) {
            TEST_OUT << COLOR_RED "Unknown exception!\n" COLOR_RESET;
        }
        if(success)
            TEST_OUT << COLOR_GREEN "Success!\n" COLOR_RESET;
        else
            TEST_OUT << COLOR_RED "Fail!\n" COLOR_RESET;
        TEST_OUT << "\n";
        return success;
    };
    Test(std::string pName, std::function<bool(void)> pCode) : mName(pName), mExpression(pCode), success(false) {};

    std::string mName;
    std::function<bool(void)> mExpression;
    bool success;
};
