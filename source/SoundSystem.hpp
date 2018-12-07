#pragma once

#include <portaudiocpp/PortAudioCpp.hxx>
#include <functional>
#include <portaudio.h>


class SoundSystem {
public:
  static const int numChanIn = 0;
  static const int numChanOut = 2;
  static const int sampleRate = 44100;
  static const int chunkSize = 512;

  /**
   * Function pointer to audio generator callback
   * parameters:
   *     - float*: Output audio array (2 channels)
   *     - size_t: Number of output samples (each sample is 2 floats)
   */
  using AudioCallback = std::function<void(float *, size_t)>;
  explicit SoundSystem(const AudioCallback &onAudio);
  ~SoundSystem();

private:
  AudioCallback audioCallback;

  portaudio::AutoSystem autoSystem;
  portaudio::System &system;
  portaudio::Device &inputDev, &outputDev;

  portaudio::DirectionSpecificStreamParameters inputParams, outputParams;
  portaudio::StreamParameters streamParams;
  portaudio::FunCallbackStream stream;
};
