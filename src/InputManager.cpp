#include "InputManager.hpp"

// Sprawdza, czy dany klawisz zosta� wci�ni�ty (tylko raz do momentu puszczenia)
bool InputManager::isKeyPressed(int key)
{
    return IsKeyPressed(key);
}

// Sprawdza, czy dany klawisz jest aktualnie wci�ni�ty
bool InputManager::isKeyDown(int key)
{
    return IsKeyDown(key);
}

// Sprawdza, czy dany przycisk myszy jest aktualnie wci�ni�ty (przytrzymany)
bool InputManager::isMouseButtonPressed(int button)
{
    return IsMouseButtonDown(button);
}

// Zwraca pozycj� kursora myszy wzgl�dem okna gry
Vector2 InputManager::getMousePosition()
{
    return GetMousePosition();
}

// Sprawdza, czy dany prostok�t zosta� klikni�ty wybranym przyciskiem myszy
bool InputManager::isRectClicked(Rectangle rect, int button)
{
    if (IsMouseButtonPressed(button))
    {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, rect))
        {
            return true;
        }
    }
    return false;
}