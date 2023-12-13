#include <iostream>
#include <SDL.h>

#include "utils.cc"
#include "menu.cc"

// Global variable to track the position in the audio data
Uint32 audioPosition = 0;

// Audio callback function
void audioCallback(void* userdata, Uint8* stream, int len) {
    // Copy audio data from the buffer to the stream
    SDL_memset(stream, 0, len);
    if (audioPosition < len) {
        SDL_memcpy(stream, reinterpret_cast<Uint8*>(userdata) + audioPosition, len - audioPosition);
        audioPosition += len;
    }
}

void manageAudio() {
    //Audio specifications
    SDL_AudioSpec want, have;

    want.freq = 44100;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.samples = 1024;

    //Load Audio
    Uint8* audioBuffer;
    Uint32 audioBufferLength;
    
    if (SDL_LoadWAV("../.music/audio.wav", &want , &audioBuffer, &audioBufferLength) == nullptr) {
        if (SDL_LoadWAV(".music/audio.wav", &want , &audioBuffer, &audioBufferLength) == nullptr) {
            errorMessage("Couldn't load test.wav");
            SDL_Quit();
            exit(EXIT_SUCCESS);
        }
    }
    
    //Create Audio Device
    SDL_AudioDeviceID audioDevice = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (audioDevice == 0) {
        errorMessage("Couldn't open audio device");
        cleanup(audioDevice, audioBuffer);
        exit(EXIT_SUCCESS);
    }
    
    SDL_QueueAudio(audioDevice, audioBuffer, audioBufferLength);

    //Song loop
    while (true) {
        callMenu(audioDevice, audioBuffer, menu);
    }
    cleanup(audioDevice, audioBuffer);
    SDL_Quit();
}



int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    errorMessage("Couldn't initialize SDL");
    return -1;
    }
    manageAudio();
    return 0;
}
