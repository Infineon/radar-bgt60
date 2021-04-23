/** 
 * @file        bgt60-conf.hpp
 * @brief       Radar BGT-60GHz Library Configuration
 * @date        April 2021
 * @copyright   Copyright (c) 2020-2021 Infineon Technologies AG
 *              
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_CONF_HPP_
#define BGT60_CONF_HPP_

#include "bgt60-conf-opts.hpp"

#ifndef BGT60_FRAMEWORK 
#define BGT60_FRAMEWORK         BGT60_FRMWK_ARDUINO
#endif

#ifndef BGT60_LOGGER_ENABLED
#define BGT60_LOGGER_ENABLED    1   /**< (1) Enabled, (0) Disabled */
#endif

/**
 * @brief Enable each logger module
 */
#if (BGT60_LOGGER_ENABLED == 1)

#define BGT60_CORE_LOGGER_ENABLED   1               /**< Core module */
#define BGT60_APP_LOGGER_ENABLED    1               /**< Application level module */

#endif

#include "bgt60-conf-dfl.hpp"

#endif /** BGT60_CONF_HPP_ **/