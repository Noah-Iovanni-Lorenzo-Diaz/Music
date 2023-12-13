void errorMessage(const std::string& message) {
    std::cerr << message << ": " << SDL_GetError() << std::endl;
}

void cleanup(SDL_AudioDeviceID audioDevice, Uint8* wavBuffer) {
    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
}