#include "Logger.h"


void func1() {
    LOG_TRACE("This is a Trace message");
    LOG_DEBUG("This is a Debug message");
    LOG_INFO("This is an Info message");
    LOG_WARN("This is a Warning message");
    LOG_ERROR("This is an Error message");
}

void func2() {
    HEADER(DEBUG);
    LOG(TRACE) << "This is a Trace message";
    LOG(DEBUG) << "This is a Debug message";
    LOG(INFO) << "This is an Info message";
    LOG(WARN) << "This is a Warning message";
    LOG(ERROR) << "This is an Error message";
    FOOTER(DEBUG);
}

int main() {
    HEADER(DEBUG);
    func1();
    func2();
    FOOTER(DEBUG);
    return 0;
}