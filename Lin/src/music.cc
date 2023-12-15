/**
 * @file music.cc
 * @author Noah Lorenzo Díaz
 * @date 13-12-2023
 * @brief Program prototype to replicate a music player
 * 
 */

#include <iostream>
#include <SDL.h>

void playAudio();

#include "utils.cc"
#include "menu.cc"

/**
 * @brief Plays the audio.
 *
 * Calls all the functions needed for the playing of songs
 *
 */
void playAudio() {
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
        callMenu(audioDevice, audioBuffer, audioBufferLength, menu);
    }
    cleanup(audioDevice, audioBuffer);
    SDL_Quit();
}



int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    errorMessage("Couldn't initialize SDL");
    return -1;
    }
    playAudio();
    return 0;
}
