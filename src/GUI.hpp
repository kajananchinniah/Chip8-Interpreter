#pragma once

#include <cstdint>
#include <SDL2/SDL.h>
#include <iostream>

class GUI
{
    public:
        GUI(char const* window_title, int window_w, int window_h);
        ~GUI();
        bool getInput(bool* keypad);
        void update(uint8_t data[64][32], bool* draw_flag, int scale);

    private:
        SDL_Window* window;
        SDL_Renderer* rend;

};
