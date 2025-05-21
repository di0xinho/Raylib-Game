#include "InputManager.hpp"

// Sprawdza, czy dany klawisz zosta³ wciœniêty (tylko raz do momentu puszczenia)
bool InputManager::isKeyPressed(int key)
{
    return IsKeyPressed(key);
}

// Sprawdza, czy dany klawisz jest aktualnie wciœniêty
bool InputManager::isKeyDown(int key)
{
    return IsKeyDown(key);
}

// Sprawdza, czy dany przycisk myszy jest aktualnie wciœniêty (przytrzymany)
bool InputManager::isMouseButtonPressed(int button)
{
    return IsMouseButtonDown(button);
}

// Zwraca pozycjê kursora myszy wzglêdem okna gry
Vector2 InputManager::getMousePosition()
{
    return GetMousePosition();
}

// Sprawdza, czy dany prostok¹t zosta³ klikniêty wybranym przyciskiem myszy
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