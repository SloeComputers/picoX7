#------------------------------------------------------------------------------
# Copyright (c) 2023 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(picoX7
        LANGUAGES CXX C ASM
        VERSION 0.21)

include(CTest)

set(HWR_CONFIG picoX7)

add_subdirectory(Platform)
add_subdirectory(Source)
add_subdirectory(docs/Research)
