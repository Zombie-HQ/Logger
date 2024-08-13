#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace logger {

// #define LOG_TRACE(...) 

using level_enum = spdlog::level::level_enum;

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(Logger const&) = delete;
    Logger& operator=(const Logger&) = delete;
private:
    Logger();
    void setGlobalLevel();
    std::shared_ptr<spdlog::logger> logger;
};

class LogStream : public std::stringstream {
public:
    LogStream(level_enum level, std::shared_ptr<spdlog::logger> logger) :
        level_(level), logger_(logger){}
    
private:
    level_enum level_;
    std::shared_ptr<spdlog::logger> logger_;
    std::ostringstream stream_;

    static thread_local int indent;
};
} // namespace logger

#define LOGGER logger::Logger

typedef enum {
    TRACE       = spdlog::level::trace,
    DEBUG       = spdlog::level::debug,
    INFO        = spdlog::level::info,
    WARN        = spdlog::level::warn,
    ERROR       = spdlog::level::err,
    CRITICAL    = spdlog::level::critical,
    OFF         = spdlog::level::off
} LogLevel;

#define LOG(LEVEL) logger::LogStream((spdlog::level::level_enum)LEVEL, logger::Logger::getInstance().logger)

#endif