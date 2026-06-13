//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#undef RELEASE

#include "DX7/Synth.h"

class PluginSynth : public DX7::Synth</* NUM_VOICES */ 16>
{
public:
   PluginSynth()
   {
      programChange(0, 0);
   }

   void setSampleRate(unsigned sample_rate_) override
   {
      sample_rate = sample_rate_;
   }

   SIG::Signal sample() override
   {
      // TODO re-sample
      return dx7_sample();
   }

private:
   SIG::Signal dx7_sample()
   {
      constexpr unsigned SAMPLES_PER_TICK = DX7::SAMPLE_RATE / DX7::TICK_RATE;

      if (--samples_to_tick < 0)
      {
         samples_to_tick = SAMPLES_PER_TICK - 1;
         tick();
      }

      int32_t value = getSample();

      return ((value << 16) >> 16) / 32768.0;
   }

   signed   samples_to_tick{0};
   unsigned sample_rate{};
};

MIDI::Synth* MIDI::Synth::construct()
{
   return new PluginSynth();
}
