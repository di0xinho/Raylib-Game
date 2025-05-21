#include "Coin.hpp"

// Konstruktor, w kt�rym ustawia si� pozycj�, rozmiar, stan zebranej oraz animacj�
Coin::Coin(Vector2 pos, const std::vector<Texture2D*>& sharedFrames)
    : position(pos), size({ 50, 50 }), collected(false), anim(sharedFrames, 0.07f)
{
}

// Aktualizuje animacj� monety, je�li nie zosta�a zebrana
void Coin::Update(float dt) {
    if (!collected)
        anim.Update(dt);
}

// Rysuje monet� na ekranie, je�li nie zosta�a zebrana
void Coin::Draw() {
    if (collected) return;
    const Texture2D* frame = anim.GetCurrentFrame();
    if (frame)
        DrawTextureEx(*frame, position, 0.0f, size.x / frame->width, WHITE);
}

// Ustawia now� pozycj� monety
void Coin::SetPosition(Vector2 pos) { position = pos; }

// Zwraca pozycj� monety
Vector2 Coin::GetPosition() const { return position; }

// Zwraca prostok�t kolizyjny monety
Rectangle Coin::GetCollisionRect() const { return { position.x, position.y, size.x, size.y }; }

// Sprawdza, czy moneta zosta�a zebrana
bool Coin::IsCollected() const { return collected; }

// Oznacza monet� jako zebran�
void Coin::Collect() { collected = true; }