#include "Weapon.hpp"

/// Konstruktor 
Weapon::Weapon(Vector2 startPos, float moveSpeed, float lifeTime, Texture2D* texture)
    : position(startPos), speed(moveSpeed), rotation(0.0f), timer(0.0f), maxLifetime(lifeTime), alive(true), size(32.0f), texture(texture) {}

/// Aktualizuje stan pocisku: pozycj�, rotacj� i czas �ycia
void Weapon::Update(float dt, const std::vector<Enemy>& enemies)
{
    if (!alive) return;

    // Ruch w poziomie w prawo
    position.x += speed * dt;

    // Obr�t (1 stopie� na klatk�)
    rotation += 1.0f;
    if (rotation >= 360.0f) rotation -= 360.0f;

    // Timer �ycia pocisku
    timer += dt;

    if (timer > maxLifetime) {
        alive = false;
    }
}

/// Rysuje pocisk na ekranie
void Weapon::Draw() const
{
    Rectangle rect = { position.x, position.y, size, size };
    Vector2 origin = { size / 2, size / 2 };

    if (texture) {
        // Rysowanie tekstury z obrotem wzgl�dem �rodka
        DrawTexturePro(
            *texture,
            { 0, 0, (float)texture->width, (float)texture->height },
            rect,
            origin,
            rotation,
            WHITE
        );
    }
    else {
        // Rysowanie prostego kwadratu, w przypadku braku tekstury
        DrawRectanglePro(rect, origin, rotation, RED);
    }
}

/// Zwraca informacj�, czy pocisk jest aktywny (nie wygas�)
bool Weapon::IsAlive() const
{
    return alive;
}

/// Sprawdza kolizj� pocisku z wybranym wrogiem
bool Weapon::CollidesWith(const Enemy& enemy) const
{
    Rectangle weaponRect = { position.x, position.y, size, size };
    return CheckCollisionRecs(weaponRect, enemy.GetCollisionRect());
}

/// U�mierca pocisk (np. po kolizji)
void Weapon::Kill()
{
    alive = false;
}