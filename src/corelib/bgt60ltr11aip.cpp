/**
 * @file        bgt60ltr11aip.cpp
 * @author      Infineon Technologies AG
 * @brief       BGT60LTRAIP API
 * @version     0.0.1
 * @date        April 2021
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "bgt60ltr11aip.hpp"

/**
 * @brief 
 * 
 */
Bgt60ltr11aip::Bgt60ltr11aip(GPIO *pDet, GPIO *tDet, MeasMode_t mode) : pDet(pDet), tDet(tDet), mode(mode)
{

}

/**
 * @brief 
 * 
 */
Bgt60ltr11aip::~Bgt60ltr11aip()
{
    // How to properly destroy the instances
}

/**
 * @brief 
 * 
 */
Error_t Bgt60ltr11aip::init()
{
    Error_t err = OK;

    do
    {
        err = pDet->init();
        if(err != OK)
            break;
        
        err = tDet->init();
        if(err != OK)
            break;
    } while (0);

    return err;
}

/**
 * @brief 
 * 
 */
Error_t Bgt60ltr11aip::deinit()
{
    Error_t err = OK;

    do
    {
        err = pDet->deinit();
        if(err != OK)
            break;

        err = tDet->deinit();
        if(err != OK)
            break;
    } while (0);
    
    return err;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
Error_t Bgt60ltr11aip::getPresence()
{
    Error_t err = OK;

    


}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
Error_t Bgt60ltr11aip::getDirection()
{

}

/**
 * @brief 
 * 
 */
void Bgt60ltr11aip::poll()
{

}

/**
 * @brief 
 * 
 */
void Bgt60ltr11aip::callbackPresence()
{

}

/**
 * @brief 
 * 
 */
void Bgt60ltr11aip::callbackDirection()
{

}
