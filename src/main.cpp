#include "raylib.h"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include "MenuState.hpp"

int main()
{
    // Inicjalizacja okna gry
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_TITLE);
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    // Tworzenie instancji GameData
    std::shared_ptr<GameData> gameData = std::make_shared<GameData>();
    gameData->inputManager = std::make_shared<InputManager>();
    gameData->assetManager = std::make_shared<AssetManager>();
    gameData->soundManager = std::make_shared<SoundManager>();

    // Dodanie pocz�tkowego stanu (MenuState)
    gameData->machine.AddState(std::make_unique<MenuState>(gameData), true);

    // G��wna p�tla gry
    while (!WindowShouldClose())
    {
        // Przetwarzanie zmian stan�w
        gameData->machine.ProcessStateChanges();

        // Sprawdzanie i obs�uga aktywnego stanu
        auto& activeState = gameData->machine.GetActiveState();
        activeState->HandleInput();
        activeState->Update(GetFrameTime());
        activeState->Draw(GetFrameTime());
    }

    // Zwalnianie zasob�w

    // Usuni�cie wszystkich stan�w
    gameData->machine.Clear();

    // Reset wszystkich manager�w
    gameData->assetManager.reset();
    gameData->inputManager.reset();
    gameData->soundManager.reset();

    // Zamkni�cie urz�dzenia audio oraz okna
    CloseAudioDevice();
    CloseWindow();

    return 0;
}