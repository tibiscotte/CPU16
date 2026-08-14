#include <gpu.hpp>

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

    window = SDL_CreateWindow("cpu16", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);

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
        200, 200
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
            key = event.key.keysym.sym;
            keyPressed = true;
        }
        if (event.type == SDL_KEYUP)
        {
            keyPressed = false;
        }
    }
}

uint16_t Gpu::getKey()
{
    SDL_Event event;
    while (true)
    {
        SDL_WaitEvent(&event);

        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
        if (event.type == SDL_QUIT)
        {
            running = false;
            return 0;
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

    for (int i = 0; i < 40000; i++)
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
        200 * sizeof(uint32_t)
    );

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}