enum Menu {
        PLAY,
        PAUSE,
        EXIT,
    };

Menu menu;

std::istream& operator>> (std::istream& in, Menu& menu) {
    int input{};
    in >> input; // input an integer

    menu = static_cast<Menu>(input);
    return in;
}

bool operator== (std::string option, Menu menu) {
    if (menu == PLAY) return option == "PLAY";
    if (menu == PAUSE) return option == "PAUSE";
    if (menu == EXIT) return option == "EXIT";
}

void callMenu(SDL_AudioDeviceID audioDevice, Uint8* audioBuffer, Menu menu) {
    std::string option;
    std::cin >> option;
       
    if(option == PLAY) {
        std::cout << "Playing song..." << std::endl;
        SDL_PauseAudioDevice(audioDevice, 0);
    } else if(option == PAUSE) {
        std::cout << "Pausing song..." << std::endl;
        SDL_PauseAudioDevice(audioDevice, 1);
    } else if(option == EXIT) {
        std::cout << "Exiting program..." << std::endl;
        cleanup(audioDevice, audioBuffer);
        SDL_Quit();
        exit(EXIT_SUCCESS);
    } else {
        std::cout << "Wrong Input" << std::endl;
    }
}
