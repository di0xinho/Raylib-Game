#include "Weapon.hpp"

/// Konstruktor 
Weapon::Weapon(Vector2 startPos, float moveSpeed, float lifeTime, Texture2D* texture)
    : position(startPos), speed(moveSpeed), rotation(0.0f), timer(0.0f), maxLifetime(lifeTime), alive(true), size(32.0f), texture(texture) {}

/// Aktualizuje stan pocisku: pozycjê, rotacjê i czas ¿ycia
void Weapon::Update(float dt, const std::vector<Enemy>& enemies)
{
    if (!alive) return;

    // Ruch w poziomie w prawo
    position.x += speed * dt;

    // Obrót (1 stopieñ na klatkê)
    rotation += 1.0f;
    if (rotation >= 360.0f) rotation -= 360.0f;

    // Timer ¿ycia pocisku
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
        // Rysowanie tekstury z obrotem wzglêdem œrodka
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

/// Zwraca informacjê, czy pocisk jest aktywny (nie wygas³)
bool Weapon::IsAlive() const
{
    return alive;
}

/// Sprawdza kolizjê pocisku z wybranym wrogiem
bool Weapon::CollidesWith(const Enemy& enemy) const
{
    Rectangle weaponRect = { position.x, position.y, size, size };
    return CheckCollisionRecs(weaponRect, enemy.GetCollisionRect());
}

/// Uœmierca pocisk (np. po kolizji)
void Weapon::Kill()
{
    alive = false;
}