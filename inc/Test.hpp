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

#define assert(expr) try{ \
if(!(expr)){self.out << "[" COLOR_RED "FAIL" COLOR_RESET "] " #expr << "\n";; return false;} \
else {self.out << "  [" COLOR_GREEN "OK" COLOR_RESET "] " #expr << "\n";} \
}catch(...){self.out << "[" COLOR_RED "FAIL" COLOR_RESET "] " #expr << " EXCEPTION" << "\n"; return false;}

#define eval(expr) expr; self.out <<"[" COLOR_YELLOW "EVAL" COLOR_RESET "] " #expr "\n";

#define log(comment, data) self.out << " [" COLOR_BLUE "LOG" COLOR_RESET "] " << comment << ": " << data << "\n";
#define log_obj(obj) self.out << " [" COLOR_BLUE "LOG" COLOR_RESET "] " << #obj ": " << obj << "\n";

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
