#pragma once

#include <raylib.h>
#include "State.hpp"
#include "GameState.hpp"
#include "GameConfig.hpp"
#include "GameData.hpp"

class MenuState : public State
{
public:
    MenuState(std::shared_ptr<GameData> data);

    void Init() override;
    void HandleInput() override;
    void Update(float dt) override;
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;

    Font* robotoFont = nullptr;
    Music* menuMusic = nullptr;

    float buttonScale = 0.5f;
    int fontSize = 42;
};