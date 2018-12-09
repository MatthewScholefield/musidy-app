#pragma once

#include <portaudiocpp/PortAudioCpp.hxx>
#include <functional>
#include <portaudio.h>

/**
 * Wrapper for Portaudio sound system
 */
class SoundSystem {
public:
    static const int numChanIn = 0;  // Number of input channels
    static const int numChanOut = 2;  // Number of output channels
    static const int sampleRate = 44100;  // Audio framerate
    static const int chunkSize = 512;  // Number of samples in each chunk of audio

    /**
     * Function pointer to audio generator callback
     * parameters:
     *     - float*: Output audio array (2 channels)
     *     - size_t: Number of output samples (each sample is 2 floats)
     */
    using AudioCallback = std::function<void(float *, size_t)>;

    /**
     * Create a new sound system
     * @param onAudio A function to run when a new audio chunk is received
     */
    explicit SoundSystem(const AudioCallback &onAudio);

    /**
     * Close audio devices and destroy the sound system
     */
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
