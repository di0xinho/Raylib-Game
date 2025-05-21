#pragma once

#include "StateMachine.hpp"
#include "InputManager.hpp"
#include "AssetManager.hpp"
#include "SoundManager.hpp"
#include <memory>

/// Struktura przechowuj�ca wszystkie kluczowe komponenty gry
struct GameData
{
    StateMachine machine;                              /// Maszyna stan�w gry
    std::shared_ptr<InputManager> inputManager;        /// Manager wej�cia
    std::shared_ptr<AssetManager> assetManager;        /// Manager zasob�w (tekstury, czcionki)
    std::shared_ptr<SoundManager> soundManager;        /// Manager d�wi�ku
};