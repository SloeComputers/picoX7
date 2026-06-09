//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#undef RELEASE

#include "DX7/Synth.h"

static const unsigned DAC_FREQ         = 48000;                 //!< DAC sample rate (Hz)
static const unsigned TICK_RATE        = 375;                   //!< 6800 firmware tick (375 Hz)
static const unsigned SAMPLES_PER_TICK = DAC_FREQ / TICK_RATE;  //!< DAC buffer size (16 bit samples)

class PluginSynth : public DX7::Synth<16>
{
public:
   PluginSynth()
   {
      programChange(0, 0);
   }

   SIG::Signal sample() override
   {
      if (--samples_to_tick < 0)
      {
         samples_to_tick = SAMPLES_PER_TICK - 1;
         tick();
      }

      int32_t value = getSample();

      return ((value << 16) >> 16) / 32768.0;
   }

private:
   signed samples_to_tick{};
};

MIDI::Synth* MIDI::Synth::construct()
{
   return new PluginSynth();
}
