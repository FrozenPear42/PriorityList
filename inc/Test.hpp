/**
* @autor Wojciech Gruszka
* @email wojciech@gruszka.eu
*
*/
#pragma once
#include <functional>
#include <iostream>

#define COLOR_RED "\x1B[31m"
#define COLOR_GREEN "\x1B[32m"
#define COLOR_YELLOW "\x1B[33m"
#define COLOR_BLUE "\x1B[34m"
#define COLOR_RESET "\x1B[0m"

#define OK_TAG      "[" COLOR_GREEN "OK" COLOR_RESET "]   "
#define FAIL_TAG    "[" COLOR_RED "FAIL" COLOR_RESET "] "
#define EVAL_TAG    "[" COLOR_YELLOW "EVAL" COLOR_RESET "] "
#define LOG_TAG     "[" COLOR_BLUE "LOG" COLOR_RESET "]  "

#define assert(expr) try{ \
if(!(expr)){self.out << FAIL_TAG #expr << "\n"; return false;} \
else {self.out << OK_TAG #expr << "\n";} \
}catch(...){self.out << FAIL_TAG #expr << " EXCEPTION" << "\n"; return false;}

#define eval(expr) expr; self.out << EVAL_TAG #expr "\n";

#define log(comment, data) self.out << LOG_TAG << comment << ": " << data << "\n";
#define log_obj(obj) self.out << LOG_TAG << #obj ": " << obj << "\n";

class Test {
public:
    bool run() {
        out << "Running test: " << mName << "\n";
        bool res = mExpression(*this);
        if(res)
            out << COLOR_GREEN "Success!\n" COLOR_RESET;
        else
            out << COLOR_RED "Fail!\n" COLOR_RESET;
        out << "\n";
        return res;
    };
    Test(std::string pName, std::function<bool(Test&)> pCode, std::ostream& pOut = std::cout) : mName(pName), mExpression(pCode), out(pOut) {};

    std::string mName;
    std::function<bool(Test&)> mExpression;
    std::ostream& out;
};
