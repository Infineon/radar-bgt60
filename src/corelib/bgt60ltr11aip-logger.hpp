/**
 * @file bgt60ltr11aip-logger.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BGT60LTR11AIP_LOGGER_HPP_
#define BGT60LTR11AIP_LOGGER_HPP_

#include "bgt60ltr11aip-conf.hpp"

#if (BGT60LTR11AIP_LOGGER_ENABLED == 1)

#include <stdint.h>
#include "bgt60ltr11aip-pal-logger.hpp"

class Logger
{
    public:
            Logger();
            Logger(LoggerPAL *logPal);
            ~Logger();
            void init();
            void deinit();
            void print();
            void printfModule();
            void printModuleHex();

    private:
        LoggerPAL *logPal;

};

/**
 * @brief Library Logger
 */

extern Logger bgt60_log;

/**
 * Logger colors options
 */
#define BGT60RTL11AIP_COLOR_RED                  "\x1b[31m"
#define BGT60RTL11AIP_COLOR_GREEN                "\x1b[32m"
#define BGT60RTL11AIP_COLOR_YELLOW               "\x1b[33m"
#define BGT60RTL11AIP_COLOR_BLUE                 "\x1b[34m"
#define BGT60RTL11AIP_COLOR_MAGENTA              "\x1b[35m"
#define BGT60RTL11AIP_COLOR_CYAN                 "\x1b[36m"
#define BGT60RTL11AIP_COLOR_LIGHT_GREY           "\x1b[90m"
#define BGT60RTL11AIP_COLOR_LIGHT_RED            "\x1b[91m"
#define BGT60RTL11AIP_COLOR_LIGHT_GREEN          "\x1b[92m"
#define BGT60RTL11AIP_COLOR_LIGHT_YELLOW         "\x1b[93m"
#define BGT60RTL11AIP_COLOR_LIGHT_BLUE           "\x1b[94m"
#define BGT60RTL11AIP_COLOR_LIGHT_MAGENTA        "\x1b[95m"
#define BGT60RTL11AIP_COLOR_LIGHT_CYAN           "\x1b[96m"
#define BGT60RTL11AIP_COLOR_DEFAULT              "\x1b[0m"

/**
 * @brief BGT60LTR11AIP logger module
 */

/**
 * Logger color for different error types
 */
#define BTG60LTR11AIP_LOGGER_ERROR_COLOR        BGT60RTL11AIP_COLOR_RED
#define BTG60LTR11AIP_LOGGER_WARNING_COLOR      BGT60RTL11AIP_COLOR_YELLOW

#define BGT60LTR11AIP_LOG_INIT()\
{\
    bgt60_log.init();\
}

#define BGT60LTR11AIP_LOG_DEINIT()\
{\
    bgt60_log.deinit();\
}

/**
 * @brief BGT60LTR11AIP core logger module
 */
#if (BGT60LTR11AIP_CORE_LOGGER_ENABLED == 1)

#define BGT60LTR11AIP_LOGGER_SERVICE        "[bgt60ltr11aip]        : "
#define BGT60LTR11AIP_LOGGER_COLOR          BGT60RTL11AIP_COLOR_GREEN

#define BGT60RTL11AIP_LOG_MSG(str)\
{\
bgt60_log.printfModule(str, BGT60LTR11AIP_LOGGER_SERVICE, BGT60LTR11AIP_LOGGER_COLOR);\
}

#define BGT60RTL11AIP_LOG_RETURN(ret)\
{\
    if(0 > ret)\
    {\
        bgt60_log.printfModule("fail with return code %i", BGT60RTL11AIP_LOGGER_SERVICE, BGT60RTL11AIP_LOGGER_ERROR_COLOR, ret);\
    }\
    else\
    {\
        bgt60_log.printfModule("pass", BGT60RTL11AIP_LOGGER_SERVICE, BGT60RTL11AIP_LOGGER_COLOR);\
    }\
}

#else

#define BGT60LTR11AIP_LOG_MSG(str)      {   }
#define BGT60LTR11AIP_LOG_RETURN(ret)   {   }

#endif  /** BGT60LTR11AIP_CORE_LOGGER_ENABLED */

/**
 * @brief BGT60LTR11AIP serial logger module
 */

#if (BGT60LTR11AIP_SERIAL_LOGGER_ENABLED == 1)

/**
 * Logger color for different error types
 */

#define BGT60LTR11AIP_SERIAL_LOGGER_SERVICE     "[bgt60ltr11aip serial]     : "
#define BGT60LTR11AIP_SERIAL_LOGGER_COLOR       