#pragma once

#include "raylib.h"
#include <cmath>

/// Klasa reprezentuj¹ca trofeum unosz¹ce siê do zebrania przez gracza, w celu ukoñczenia gry
class Trophy {
public:
    /// Konstruktor z parametrami (pozycja, wskaŸnik do tekstury)
    Trophy(Vector2 pos, Texture2D* texture);

    /// Domyœlny konstruktor 
    Trophy();

    /// Aktualizuje efekt unoszenia siê trofeum (animacja góra/dó³)
    void Update(float dt);

    /// Rysuje trofeum na ekranie
    void Draw() const;

    /// Zwraca prostok¹t kolizji (do sprawdzania zbierania przez gracza)
    Rectangle GetCollisionRect() const;

private:
    /// Pozycja bazowa (np. na pod³odze, punkt odniesienia animacji)
    Vector2 basePosition;

    /// Aktualna pozycja (z uwzglêdnieniem efektu unoszenia)
    Vector2 position;

    /// Rozmiar trofeum
    Vector2 size;

    /// WskaŸnik do tekstury trofeum
    Texture2D* texture;

    /// Licznik czasu dla animacji unoszenia
    float floatTimer = 0.0f;

    /// Amplituda unoszenia (jak wysoko siê unosi, w pikselach)
    float floatAmplitude = 14.0f;

    /// Prêdkoœæ animacji unoszenia (im wiêcej, tym szybciej)
    float floatSpeed = 2.0f;
};