/*
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "CGameEngine.h"

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    
    /* Create the window */
    if (!CGameEngine::GetInstance().Init())
    {
        SDL_Log("Failed to initialize Game Engine");
        return SDL_APP_FAILURE;
    }

    *appstate = nullptr;

    SDL_Log("Game Engine initialized");
    
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    (void)appstate;

    CGameEngine::GetInstance().GetInput()->ProcessEvent(event);
    
    if (CGameEngine::GetInstance().GetInput()->ShouldQuit()) 
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    (void)appstate;
    
    CGameEngine::GetInstance().Loop();

    if (CGameEngine::GetInstance().GetInput()->ShouldQuit())
    {
        SDL_Log("Quit requested");
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    (void)appstate;
     
    SDL_Log("SDL_AppQuit called with result: %d", result);
    CGameEngine::GetInstance().Shutdown();
}

