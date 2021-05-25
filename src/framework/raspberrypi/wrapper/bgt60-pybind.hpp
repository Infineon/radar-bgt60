/**
 * @file        bgt60-pybind.hpp
 *  @author      Infineon Technologies AG
 * @brief       Radar BGT60 Raspberry Pi Python Wrapper API
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_PYBIND_HPP_
#define BGT60_PYBIND_HPP_


#include "../../../config/bgt60-conf.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)

#include "bgt60.hpp"
#include "bgt60-rpi.hpp"
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#endif /** BGT60_FRAMEWORK **/
#endif /** BGT60_PYBIND_HPP_ **/