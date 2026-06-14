//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#undef RELEASE

#include "DX7/Synth.h"
#include "SIG/ReSample.h"

class PluginSynth : public DX7::Synth</* NUM_VOICES */ 16>
{
public:
   PluginSynth()
   {
      programChange(0, 0);
   }

   //! Get DX7 rate sample
   SIG::Signal operator()()
   {
      constexpr unsigned SAMPLES_PER_TICK = DX7::SAMPLE_RATE / DX7::TICK_RATE;

      if (--samples_to_tick < 0)
      {
         samples_to_tick = SAMPLES_PER_TICK - 1;
         tick();
      }

      int32_t value = getSampleSingle();

      return ((value << 16) >> 16) / 32768.0;
   }

private:
   void setSampleRate(unsigned sample_rate_) override
   {
      re_sample.setOutRate(sample_rate_);
   }

   //! Get DAW rate sample
   SIG::Signal sample() override
   {
      return re_sample();
   }

   signed samples_to_tick{0};

   SIG::ReSample<PluginSynth,/* N */ 16> re_sample{*this, DX7::SAMPLE_RATE};
};

MIDI::Synth* MIDI::Synth::construct()
{
   return new PluginSynth();
}
