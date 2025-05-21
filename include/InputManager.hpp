#pragma once

#include <raylib.h>

/// Klasa zarz¹dzaj¹ca wejœciem u¿ytkownika (klawiatura, mysz)
class InputManager {
public:
    /// Konstruktor/Destruktor
    InputManager() {}
    ~InputManager() {}

    /// Sprawdza, czy dany klawisz zosta³ wciœniêty (tylko raz do momentu puszczenia)
    bool isKeyPressed(int key); // Raylib u¿ywa kodów klawiszy (np. KEY_SPACE, KEY_ENTER)

    /// Sprawdza, czy dany klawisz jest aktualnie wciœniêty
    bool isKeyDown(int key);

    /// Sprawdza, czy przycisk myszy zosta³ wciœniêty (tylko raz do momentu puszczenia)
    bool isMouseButtonPressed(int button); 

    /// Zwraca pozycjê kursora myszy wzglêdem okna gry
    Vector2 getMousePosition();

    /// Sprawdza, czy dany prostok¹t (np. przycisk) zosta³ klikniêty wybranym przyciskiem myszy
    bool isRectClicked(Rectangle rect, int button);
};