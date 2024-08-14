#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <cstdlib>

spdlog::level::level_enum LOG_LEVEL;

namespace logger {

Logger::Logger() {
    setGlobalLevel();
    logger_ = spdlog::stdout_color_mt(LOGGER_NAME);
    logger_->set_level(static_cast<spdlog::level::level_enum>(LOG_LEVEL)); 
    logger_->set_pattern("[%^%t%$][%^%L%$] %v"); // thread + level + content

    spdlog::set_default_logger(logger_);
}

void Logger::setGlobalLevel() {
    if (std::getenv("LOG_LEVEL") != nullptr) {
        std::string level = std::getenv("LOG_LEVEL");
        if (level == "6") {
            LOG_LEVEL = level_enum::off;
        } else if (level == "5") {
            LOG_LEVEL = level_enum::critical;
        } else if (level == "4") {
            LOG_LEVEL = level_enum::err;
        } else if (level == "3") {
            LOG_LEVEL = level_enum::warn;
        } else if (level == "2") {
            LOG_LEVEL = level_enum::info;
        } else if (level == "1") {
            LOG_LEVEL = level_enum::debug;
        } else if (level == "0") {
            LOG_LEVEL = level_enum::trace;
        }
    } 
}

LogStream::~LogStream() {
    flush(level_, logger_);
}

thread_local int LogStream::indent_ = 0;

void LogStream::flush(level_enum level, std::shared_ptr<spdlog::logger> logger) {
    std::string logStr = std::string(LogStream::indent_, ' ') + str();
    switch (level) {
        case level_enum::trace:
        LOG_TRACE(logStr);
        break;
        case level_enum::debug:
        LOG_DEBUG(logStr);
        break;
        case level_enum::info:
        LOG_INFO(logStr);
        break;
        case level_enum::warn:
        LOG_WARN(logStr);
        break;
        case level_enum::err:
        LOG_ERROR(logStr);
        break;
        default:
         break;
    }
}

}
