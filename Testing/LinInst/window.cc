#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int ScreenWidth = 1200;
const int ScreenHeight = 800;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gImage = NULL;

SDL_Surface* gJPGSurface = NULL;

void errorMessage(std::string_view error, bool which) {
    switch (which)
    {
    case 0:
        std::cerr << error << " ERROR: " << SDL_GetError() << std::endl; 
        break;
    case 1:
        std::cerr << error << " ERROR: " << IMG_GetError() << std::endl;
    
    default:
        throw std::invalid_argument ("Invalid argument, only accepts a string and a bool (0 or 1)");
        break;
    }
}

bool init() {
    bool success = true;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        errorMessage("Couldn't initialize SDL", 0); 
        success = false;
    } else {
        gWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            errorMessage("Window could not be created!", 0); 
            success = false;
        } else {
            int imgFlags = IMG_INIT_JPG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                errorMessage("SDL_Image could not initialize!", 1);
                success = false;
            } else {
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;

    gJPGSurface = loadSurface("testimage.jpg");
    if (gJPGSurface == NULL) {
        errorMessage("Failed to load JPG image", 1);
        success = false;
    }
    return success;
}

SDL_Surface* loadSurface(std::string path) {
    SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        errorMessage("Unable to load image!", 1);
    } else {
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL) {
            errorMessage("Unable to optimize image!", 1);
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

void close() {
    //Deallocate surface
    SDL_FreeSurface( gJPGSurface );
    gJPGSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main (int argc, char* argv[]) {
    if (!init()) {
        std::cerr << "Failed to initialize!\n";
    } else {
        if (!loadMedia()) {
            std::cerr << "Failed to load media!\n";
        } else {
            bool quit = false;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e)!=0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                SDL_BlitSurface(gJPGSurface, NULL, gScreenSurface, NULL) ;
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    close();
    return 0;
}