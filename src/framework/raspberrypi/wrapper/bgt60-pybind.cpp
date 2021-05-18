/**
 * @file        bgt60-pybind.cpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Raspberry Pi Python Wrapper API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "bgt60-pybind.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(bgt60_py, m) {
	
    // Wrapper for Bgt60 Class 
    py::class_<Bgt60>bgt60(m, "Bgt60");
        bgt60
        .def("init", &Bgt60::init, "Initialization function")
        .def("deinit", &Bgt60::deinit, "De-initialize function")
        .def("getMotion", &Bgt60::getMotion, "Function to detect moving target")
        .def("getDirection", &Bgt60::getDirection, "Function to detect direction of \
                                                    moving target")
        .def("disableInterrupt", &Bgt60::disableInterrupt, "Disable interrupt");
    
    // Wrapping variables that are arguements to member functions and are defined as enum
    py::enum_<bgt60::Error_t>(bgt60, "Error_t", py::arithmetic())
        .value("OK",bgt60::Error_t::OK)
        .value("INTF_ERROR",bgt60::Error_t::INTF_ERROR)
        .value("CONF_ERROR",bgt60::Error_t::CONF_ERROR)
        .value("READ_ERROR",bgt60::Error_t::READ_ERROR)
        .value("WRITE_ERROR",bgt60::Error_t::WRITE_ERROR)
        .export_values();

    py::enum_<Bgt60::Motion_t>(bgt60, "Motion_t", py::arithmetic())
        .value("NO_MOTION", Bgt60::Motion_t::NO_MOTION)
        .value("MOTION", Bgt60::Motion_t::MOTION)
        .export_values();
    
    py::enum_<Bgt60::Direction_t>(bgt60, "Direction_t", py::arithmetic())
        .value("NO_DIR", Bgt60::Direction_t::NO_DIR)
        .value("APPROACHING", Bgt60::Direction_t::APPROACHING)
        .value("DEPARTING", Bgt60::Direction_t::DEPARTING)
        .export_values();

    // Wrapper for child Bgt60Rpi class
    py::class_<Bgt60Rpi, Bgt60> bgt60rpi(m, "Bgt60Rpi", py::multiple_inheritance());
    bgt60rpi.def(py::init<uint8_t, uint8_t>());

    m.def("setInterrupt", [](Bgt60Rpi radarShieldObj){
        Error_t err_int = OK;
        err_int = radarShieldObj).enableInterrupt(cBackF);
        return err_int;
    });

    m.def("checkIntStats", [](std::function<bool(void)> &py_callback){
        bool flag_stat = 0;
        if(int_flag == 1)
            flag_stat = py_callback();
        return flag_stat;   
    });

}
#endif /** BGT60_FRAMEWORK **/