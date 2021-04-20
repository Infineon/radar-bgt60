/**
 * @file bgt60-ino.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BGT60_INO_HPP_
#define BGT60_INO_HPP_

#include "bgt60-conf.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_ARDUINO)

#include <Arduino.h>
#include "bgt60-gpio.hpp"
#include "bgt60-gpio-ino.hpp"

class BGT60Ino : public BGT60
{
    public:
                    BGT60Ino();
                    ~BGT60Ino();
        Error_t     begin();
        Errort_t    end();
}

#endif /** BGT60_FRMWK_ARDUINO */
#endif /** BGT60_INO_HPP_ */