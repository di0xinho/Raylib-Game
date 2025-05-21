#pragma once

#include <raylib.h>
#include <vector>
#include <cmath>
#include "Enemy.hpp"

/// Klasa reprezentuj¹ca pocisk (lataj¹cy nó¿/miecz) wystrzeliwan¹ przez gracza
class Weapon
{
public:
    /// Konstruktor
    /// @parametr startPos - Pocz¹tkowa pozycja broni
    /// @parametr moveSpeed - Prêdkoœæ poruszania siê broni (pocisku)
    /// @parametr lifeTime - Maksymalny czas ¿ycia pocisku (w sekundach)
    /// @parametr texture - WskaŸnik do tekstury pocisku
    Weapon(Vector2 startPos, float moveSpeed, float lifeTime, Texture2D* texture);

    /// Aktualizuje stan broni i sprawdza kolizje z wrogami
    void Update(float dt, const std::vector<Enemy>& enemies);

    /// Rysuje pocisk/broñ na ekranie
    void Draw() const;

    /// Sprawdza, czy pocisk nadal ¿yje (nie wygas³ i nie zderzy³ siê)
    bool IsAlive() const;

    /// Sprawdza kolizjê pocisku z danym wrogiem
    bool CollidesWith(const Enemy& enemy) const;

    /// Zwraca aktualn¹ pozycjê pocisku
    Vector2 GetPosition() const { return position; }

    /// Zwraca aktualn¹ rotacjê pocisku
    float GetRotation() const { return rotation; }

    /// Uœmierca pocisk/broñ (po kolizji)
    void Kill();

private:
    Vector2 position;       /// Aktualna pozycja pocisku
    float speed;            /// Prêdkoœæ poruszania siê pocisku
    float rotation;         /// K¹t obrotu pocisku
    float timer;            /// Licznik czasu ¿ycia pocisku
    float maxLifetime;      /// Maksymalny czas ¿ycia pocisku
    bool alive;             /// Czy pocisk jest aktywny
    float size;             /// Rozmiar pocisku
    Texture2D* texture;     /// WskaŸnik do tekstury pocisku
};