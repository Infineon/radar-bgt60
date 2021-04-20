/**
 * @file bgt60-logger.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BGT60_PAL_LOGGER_HPP_
#define BGT60_PAL_LOGGER_HPP_

#include "bgt60-conf.hpp"

#if (BGT60_LOGGER_ENABLED == 1)

#include <stdint.h>
#include "bgt60-types.hpp"

namespace bgt60
{

class LoggerPAL
{
    public:

        /**
         * @brief       Initialize the logger interface
         * @return      Error_t
         * @retval      OK if success
         * @retval      INTF_ERROR if error
         */
        virtual Error_t init() = 0;

        /**
         * @brief       De-Initialize the logger interface
         * @return      Error_t
         * @retval      OK if success
         * @retval      INTF_ERROR if error 
         */
        virtual Error_t deinit() = 0;

        /**
         * @brief       Write in the logger interface
         * @param[in]   *logData    Pointer to the array holding the data to be logged
         * @param[in]   length      Length in bytes of the data to be written
         * @return      Error_t
         * @retval      OK if success
         * @retval      INTF_ERROR if error
         */
        virtual Error_t write(const uint8_t * logData, uint32_t length) = 0;
};

}

#endif /** BGT60_LOGGER_ENABLED */
#endif /** BGT60_PAL_LOGGER_HPP_ */