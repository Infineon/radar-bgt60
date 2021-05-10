/**
 * @file bgt60-platf-ino.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-05-10
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef BGT60_PLATF_INO_HPP_
#define BGT60_PLATF_INO_HPP_

#include "bgt60-conf.hpp"

#if(BGT60_FRAMEWORK == BGT60_FRMWK_ARDUINO)

#include <Arduino.h>

#ifdef ARDUINO_SAMD_MKR1000         /**< Arduino MKR1000 */

#define TD  16
#define PD  17

/** TODO: Also add all the other MKR-Boards from Arduino as soon they are tested **/

#elif defined(ARDUINO_AVR_UNO)      /**< Arduino MKR1000 */

#define TD  2
#define PD  3

#elif defined(XMC1100_Boot_Kit)     /**< XMC1100 Boot Kit */

#define TD  2
#define PD  3

#elif defined(XMC4700_RELAX_Kit)    /**< XMC4700 Relax Kit */

#define TD  2
#define PD  3

#else
#warning "You did not define a supported platform! \
Please make sure you're using a platfrom that is officially \
supported by the library. Have a look in the Wiki for more information."

#endif

#endif /** BGT60_FRAMEWORK **/