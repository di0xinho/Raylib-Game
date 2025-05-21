#include "PauseState.hpp"

PauseState::PauseState(std::shared_ptr<GameData> data) : _data(data) {}

void PauseState::Init() {}

void PauseState::Update(float dt) {}

void PauseState::HandleInput() {
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
        // Zdejmij stan pauzy (wróæ do poprzedniego stanu)
        _data->machine.RemoveState();
    }
}

void PauseState::Draw(float dt) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // T³o pó³przezroczyste
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
    // Tytu³
    DrawText(titleText, GetScreenWidth() / 2 - MeasureText(titleText, 60) / 2, 200, 60, WHITE);
    // Instrukcja
    DrawText(instructionText, GetScreenWidth() / 2 - MeasureText(instructionText, 30) / 2, 300, 30, GRAY);

    EndDrawing();
}