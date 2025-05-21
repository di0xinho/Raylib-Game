#include "Trophy.hpp"

/// Domy�lny konstruktor 
Trophy::Trophy()
    : basePosition{ 0,0 }, position{ 0,0 }, size{ 0,0 }, texture(nullptr), floatTimer(0.0f) {
}

/// Konstruktor z parametrami - ustawia pozycj� bazow�, aktualn� i tekstur�
Trophy::Trophy(Vector2 pos, Texture2D* texture) : basePosition(pos), position(pos), texture(texture)
{
    // Ustal rozmiar na podstawie rozmiaru tekstury
    size = { (float)texture->width, (float)texture->height };
}

/// Aktualizuje efekt unoszenia trofeum (oscylacja g�ra/d�)
void Trophy::Update(float dt)
{
    floatTimer += dt * floatSpeed; // Zwi�ksz licznik czasu
    // Efekt unoszenia: pozycja.y oscyluje sinusoidalnie wzgl�dem pozycji bazowej
    position.y = basePosition.y + std::sin(floatTimer) * floatAmplitude;
}

/// Rysuje trofeum na ekranie w aktualnej pozycji
void Trophy::Draw() const
{
    DrawTexture(*texture, (int)position.x, (int)position.y, WHITE);
}

/// Zwraca prostok�t kolizji trofeum
Rectangle Trophy::GetCollisionRect() const
{
    return { position.x, position.y, size.x, size.y };
}