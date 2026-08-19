#include <gpu.hpp>

#include <cpu.hpp>

Gpu::Gpu()
{
    window = nullptr;
    renderer = nullptr;
    texture = nullptr;
    reset();
    palette[0] = {0, 0, 0};
    palette[1] = {240, 240, 240};
    palette[2] = {240, 0, 0};
    palette[3] = {240, 240, 0};
    palette[4] = {0, 240, 0};
    palette[5] = {0, 240, 240};
    palette[6] = {0, 0, 240};
    palette[7] = {240, 0, 240};
}

Gpu::~Gpu()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);

    if (texture)
        SDL_DestroyTexture(texture);

    SDL_Quit();
}

void Gpu::reset()
{
    running = false;
    keyPressed = false;
    key = 0x0000;
}

bool Gpu::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("cpu16", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256 * 3, 256 * 3, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        std::cerr << "Renderer error: " << SDL_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        256, 256
    );

    if (!texture) {
        std::cerr << "Texture error: " << SDL_GetError() << std::endl;
        return false;
    }

    running = true;

    return true;
}

void Gpu::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            running = false;

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.repeat == 0)
            {
                key = event.key.keysym.sym;
                keyPressed = true;
            }
        }

        if (event.type == SDL_KEYUP)
        {
            keyPressed = false;
        }
    }
}

void Gpu::getKey()
{
    SDL_Event event;
    while (true)
    {
        SDL_WaitEvent(&event);

        if (event.type == SDL_KEYDOWN)
            key = event.key.keysym.sym;
        if (event.type == SDL_QUIT)
        {
            running = false;
            return;
        }
    }
}

void Gpu::drawScreen()
{
    if (!renderer)
    {
        std::cerr << "ERROR : renderer == nullptr" << std::endl;
        return;
    }

    if (!texture)
    {
        std::cerr << "ERROR : texture == nullptr" << std::endl;
        return;
    }

    for (int i = 0; i < 65535; i++)
    {
        uint16_t colorIndex = vram.data[i];

        Color color = palette[colorIndex];

        pixels[i] =
            (0xFF << 24) |
            (color.r << 16) |
            (color.g << 8) |
            color.b;
    }

    SDL_UpdateTexture(
        texture,
        nullptr,
        pixels,
        256 * sizeof(uint32_t)
    );

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Gpu::drawChar(uint16_t mvac, Cpu& cpu)
{
    uint16_t startPos = cursorPos;

    uint16_t address = mvac * 8;

    for (int row = 0; row < 8; row++)
    {
        uint8_t line = cpu.hd->read8(0xFFFF, address + row);

        for (int col = 0; col < 8; col++)
        {
            bool pixel = (line >> (7 - col)) & 0x01;

            cpu.bus->vram->write8(
                startPos + row * 256 + col,
                pixel ? 1 : 0
            );
        }
    }
}

uint8_t Gpu::convertKey(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_a: return 0;
        case SDLK_b: return 1;
        case SDLK_c: return 2;
        case SDLK_d: return 3;
        case SDLK_e: return 4;
        case SDLK_f: return 5;
        case SDLK_g: return 6;
        case SDLK_h: return 7;
        case SDLK_i: return 8;
        case SDLK_j: return 9;
        case SDLK_k: return 10;
        case SDLK_l: return 11;
        case SDLK_m: return 12;
        case SDLK_n: return 13;
        case SDLK_o: return 14;
        case SDLK_p: return 15;
        case SDLK_q: return 16;
        case SDLK_r: return 17;
        case SDLK_s: return 18;
        case SDLK_t: return 19;
        case SDLK_u: return 20;
        case SDLK_v: return 21;
        case SDLK_w: return 22;
        case SDLK_x: return 23;
        case SDLK_y: return 24;
        case SDLK_z: return 25;
        case SDLK_1: return 26;
        case SDLK_2: return 27;
        case SDLK_3: return 28;
        case SDLK_4: return 29;
        case SDLK_5: return 30;
        case SDLK_6: return 31;
        case SDLK_7: return 32;
        case SDLK_8: return 33;
        case SDLK_9: return 34;
        case SDLK_0: return 35;
        case SDLK_COMMA: return 36;
        case SDLK_PERIOD: return 37;
        case SDLK_SPACE: return 38;
        case SDLK_SLASH: return 39;
        case SDLK_LEFTBRACKET: return 40;
        case SDLK_RIGHTBRACKET: return 41;
        case SDLK_BACKSLASH: return 42;
        case SDLK_BACKSPACE: return 43;
        case SDLK_LGUI: return 44;
        case SDLK_RETURN: return 45;

        default: return 42;
    }
}