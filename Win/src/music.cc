#include <iostream>
#include <windows.h>
#include <string>
#include <mmsystem.h>

//Compiling command: g++ .\music.cc -o music.exe -static-libstdc++ -lwinmm -static-libgcc

/**
* @brief Outputs instructions and opens or stops the music file accordingly
*
* @return -1 Value that exits the whole program
*/
int MusicPlayer() {
    while (1==1) {
        
        // First input, PLAY or EXIT
        while (2==2) {
            std::cout << "Input \"PLAY\" to play the song, input \"EXIT\" to exit program\n";
            std::string input1;
            getline(std::cin, input1);
            if (input1 == "EXIT") {
                std::cout << "Exiting program...\n";
                return -1;
            } else if(input1 == "PLAY" ) {
                std::cout << "Playing music\n";
                PlaySound(TEXT(".music/InconvenienceStoreTheme.wav"), NULL, SND_ASYNC | SND_LOOP);
            } else {
                std::cout << " Wrong input, did you input PLAY or play?\n";
            }
        }
       
        // Second input, STOP or EXIT, dont input anything so the program keeps going
        while(3==3) {
            std::cout << "Input \"STOP\" to stop music, or \"EXIT\" to exit program\n";
            std::string input2;
            getline(std::cin, input2);
            if (input2 == "STOP") {
                PlaySound(0, 0, 0);
                std::cout << "Stopped music\n";
            } else if (input2 == "EXIT") {
                std::cout << "Exiting program...\n";
                return -1;
            } else {
                std::cout << " Wrong input, did you input Stop or stop?\n";
            }
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
