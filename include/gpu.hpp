#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>
#include <vram.hpp>

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Gpu
{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint32_t pixels[40000];

    std::array<Color, 256> palette;

    Vram vram;

    uint16_t key;
    bool keyPressed;

    bool running;


    Gpu();
    ~Gpu();

    void reset();
    bool init();
    void handleEvents();
    void drawScreen();
    uint16_t getKey();
};