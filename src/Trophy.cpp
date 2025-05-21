#include "Trophy.hpp"

/// Domyœlny konstruktor 
Trophy::Trophy()
    : basePosition{ 0,0 }, position{ 0,0 }, size{ 0,0 }, texture(nullptr), floatTimer(0.0f) {
}

/// Konstruktor z parametrami - ustawia pozycjê bazow¹, aktualn¹ i teksturê
Trophy::Trophy(Vector2 pos, Texture2D* texture) : basePosition(pos), position(pos), texture(texture)
{
    // Ustal rozmiar na podstawie rozmiaru tekstury
    size = { (float)texture->width, (float)texture->height };
}

/// Aktualizuje efekt unoszenia trofeum (oscylacja góra/dó³)
void Trophy::Update(float dt)
{
    floatTimer += dt * floatSpeed; // Zwiêksz licznik czasu
    // Efekt unoszenia: pozycja.y oscyluje sinusoidalnie wzglêdem pozycji bazowej
    position.y = basePosition.y + std::sin(floatTimer) * floatAmplitude;
}

/// Rysuje trofeum na ekranie w aktualnej pozycji
void Trophy::Draw() const
{
    DrawTexture(*texture, (int)position.x, (int)position.y, WHITE);
}

/// Zwraca prostok¹t kolizji trofeum
Rectangle Trophy::GetCollisionRect() const
{
    return { position.x, position.y, size.x, size.y };
}