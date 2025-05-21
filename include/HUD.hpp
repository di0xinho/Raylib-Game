#pragma once

#include "raylib.h"
#include <cstdio>

/// Klasa odpowiadaj�ca za wy�wietlanie interfejsu gracza (HUD)
class HUD {
public:
    /// Konstruktor/Destruktor
    HUD();
    ~HUD();

    /// Rysuje HUD z liczb� �y� i wynikiem
    void Draw(int lives, int score);
};