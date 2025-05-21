#include "Enemy.hpp"

// Konstruktor, który ustawia pozycjê, rozmiar, wartoœci patrolowania, animacjê i dŸwiêk
Enemy::Enemy(Vector2 startPos, const std::vector<Texture2D*>& sharedTextures, Sound* ouchSoundPtr)
    : position(startPos), size({ 50, 50 }), patrolDistance(100), walked(0), direction(1), speed(40), anim(sharedTextures, 0.2f),
    alive(true), ouchSound(ouchSoundPtr) {}

// Aktualizuje stan przeciwnika: animacja, ruch, patrol, grawitacja i kolizja z pod³o¿em
void Enemy::Update(float dt, float groundY)
{
    anim.Update(dt);

    // Obs³uga efektu trafienia (przeciwnik miga na czerwono)
    if (hitTimer > 0.0f) {
        hitTimer -= dt;
        if (hitTimer < 0.0f) hitTimer = 0.0f;
    }

    // Grawitacja + kolizja z pod³o¿em (tak jak w klasie Player)
    velocity.y += gravity * dt;
    float newY = position.y + velocity.y * dt;

    isOnGround = false;

    // Detekcja kontaktu z pod³o¿em (przejœcie dolnej krawêdzi przez groundY)
    if (
        position.x + size.x > 0 && position.x < GetScreenWidth() * 10 && // wróg jest w "grze"
        groundY >= position.y + size.y && groundY <= newY + size.y       // dolna krawêdŸ przechodzi przez groundY
        ) {
        newY = groundY - size.y;
        velocity.y = 0;
        isOnGround = true;
    }

    position.y = newY;

    // Patrolowanie przestrzeni tylko bêd¹c na ziemi
    if (isOnGround) {
        float step = speed * dt * direction;
        position.x += step;
        walked += fabs(step);

        if (walked >= patrolDistance) {
            direction *= -1; // zmieñ kierunek
            walked = 0;
        }
    }
}

// Rysuje przeciwnika z odpowiednim kolorem (czerwony jeœli trafiony - efekt migania)
void Enemy::Draw()
{
    const Texture2D* frame = anim.GetCurrentFrame();
    if (frame) {
        Color tint = (hitTimer > 0.0f) ? RED : WHITE;
        DrawTextureEx(*frame, position, 0.0f, size.x / frame->width, tint);
    }
}

// Ustawia pozycjê przeciwnika
void Enemy::SetPosition(Vector2 pos) { position = pos; }

// Zwraca pozycjê przeciwnika
Vector2 Enemy::GetPosition() const { return position; }

// Zwraca prostok¹t kolizycjny przeciwnika
Rectangle Enemy::GetCollisionRect() const { return { position.x, position.y, size.x, size.y }; }

// Trafienie wroga: dŸwiêk, efekt, zmniejszenie hp i ewentualnie jego zabicie
void Enemy::Hit()
{
    if (!alive) return;

    health--;
    if (ouchSound) {
        PlaySound(*ouchSound);
    }
    hitTimer = hitDuration; // wróg bêdzie czerwony przez jak¹œ iloœæ czasu (hitDuration)
    if (health <= 0) {
        Kill();
    }
}

// Ustawia alive na false (wróg jest martwy)
void Enemy::Kill() {
    alive = false;
}

// Zwraca, czy wróg ¿yje
bool Enemy::IsAlive() const {
    return alive;
}