#pragma once

#include "raylib.h"
#include <cmath>

/// Klasa reprezentuj�ca trofeum unosz�ce si� do zebrania przez gracza, w celu uko�czenia gry
class Trophy {
public:
    /// Konstruktor z parametrami (pozycja, wska�nik do tekstury)
    Trophy(Vector2 pos, Texture2D* texture);

    /// Domy�lny konstruktor 
    Trophy();

    /// Aktualizuje efekt unoszenia si� trofeum (animacja g�ra/d�)
    void Update(float dt);

    /// Rysuje trofeum na ekranie
    void Draw() const;

    /// Zwraca prostok�t kolizji (do sprawdzania zbierania przez gracza)
    Rectangle GetCollisionRect() const;

private:
    /// Pozycja bazowa (np. na pod�odze, punkt odniesienia animacji)
    Vector2 basePosition;

    /// Aktualna pozycja (z uwzgl�dnieniem efektu unoszenia)
    Vector2 position;

    /// Rozmiar trofeum
    Vector2 size;

    /// Wska�nik do tekstury trofeum
    Texture2D* texture;

    /// Licznik czasu dla animacji unoszenia
    float floatTimer = 0.0f;

    /// Amplituda unoszenia (jak wysoko si� unosi, w pikselach)
    float floatAmplitude = 14.0f;

    /// Pr�dko�� animacji unoszenia (im wi�cej, tym szybciej)
    float floatSpeed = 2.0f;
};