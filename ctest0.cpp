#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GameController* controller = nullptr;
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            controller = SDL_GameControllerOpen(i);
            if (controller) {
                std::cout << "Found game controller: " << SDL_GameControllerName(controller) << std::endl;
                break;
            }
        }
    }

    if (!controller) {
        std::cerr << "No game controller found!" << std::endl;
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    std::cout << "Button pressed: " << SDL_GameControllerGetStringForButton(
                        static_cast<SDL_GameControllerButton>(event.cbutton.button)) << std::endl;
                    break;
                case SDL_CONTROLLERAXISMOTION:
                    std::cout << "Axis moved: " << SDL_GameControllerGetStringForAxis(
                        static_cast<SDL_GameControllerAxis>(event.caxis.axis)) 
                              << " Value: " << event.caxis.value << std::endl;
                    break;
                case SDL_CONTROLLERSENSORUPDATE:
                    std::cout << "Sensor updated: " << event.csensor.sensor << std::endl;
                    break;
            }
        }

        SDL_Delay(10);
    }

    SDL_GameControllerClose(controller);
    SDL_Quit();
    return 0;
}
