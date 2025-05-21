#pragma once

#include "raylib.h"
#include "Player.hpp"
#include "Animation.hpp"
#include <vector>

/// Klasa reprezentuj�ca monet� do zebrania przez gracza (do naliczania punkt�w dla gracza)
class Coin {
public:
    /// Konstruktor inicjuj�cy monet� na danej pozycji z referencj� do wsp�dzielonych klatek animacji
    Coin(Vector2 pos, const std::vector<Texture2D*>& sharedFrames);

    /// Aktualizuje stan animacji monety
    void Update(float dt);

    /// Rysuje monet� na ekranie
    void Draw();

    /// Ustawia pozycj� monety
    void SetPosition(Vector2 pos);

    /// Pobiera pozycj� monety
    Vector2 GetPosition() const;

    /// Pobiera prostok�t kolizyjny monety
    Rectangle GetCollisionRect() const;

    /// Sprawdza, czy moneta zosta�a zebrana
    bool IsCollected() const;

    /// Zaznacza, �e moneta zosta�a zebrana
    void Collect();

private:
    Vector2 position;    /// Pozycja monety na mapie
    Vector2 size;        /// Rozmiar monety (ustalany na podstawie klatki animacji)
    bool collected;      /// Czy moneta zosta�a ju� zebrana?
    Animation anim;      /// Animacja monety
};