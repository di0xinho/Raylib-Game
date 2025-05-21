#include "HUD.hpp"

// Konstruktor 
HUD::HUD() {}

// Destruktor
HUD::~HUD() {}

// Rysuje pasek HUD - zdrowie i wynik
void HUD::Draw(int lives, int score) {
    const int hudPadding = 24;
    const int fontSize = 34;
    const int spacing = 10;

    char livesText[32], scoreText[32];
    std::sprintf(livesText, "ZDROWIE: %d", lives);
    std::sprintf(scoreText, "WYNIK: %d", score);

    int screenWidth = GetScreenWidth();
    int livesWidth = MeasureText(livesText, fontSize);
    int scoreWidth = MeasureText(scoreText, fontSize);

    DrawText(livesText, screenWidth - livesWidth - hudPadding, hudPadding, fontSize, RED);
    DrawText(scoreText, screenWidth - scoreWidth - hudPadding, hudPadding + fontSize + spacing, fontSize, DARKGREEN);
}