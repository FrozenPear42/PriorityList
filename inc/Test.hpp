/**
* @autor Wojciech Gruszka
* @email wojciech@gruszka.eu
*
*/
#pragma once
#include <functional>
#include <iostream>

#define assert(expr) try{ \
if(!(expr)){self.out << "Test " << self.mName << " failed at: " #expr "\n"; return false;} \
else {self.out << "[OK] " #expr << "\n";} \
}catch(...){self.out << "Test " << self.mName << " failed at: " #expr "\n" << "Exception: " << "happened!" << "\n"; return false;}

#define eval(expr) self.out <<"[OP] " #expr "\n"; expr;

class Test {
public:
    bool run() {
        out << "Running test " << mName << ":\n";
        bool res = mExpression(*this);
        if(res)
        out << "Success!\n";
        else
        out << "Fail!\n";
        out << "\n";
        return res;
    };
    Test(std::string pName, std::function<bool(Test&)> pCode, std::ostream& pOut = std::cout) : mName(pName), mExpression(pCode), out(pOut) {};

    std::string mName;
    std::function<bool(Test&)> mExpression;
    std::ostream& out;
};
