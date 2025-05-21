#include "MenuState.hpp"

MenuState::MenuState(std::shared_ptr<GameData> data)
    : _data(data), robotoFont(nullptr), menuMusic(nullptr) {
}

void MenuState::Init()
{
    // £adowanie tekstur przez AssetManagera
    _data->assetManager->loadTexture("background_2", BACKGROUND_TEXTURE_2);
    _data->assetManager->loadTexture("play_button", PLAY_BUTTON);

    _data->assetManager->loadFont("robotoFont", ROBOTO_FONT);
    robotoFont = &_data->assetManager->getFont("robotoFont");

    _data->soundManager->loadMusic("menuMusic", MENU_MUSIC);
    menuMusic = &_data->soundManager->getMusic("menuMusic");

    menuMusic->looping = true;
    PlayMusicStream(*menuMusic);
}

void MenuState::HandleInput()
{
    Texture2D& playButtonTex = _data->assetManager->getTexture("play_button");

    float btnWidth = playButtonTex.width * buttonScale;
    float btnHeight = playButtonTex.height * buttonScale;

    Rectangle playButtonRect = {
        (float)(WINDOW_WIDTH / 2 - btnWidth / 2),
        (float)(WINDOW_HEIGHT / 2 - btnHeight / 2),
        btnWidth,
        btnHeight
    };

    if (_data->inputManager->isRectClicked(playButtonRect, MOUSE_LEFT_BUTTON))
    {
        // PrzejdŸ do GameState
        _data->machine.AddState(std::make_unique<GameState>(_data), true);
    }
}

void MenuState::Update(float dt)
{
    UpdateMusicStream(*menuMusic);
}

void MenuState::Draw(float dt)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // T³o
    Texture2D& backgroundTex = _data->assetManager->getTexture("background_2");
    DrawTexture(backgroundTex, 0, 0, WHITE);

    // Przycisk
    Texture2D& playButtonTex = _data->assetManager->getTexture("play_button");

    float btnWidth = playButtonTex.width * buttonScale;
    float btnHeight = playButtonTex.height * buttonScale;
    int posX = WINDOW_WIDTH / 2 - btnWidth / 2;
    int posY = WINDOW_HEIGHT / 2 - btnHeight / 2;

    DrawTextureEx(playButtonTex, { (float)posX, (float)posY }, 0.0f, buttonScale, WHITE);

    // Napis nad przyciskiem
    const char* infoText = "Nacisnij guzik, aby wystartowac gre";

    // Mierzenie szerokoœci napisu
    Vector2 textSize = MeasureTextEx(*robotoFont, infoText, (float)fontSize, 1.0f);
    int textPosX = WINDOW_WIDTH / 2 - (int)textSize.x / 2;
    int textPosY = posY - fontSize - 20; // 20px odstêpu nad przyciskiem

    DrawTextEx(*robotoFont, infoText, { (float)textPosX, (float)textPosY }, (float)fontSize, 1.0f, DARKGRAY);

    EndDrawing();
}