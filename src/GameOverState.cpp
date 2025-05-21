#include "GameOverState.hpp"

// Konstruktor
GameOverState::GameOverState(std::shared_ptr<GameData> data, int finalScore, bool won)
    : _data(data), _finalScore(finalScore), _won(won) {}

void GameOverState::Init() {
    // Za�aduj tekstur� t�a ekranu ko�ca gry
    _data->assetManager->loadTexture("gameover", GAMEOVER_IMAGE);
    gameOverTexture = &_data->assetManager->getTexture("gameover");

    // Pobierz czcionk� (je�li nie jest za�adowana, nale�y j� za�adowa� wcze�niej - �adujemy j� jednak wcze�niej w menu gry)
    font = &_data->assetManager->getFont("robotoFont");

    // Wybierz i za�aduj odpowiedni d�wi�k w zale�no�ci od wyniku
    std::string soundKey = _won ? "levelPassedSound" : "levelFailedSound";
    std::string soundPath = _won ? LEVEL_PASSED_SOUND : LEVEL_FAILED_SOUND;
    _data->soundManager->loadSound(soundKey, soundPath);
    gameOverSound = &_data->soundManager->getSound(soundKey);

    // Odtw�rz d�wi�k ko�ca gry
    PlaySound(*gameOverSound);
}

void GameOverState::HandleInput() {
    // Restart gry po naci�ni�ciu klawisza R
    if (IsKeyPressed(KEY_R)) {
        _data->machine.AddState(std::make_unique<GameState>(_data), true);
    }
}

void GameOverState::Update(float dt) {
    // Brak logiki aktualizacji w tym stanie
}

void GameOverState::Draw(float dt) {
    BeginDrawing();
    ClearBackground(BLACK);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Rysuj tekstur� t�a GameOver (je�li jest dost�pna)
    if (gameOverTexture && gameOverTexture->id > 0) {
        DrawTexture(
            *gameOverTexture,
            screenWidth / 2 - gameOverTexture->width / 2,
            screenHeight / 2 - gameOverTexture->height / 2 - 60,
            WHITE
        );
    }

    // Wy�wietl odpowiedni komunikat
    const char* message = _won ? "WYGRALES!" : "PRZEGRALES!";
    Color msgColor = _won ? GREEN : RED;
    int msgFontSize = 48;
    int textWidth = MeasureTextEx(*font, message, (float)msgFontSize, 2).x;

    int textureBottomY = screenHeight / 2 - (gameOverTexture ? gameOverTexture->height : 0) / 2 - 60 +
        (gameOverTexture ? gameOverTexture->height : 0);
    int messageY = textureBottomY + 40;

    DrawTextEx(
        *font,
        message,
        { screenWidth / 2.0f - textWidth / 2, (float)messageY },
        (float)msgFontSize,
        2,
        msgColor
    );

    // Wy�wietl wynik
    char scoreText[64];
    sprintf(scoreText, "Wynik: %d", _finalScore);
    int scoreWidth = MeasureTextEx(*font, scoreText, 32, 2).x;
    DrawTextEx(
        *font,
        scoreText,
        { screenWidth / 2.0f - scoreWidth / 2, (float)(messageY + 60) },
        32,
        2,
        WHITE
    );

    // Komunikat o restarcie gry
    const char* restartMsg = "Nacisnij klawisz R, aby zrestartowac gre";
    int restartWidth = MeasureTextEx(*font, restartMsg, 24, 2).x;
    DrawTextEx(
        *font,
        restartMsg,
        { screenWidth / 2.0f - restartWidth / 2, (float)(messageY + 110) },
        24,
        2,
        YELLOW
    );

    EndDrawing();
}