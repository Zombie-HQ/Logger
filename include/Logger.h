#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/fmt/bundled/core.h"
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace logger {

// #define LOG_TRACE(...) 

#define LOGGER_NAME  "logger"
using level_enum = spdlog::level::level_enum;

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(Logger const&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::shared_ptr<spdlog::logger> logger_;
private:
    Logger();
    void setGlobalLevel();
};

class LogStream : public std::stringstream {
public:
    LogStream(level_enum level, std::shared_ptr<spdlog::logger> logger) :
        level_(level), logger_(logger){}
    ~LogStream();
    void flush(level_enum level, std::shared_ptr<spdlog::logger> logger);

    static void increaseIndent() {
        if (LogStream::indent_ <= 20) {
            LogStream::indent_ += 2;
        }
    }

    static void decreaseIndent() {
        if (LogStream::indent_ >= 2) {
            LogStream::indent_ -= 2;
        }
    }

    std::shared_ptr<spdlog::logger> logger_;
private:
    level_enum level_;
    std::ostringstream stream_;

    static thread_local int indent_;
};
} // namespace logger

using namespace logger;

#define LOGGER logger::Logger

typedef enum {
    NONE     = spdlog::level::off,
    TRACE    = spdlog::level::trace,
    DEBUG    = spdlog::level::debug,
    INFO     = spdlog::level::info,
    WARN     = spdlog::level::warn,
    ERROR    = spdlog::level::err,
    CRITICAL = spdlog::level::critical,
    OFF      = spdlog::level::off
} LogLevel;

#define LOG_TRACE(...) Logger::getInstance().logger_->trace(__VA_ARGS__)
#define LOG_DEBUG(...) Logger::getInstance().logger_->debug(__VA_ARGS__)
#define LOG_INFO(...) Logger::getInstance().logger_->info(__VA_ARGS__)
#define LOG_WARN(...) Logger::getInstance().logger_->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::getInstance().logger_->error(__VA_ARGS__)

#define LOG(LEVEL) LogStream((spdlog::level::level_enum)LEVEL, Logger::getInstance().logger_)

#define HEADER(LEVEL)                                                             \
do {                                                                              \
    {                                                                             \
        LogStream logStream((spdlog::level::level_enum)LEVEL, Logger::getInstance().logger_);  \
        logStream << "+" << __FUNCTION__ << "()";                                                          \
    }                                                                                                      \
    LogStream::increaseIndent();                                                                           \
} while (0)                                                                                                \

#define FOOTER(LEVEL)                                                             \
do {                                                                              \
    LogStream::decreaseIndent();                                                  \
    {                                                                             \
        LogStream logStream((spdlog::level::level_enum)LEVEL, Logger::getInstance().logger_);  \
        logStream << "-" << __FUNCTION__ << "()";                                                          \
    }                                                                                                      \
} while (0)                                                                                                \

#endif