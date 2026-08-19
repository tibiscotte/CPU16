#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>
#include <vram.hpp>
#include <array>

class Cpu;

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Gpu
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    uint32_t pixels[65535];

    std::array<Color, 256> palette;

    Vram vram;

    SDL_Keycode key;
    bool keyPressed;

    bool running;

    uint16_t cursorPos;

    Gpu();
    ~Gpu();

    void reset();
    bool init();
    void handleEvents();
    void drawScreen();
    void drawChar(uint16_t mvac, Cpu &cpu);
    uint8_t convertKey(SDL_Keycode key);
    void getKey();
};