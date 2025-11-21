#pragma once

#include <android/log.h>
#include <source_location>
#include <string>

#define LOG_TAG "Breakout"

inline void log(const std::string &message,
                const std::source_location &location = std::source_location::current()) {
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s:%u\n%s",
                        location.file_name(),
                        location.line(),
                        message.c_str());
}
