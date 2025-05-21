#pragma once

#include "raylib.h"
#include "Player.hpp"
#include "Animation.hpp"
#include <vector>

/// Klasa reprezentuj¹ca monetê do zebrania przez gracza (do naliczania punktów dla gracza)
class Coin {
public:
    /// Konstruktor inicjuj¹cy monetê na danej pozycji z referencj¹ do wspó³dzielonych klatek animacji
    Coin(Vector2 pos, const std::vector<Texture2D*>& sharedFrames);

    /// Aktualizuje stan animacji monety
    void Update(float dt);

    /// Rysuje monetê na ekranie
    void Draw();

    /// Ustawia pozycjê monety
    void SetPosition(Vector2 pos);

    /// Pobiera pozycjê monety
    Vector2 GetPosition() const;

    /// Pobiera prostok¹t kolizyjny monety
    Rectangle GetCollisionRect() const;

    /// Sprawdza, czy moneta zosta³a zebrana
    bool IsCollected() const;

    /// Zaznacza, ¿e moneta zosta³a zebrana
    void Collect();

private:
    Vector2 position;    /// Pozycja monety na mapie
    Vector2 size;        /// Rozmiar monety (ustalany na podstawie klatki animacji)
    bool collected;      /// Czy moneta zosta³a ju¿ zebrana?
    Animation anim;      /// Animacja monety
};