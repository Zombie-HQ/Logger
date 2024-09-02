#include "Logger.h"


void func1() {
    LOG_TRACE("This is a Trace message");
    LOG_DEBUG("This is a Debug message");
    LOG_INFO("This is an Info message");
    LOG_WARN("This is a Warning message");
    LOG_ERROR("This is an Error message");
}

 

int main() {
    HEADER(DEBUG);
    func1();
    func2();
    FOOTER(DEBUG);
    return 0;
}