#include "GUI.hpp"

GUI::GUI(char const* window_title, int window_w, int window_h)
{
    SDL_Init(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow(window_title, 0, 0, window_w, window_h, SDL_WINDOW_SHOWN);
    
    uint32_t render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    int render_index = -1;
    this->rend = SDL_CreateRenderer(this->window, render_index, render_flags);

}

GUI::~GUI()
{
    SDL_DestroyRenderer(this->rend);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void GUI::update(char* const data, bool* draw_flag, int scale)
{

}

bool GUI::getInput(bool* keypad)
{
    bool quit = false;
    SDL_EVENT event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
            break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_ESCAPE:
                        quit = true;
                    break;

                    case SDL_SCANCODE_1:
                        keypad[1] = true;
                    break;

                    case SDL_SCANCODE_2:
                        keypad[2] = true;
                    break;

                    case SDL_SCANCODE_3:
                        keypad[3] = true;
                    break;

                    case SDL_SCANCODE_4:
                        keypad[0xC] = true;
                    break;

                    case SDL_SCANCODE_Q:
                        keypad[4] = true;
                    break;

                    case SDL_SCANCODE_W:
                        keypad[5] = true;
                    break;

                    case SDL_SCANCODE_E:
                        keypad[6] = true;
                    break;

                    case SDL_SCANCODE_R:
                        keypad[0xD] = true;
                    break;

                    case SDL_SCANCODE_A:
                        keypad[7] = true;
                    break;

                    case SDL_SCANCODE_S:
                        keypad[8] = true;
                    break;

                    case SDL_SCANCODE_D:
                        keypad[9] = true;
                    break;

                    case SDL_SCANCODE_F:
                        keypad[0xE] = true;
                    break;
                    
                    case SDL_SCANCODE_Z:
                        keypad[0xA] = true;
                    break;

                    case SDL_SCANCODE_X:
                        keypad[0] = true;
                    break;

                    case SDL_SCANCODE_C:
                        keypad[0xB] = true;
                    break;

                    case SDL_SCANCODE_V:
                        keypad[0xF] = true;
                    break;
                }
            break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDL_SCANCODE_1:
                        keypad[1] = false;
                    break;

                    case SDL_SCANCODE_2:
                        keypad[2] = false;
                    break;

                    case SDL_SCANCODE_3:
                        keypad[3] = false;
                    break;

                    case SDL_SCANCODE_4:
                        keypad[0xC] = false;
                    break;

                    case SDL_SCANCODE_Q:
                        keypad[4] = false;
                    break;

                    case SDL_SCANCODE_W:
                        keypad[5] = false;
                    break;

                    case SDL_SCANCODE_E:
                        keypad[6] = false;
                    break;

                    case SDL_SCANCODE_R:
                        keypad[0xD] = false;
                    break;

                    case SDL_SCANCODE_A:
                        keypad[7] = false;
                    break;

                    case SDL_SCANCODE_S:
                        keypad[8] = false;
                    break;

                    case SDL_SCANCODE_D:
                        keypad[9] = false;
                    break;

                    case SDL_SCANCODE_F:
                        keypad[0xE] = false;
                    break;

                    case SDL_SCANCODE_Z:
                        keypad[0xA] = false;
                    break;

                    case SDL_SCANCODE_X:
                        keypad[0] = false;
                    break;

                    case SDL_SCANCODE_C:
                        keypad[0xB] = false;
                    break;

                    case SDL_SCANCODE_V:
                        keypad[0xF] = false;
                    break'
                }
            break;
                
        }
    }
    return quit;
}
