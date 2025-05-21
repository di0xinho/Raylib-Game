#pragma once

#include <raylib.h>
#include <vector>
#include <cmath>
#include "Enemy.hpp"

/// Klasa reprezentuj�ca pocisk (lataj�cy n�/miecz) wystrzeliwan� przez gracza
class Weapon
{
public:
    /// Konstruktor
    /// @parametr startPos - Pocz�tkowa pozycja broni
    /// @parametr moveSpeed - Pr�dko�� poruszania si� broni (pocisku)
    /// @parametr lifeTime - Maksymalny czas �ycia pocisku (w sekundach)
    /// @parametr texture - Wska�nik do tekstury pocisku
    Weapon(Vector2 startPos, float moveSpeed, float lifeTime, Texture2D* texture);

    /// Aktualizuje stan broni i sprawdza kolizje z wrogami
    void Update(float dt, const std::vector<Enemy>& enemies);

    /// Rysuje pocisk/bro� na ekranie
    void Draw() const;

    /// Sprawdza, czy pocisk nadal �yje (nie wygas� i nie zderzy� si�)
    bool IsAlive() const;

    /// Sprawdza kolizj� pocisku z danym wrogiem
    bool CollidesWith(const Enemy& enemy) const;

    /// Zwraca aktualn� pozycj� pocisku
    Vector2 GetPosition() const { return position; }

    /// Zwraca aktualn� rotacj� pocisku
    float GetRotation() const { return rotation; }

    /// U�mierca pocisk/bro� (po kolizji)
    void Kill();

private:
    Vector2 position;       /// Aktualna pozycja pocisku
    float speed;            /// Pr�dko�� poruszania si� pocisku
    float rotation;         /// K�t obrotu pocisku
    float timer;            /// Licznik czasu �ycia pocisku
    float maxLifetime;      /// Maksymalny czas �ycia pocisku
    bool alive;             /// Czy pocisk jest aktywny
    float size;             /// Rozmiar pocisku
    Texture2D* texture;     /// Wska�nik do tekstury pocisku
};