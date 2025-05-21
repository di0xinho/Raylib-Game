#include "Coin.hpp"

// Konstruktor, w którym ustawia siê pozycjê, rozmiar, stan zebranej oraz animacjê
Coin::Coin(Vector2 pos, const std::vector<Texture2D*>& sharedFrames)
    : position(pos), size({ 50, 50 }), collected(false), anim(sharedFrames, 0.07f)
{
}

// Aktualizuje animacjê monety, jeœli nie zosta³a zebrana
void Coin::Update(float dt) {
    if (!collected)
        anim.Update(dt);
}

// Rysuje monetê na ekranie, jeœli nie zosta³a zebrana
void Coin::Draw() {
    if (collected) return;
    const Texture2D* frame = anim.GetCurrentFrame();
    if (frame)
        DrawTextureEx(*frame, position, 0.0f, size.x / frame->width, WHITE);
}

// Ustawia now¹ pozycjê monety
void Coin::SetPosition(Vector2 pos) { position = pos; }

// Zwraca pozycjê monety
Vector2 Coin::GetPosition() const { return position; }

// Zwraca prostok¹t kolizyjny monety
Rectangle Coin::GetCollisionRect() const { return { position.x, position.y, size.x, size.y }; }

// Sprawdza, czy moneta zosta³a zebrana
bool Coin::IsCollected() const { return collected; }

// Oznacza monetê jako zebran¹
void Coin::Collect() { collected = true; }