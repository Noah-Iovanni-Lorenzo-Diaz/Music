#include <iostream>
#include <SDL.h>

void errorMessage(const std::string& message) {
    std::cerr << message << ": " << SDL_GetError() << std::endl;
}

void cleanup(SDL_AudioDeviceID audioDevice, Uint8* wavBuffer) {
    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
}

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

/**

#include "iooverload.cc"
void menu() {
   timeElapsed();
   enum Options {
        PLAY,
        PAUSE,
        STOP,
        EXIT,
    };
    
    Options option{};
    std::cin >> option;

    switch(option) {
        case PLAY: {
        std::cout << PLAY << std::endl;
        } break;

        case PAUSE: {
        std::cout << PAUSE << std::endl;  
        } break;

        case STOP: {
        std::cout << STOP << std::endl;
        } break;

        case EXIT: {
        std::cout << EXIT << std::endl;
        } break;

        default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
}
*/

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
        errorMessage("Couldn't load test.wav");
        SDL_Quit();
    }
    
    //Create Audio Device
    SDL_AudioDeviceID audioDevice = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (audioDevice == 0) {
        errorMessage("Couldn't open audio device");
        SDL_Quit();
    }
    
    SDL_QueueAudio(audioDevice, audioBuffer, audioBufferLength);
    SDL_PauseAudioDevice(audioDevice, 0);
    while (audioPosition < audioBufferLength) {
        std::string option;
        std::cin >> option;
        if (option == "STOP") {
            break;
        }
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
}
