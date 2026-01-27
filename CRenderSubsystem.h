#pragma once

#ifndef CRENDER_SUBSYSTEM_H
#define CRENDER_SUBSYSTEM_H

#include "ISubsystem.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class CRenderSubsystem : public ISubsystem
{
public:
    CRenderSubsystem(): window(nullptr), renderer(nullptr) {}

    ~CRenderSubsystem() override
    {
        Shutdown();
    }
    
    bool Start() override
    {
        if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, 0, &window, &renderer)) {
            SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
            return false;
        }

        SDL_Log("Render subsystem started");
        
        return true;
    }

    void Shutdown() override
    {
        SDL_Log("Render subsystem shutdown");
        
        window = nullptr;
        renderer = nullptr;
    }

    void Update(float deltaSeconds) override
    {
        (void)deltaSeconds;
    }

    void Render(float averageFPS, int red, int green, int blue)
    {
        char message[64];
        SDL_snprintf(message, 64, "FPS: %f\n", averageFPS);
        
        int w = 0, h = 0;
        float x, y;
        const float scale = 4.0f;
        
        /* Center the message and scale it up */
        SDL_GetRenderOutputSize(renderer, &w, &h);
        SDL_SetRenderScale(renderer, scale, scale);
        x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
        y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

        /* Draw the message */
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(renderer, x, y, message);
        SDL_RenderPresent(renderer);
    }
    
    SDL_Renderer* GetRenderer() { return renderer; }
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
