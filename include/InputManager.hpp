#pragma once

#include <raylib.h>

/// Klasa zarz�dzaj�ca wej�ciem u�ytkownika (klawiatura, mysz)
class InputManager {
public:
    /// Konstruktor/Destruktor
    InputManager() {}
    ~InputManager() {}

    /// Sprawdza, czy dany klawisz zosta� wci�ni�ty (tylko raz do momentu puszczenia)
    bool isKeyPressed(int key); // Raylib u�ywa kod�w klawiszy (np. KEY_SPACE, KEY_ENTER)

    /// Sprawdza, czy dany klawisz jest aktualnie wci�ni�ty
    bool isKeyDown(int key);

    /// Sprawdza, czy przycisk myszy zosta� wci�ni�ty (tylko raz do momentu puszczenia)
    bool isMouseButtonPressed(int button); 

    /// Zwraca pozycj� kursora myszy wzgl�dem okna gry
    Vector2 getMousePosition();

    /// Sprawdza, czy dany prostok�t (np. przycisk) zosta� klikni�ty wybranym przyciskiem myszy
    bool isRectClicked(Rectangle rect, int button);
};