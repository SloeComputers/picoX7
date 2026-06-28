#-------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

if(${PDK_NATIVE})

   add_executable(test_DX7
                  testMain.cpp
                  testSynth.cpp
                  testOps.cpp
                  testEgs.cpp
                  testEgsOpState.cpp
                  testEnvGen.cpp
                  testPitchEg.cpp
                  testSynth.cpp)

   target_link_libraries(test_DX7
      PRIVATE DX7 STB SIG_FL32)

   add_test(NAME test_DX7 COMMAND test_DX7)

endif()
