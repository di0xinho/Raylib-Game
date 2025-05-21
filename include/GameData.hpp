#pragma once

#include "StateMachine.hpp"
#include "InputManager.hpp"
#include "AssetManager.hpp"
#include "SoundManager.hpp"
#include <memory>

/// Struktura przechowuj¹ca wszystkie kluczowe komponenty gry
struct GameData
{
    StateMachine machine;                              /// Maszyna stanów gry
    std::shared_ptr<InputManager> inputManager;        /// Manager wejœcia
    std::shared_ptr<AssetManager> assetManager;        /// Manager zasobów (tekstury, czcionki)
    std::shared_ptr<SoundManager> soundManager;        /// Manager dŸwiêku
};