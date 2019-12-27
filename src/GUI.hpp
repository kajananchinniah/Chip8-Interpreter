#pragma once

#include <cstdint>
#include <SDL2/SDL.h>

class GUI
{
    public:
        GUI(char const* window_title, int window_w, int window_h);
        ~GUI();
        bool getInput(bool* keypad);
    
    private:
        SDL_Window* window;
        SDL_Renderer* rend;

}
