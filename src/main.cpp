#include "Chip8.hpp"
#include "GUI.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error: Input format is " << argv[0] << " rom_path\n";
        return 0;
    }

    int scale = 10;
    int delay = 4;
    char const* file_path = argv[1];

    GUI gui("Chip 8", DISP_LENGTH*scale, DISP_WIDTH*scale);
    Chip8 chip8;
    chip8.load(file_path);
    bool quit = false;
    while (quit == false)
    {
        quit = gui.getInput(chip8.keypad);
        chip8.cycle();
        if (chip8.draw_flag == true)
        {
            gui.update(chip8.display, &chip8.draw_flag, scale);
        }

        SDL_Delay(delay);
    }

    return 0;

}
