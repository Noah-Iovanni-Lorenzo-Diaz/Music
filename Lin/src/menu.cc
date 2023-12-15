/**
 * @file menu.cc
 * @author Noah Lorenzo Díaz
 * @date 13-12-2023
 * @brief Everything related to the menu
 * 
 * @see 
 */

enum Menu {
        PLAY,
        PAUSE,
        REPLAY,
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
    if (menu == REPLAY) return option == "REPLAY";
    if (menu == EXIT) return option == "EXIT";
}

/**
 * @brief Displays menu and handles input choices
 *
 *
 * @param audioDevice The ID of the audio device in use.
 * @param audioBuffer Holds the samples for the audio.
 * @param menu An enum with the menu options.
 */
void callMenu(SDL_AudioDeviceID audioDevice, Uint8* audioBuffer, Uint32 audioBufferLength, Menu menu) {
    std::cout << "Input PLAY to play song\nInput PAUSE to pause song\nInput EXIT to exit program\n";

    std::string option;
    std::cin >> option;
       
    if(option == PLAY) {
        std::cout << "\nPlaying song...\n" << std::endl;
        SDL_PauseAudioDevice(audioDevice, 0);
    } else if(option == PAUSE) {
        std::cout << "\nPausing song...\n" << std::endl;
        SDL_PauseAudioDevice(audioDevice, 1);
    } else if(option == EXIT) {
        std::cout << "\nExiting program...\n" << std::endl;
        cleanup(audioDevice, audioBuffer);
        SDL_Quit();
        exit(EXIT_SUCCESS);
    } else {
        std::cout << "\nWrong Input\n" << std::endl;
    }
}
