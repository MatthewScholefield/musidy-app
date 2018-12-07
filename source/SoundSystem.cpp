
#include "SoundSystem.hpp"

static int processAudio(const void *inputBuffer, void *outputBuffer, unsigned long numFrames,
                        const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
                        void *userData) {
    const SoundSystem::AudioCallback &audioGenerator = *reinterpret_cast<SoundSystem::AudioCallback *> (userData);
    audioGenerator((float *) outputBuffer, numFrames);
    return 0;
}

SoundSystem::SoundSystem(const SoundSystem::AudioCallback &onAudio) :
        audioCallback(onAudio), autoSystem(), system(portaudio::System::instance()),
        inputDev(system.defaultInputDevice()), outputDev(system.defaultOutputDevice()),
        inputParams(inputDev, numChanIn, portaudio::FLOAT32, true, inputDev.defaultLowInputLatency(), nullptr),
        outputParams(outputDev, numChanOut, portaudio::FLOAT32, true, outputDev.defaultLowOutputLatency(), nullptr),
        streamParams(inputParams, outputParams, sampleRate, chunkSize, paNoFlag),
        stream(streamParams, processAudio, (void *) &this->audioCallback) {
    stream.start();
}

SoundSystem::~SoundSystem() {
    stream.stop();
}
