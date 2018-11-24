
#include "SoundSystem.hpp"

static int processAudio(const void *input_buffer, void *output_buffer, unsigned long num_frames,
                        const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags status_flags,
                        void *user_data) {
  const SoundSystem::AudioCallback &audio_generator = *reinterpret_cast<SoundSystem::AudioCallback *> (user_data);
  audio_generator((float *) output_buffer, num_frames);
  return 0;
}

SoundSystem::SoundSystem(const SoundSystem::AudioCallback &on_audio) :
    audio_callback_(on_audio), auto_system_(), system_(portaudio::System::instance()),
    input_dev_(system_.defaultInputDevice()), output_dev_(system_.defaultOutputDevice()),
    input_params_(input_dev_, kNumChanIn, portaudio::FLOAT32, true, input_dev_.defaultLowInputLatency(), nullptr),
    output_params_(output_dev_, kNumChanOut, portaudio::FLOAT32, true, output_dev_.defaultLowOutputLatency(), nullptr),
    stream_parameters_(input_params_, output_params_, kSampleRate, kChunkSize, paNoFlag),
    stream_(stream_parameters_, processAudio, (void *) &this->audio_callback_) {
  stream_.start();
}

SoundSystem::~SoundSystem() {
  stream_.stop();
}
