#pragma once

#include <portaudiocpp/PortAudioCpp.hxx>
#include <functional>
#include <portaudio.h>


class SoundSystem {
public:
  static const int kNumChanIn = 0;
  static const int kNumChanOut = 2;
  static const int kSampleRate = 44100;
  static const int kChunkSize = 512;

  /**
   * Function pointer to audio generator callback
   * parameters:
   *     - float*: Output audio array (2 channels)
   *     - size_t: Number of output samples (each sample is 2 floats)
   */
  using AudioCallback = std::function<void(float *, size_t)>;
  explicit SoundSystem(const AudioCallback &on_audio);
  ~SoundSystem();

private:
  AudioCallback audio_callback_;

  portaudio::AutoSystem auto_system_;
  portaudio::System &system_;
  portaudio::Device &input_dev_, &output_dev_;

  portaudio::DirectionSpecificStreamParameters input_params_, output_params_;
  portaudio::StreamParameters stream_parameters_;
  portaudio::FunCallbackStream stream_;
};
