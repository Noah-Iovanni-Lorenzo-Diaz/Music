#include <iostream>
#include <windows.h>
#include <string>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

int MusicPlayer() {
    while (1==1) {
        std::cout << "Input PLAY to play the song, input EXIT to exit program\n";
        std::string input1;
        getline(std::cin, input1);
        if (input1 == "EXIT") {
            std::cout << "Exiting program...\n";
            return -1;
        } else if(input1 == "PLAY" ) {
            std::cout << "Playing music\n";
            PlaySound(TEXT("../InconvenienceStoreTheme.wav"), NULL, SND_ASYNC | SND_LOOP);
        }
        

        std::cout << "Input STOP to stop music, or EXIT to exit program\n";
        std::string input2;
        getline(std::cin, input2);
        if (input2 == "STOP") {
            PlaySound(0, 0, 0);
            std::cout << "Stopped music\n";
        } else if (input2 == "EXIT") {
            std::cout << "Exiting program...\n";
            return -1;
        }
    }
}

int main() {
    while(1==1){
        int value = MusicPlayer();
        if(value == -1) {
            break;
        }
    }  
    return 0;
}