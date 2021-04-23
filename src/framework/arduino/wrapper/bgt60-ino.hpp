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
#include "bgt60.hpp"
#include "bgt60-pal-gpio-ino.hpp"

class BGT60Ino : public BGT60
{
    public:
                    BGT60Ino(uint8_t targetDet, uint8_t phaseDet, MeasMode_t pinMode);
                    ~BGT60Ino();
        Error_t     begin();
        Error_t     end();
        void        checkIntFlags();

    private:
    
        GPIOIno * tDetPin;
        GPIOIno * pDetPin;
};

#endif /** BGT60_FRMWK_ARDUINO */
#endif /** BGT60_INO_HPP_ */