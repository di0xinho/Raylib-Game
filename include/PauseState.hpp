#pragma once

#include <raylib.h>
#include <memory>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"

/// Stan gry odpowiadaj¹cy za ekran pauzy
class PauseState : public State {
public:
    /// Tworzy stan pauzy, przekazuj¹c wskaŸnik do danych gry
    PauseState(std::shared_ptr<GameData> data);

    /// Inicjalizuje zasoby wymagane przez stan pauzy
    void Init() override;

    /// Obs³uguje wejœcie u¿ytkownika podczas pauzy
    void HandleInput() override;

    /// Aktualizuje logikê stanu pauzy
    void Update(float dt) override;

    /// Rysuje ekran pauzy
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;

    const char* titleText = "PAUZA";
    const char* instructionText = "Nacisnij klawisz Escape lub P, aby kontynuowac rozgrywke";
};