/**
 * @file bgt60-conf-dfl.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BGT60_CONF_DFL_HPP_
#define BGT60_CONF_DFL_HPP_

#include "bgt60-conf-opts.hpp"

#ifndef BGT60_FRAMEWORK
#error "BGT60 error: Framwork undefined"        /**< BGT60 framework must be define in conf.hpp or at compilation */
#endif

#ifndef BGT60_LOGGER_ENABLED
#define BGT60_LOGGER_ENABLED    0
#endif


#endif /** BGT60_CONF_DFL_HPP_ */