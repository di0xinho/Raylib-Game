#pragma once

#include "raylib.h"
#include <cstdio>

/// Klasa odpowiadaj¹ca za wyœwietlanie interfejsu gracza (HUD)
class HUD {
public:
    /// Konstruktor/Destruktor
    HUD();
    ~HUD();

    /// Rysuje HUD z liczb¹ ¿yæ i wynikiem
    void Draw(int lives, int score);
};