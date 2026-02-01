#pragma once

#ifndef CGAMEENGINE_H
#define CGAMEENGINE_H
#include "CCounter.h"
#include "CGameSubsystem.h"
#include "CInputSubsystem.h"
#include "CRenderSubsystem.h"

class CGameEngine
{
public:
    static CGameEngine& GetInstance()
    {
        static CGameEngine instance;
        return instance;
    }
    
    bool Init()
    {
        SDL_Log("Initializing Game Engine");

        renderSubsystem = std::make_unique<CRenderSubsystem>();
        inputSubsystem = std::make_unique<CInputSubsystem>();
        gameSubsystem = std::make_unique<CGameSubsystem>();

        gameSubsystem->SetInputSubsystem(inputSubsystem.get());
        
        if (!renderSubsystem->Start())
        {
            SDL_Log("Renderer subsystem could not be started");
            return false;
        }

        if (!inputSubsystem->Start())
        {
            SDL_Log("Input subsystem could not be started");
            return false;
        }

        if (!gameSubsystem->Start())
        {
            SDL_Log("GameSubsystem could not be started");
            return false;
        }
        
        counter.Start();

        SDL_Log("Game Engine initialized");

        return true;
    }

    void Loop()
    {
        counter.Tick();
        float deltaSeconds = counter.GetDeltaSeconds();
        
        renderSubsystem->Update(deltaSeconds);
        inputSubsystem->Update(deltaSeconds);
        gameSubsystem->Update(deltaSeconds);

        renderSubsystem->Render(gameSubsystem->GetAverageFPS(), gameSubsystem->GetAverageDeltaTime(), gameSubsystem->GetRed(), gameSubsystem->GetGreen(), gameSubsystem->GetBlue());
    }
    
    void Shutdown()
    {
        SDL_Log("Shutting down Game Engine");
        
        if (renderSubsystem)
        {
            renderSubsystem->Shutdown();
            renderSubsystem.reset();
        }
        
        if (inputSubsystem)
        {
            inputSubsystem->Shutdown();
            inputSubsystem.reset();
        }

        if (gameSubsystem)
        {
            gameSubsystem->Shutdown();
            gameSubsystem.reset();
        }

        SDL_Log("Game Engine shutdown");
    }

    CRenderSubsystem* GetRenderer() { return renderSubsystem.get(); }

    CInputSubsystem* GetInput() { return inputSubsystem.get(); }

    CGameSubsystem* GetGame() { return gameSubsystem.get(); }

private:
    CGameEngine() = default;
    
    ~CGameEngine() = default;
    
    std::unique_ptr<CRenderSubsystem> renderSubsystem;
    std::unique_ptr<CInputSubsystem> inputSubsystem;
    std::unique_ptr<CGameSubsystem> gameSubsystem;
    CCounter counter;
};

#endif