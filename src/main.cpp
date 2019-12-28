#include "Chip8.hpp"
#include "GUI.hpp"

int main(void)
{
    int scale = 10;
    int delay = 1;
    char const* file_path = "BC_test.ch8";

    GUI gui("Chip 8", DISP_LENGTH*10, DISP_WIDTH*10);
    Chip8 chip8;
    chip8.load(file_path);
    bool quit = false;
    while (quit == false)
    {
        quit = gui.getInput(chip8.keypad);
        chip8.cycle();
        if (chip8.draw_flag == true)
            gui.update(chip8.display, &chip8.draw_flag, scale);
        
        SDL_Delay(10);
    }

    return 0;

}
