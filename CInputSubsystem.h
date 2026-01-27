#pragma once

#ifndef C_INPUTSUBSYSTEM_H
#define C_INPUTSUBSYSTEM_H

#include "ISubsystem.h"
#include <iostream>

enum class EButtonState { UP, DOWN, JUST_PRESSED };

class CInputSubsystem : public ISubsystem
{
public:
    CInputSubsystem(): shouldQuit(false) {}

    ~CInputSubsystem()
    {
        Shutdown();
    }
    
    bool Start() override
    {
        SDL_Log("Input subsystem started");
        return true;
    }

    void Shutdown() override
    {
        SDL_Log("Input subsystem shutdown");
    }

    void Update(float deltaSeconds) override
    {
        (void)deltaSeconds;
    }

    bool ShouldQuit() const { return shouldQuit; }

    void ProcessEvent(const SDL_Event* event)
    {
        if (event->type == SDL_EVENT_QUIT) 
            shouldQuit = true;  /* end the program, reporting success to the OS. */
        else if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_SPACE)
        {
            //MIXING JUST PRESSED AND DOWN!!!
            if (spaceState == EButtonState::UP)
                spaceState = EButtonState::JUST_PRESSED;
        }
        else if (event->type == SDL_EVENT_KEY_UP && event->key.key == SDLK_SPACE)
            spaceState = EButtonState::UP;
    }

    EButtonState GetSpaceState() const { return spaceState; }
private:
    bool shouldQuit;
    EButtonState spaceState = EButtonState::UP;
};

#endif
