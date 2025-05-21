#pragma once

#include "raylib.h"
#include "Animation.hpp"
#include <cmath>
#include <vector>

class Player {
public:

    // Konstruktory (domyœlny i z parametrami)
    Player();
    Player(Vector2 startPos,
        const std::vector<Texture2D*>& idleFrames,
        const std::vector<Texture2D*>& runFrames,
        const std::vector<Texture2D*>& jumpFrames);

    // Aktualizuje animacje oraz stany gracza na podstawie wejœcia
    void Update(float dt, bool isMoving, bool isJumping);
    // Rysuje gracza na ekranie
    void Draw();

    // Aktualizuje fizykê gracza: kolizje, grawitacja, platformy
    void PhysicsUpdate(float dt, const std::vector<Rectangle>& platforms, float groundY);

    // Ustawia pozycjê gracza
    void SetPosition(Vector2 pos);
    // Zwraca pozycjê gracza
    Vector2 GetPosition() const;
    // Przesuwa gracza o podany wektor (metoda pod zastosowanie efektu odrzutu)
    void MoveBy(Vector2 offset);
    // Zwraca prostok¹t kolizyjny gracza
    Rectangle GetCollisionRect() const;
    // Zwraca rozmiar gracza
    Vector2 GetSize() const;

    // Zwraca prêdkoœæ gracza (wektor prêdkoœci)
    Vector2 GetVelocity() const;
    // Ustawia prêdkoœæ gracza
    void SetVelocity(Vector2 vel);
    // Sprawdza, czy gracz stoi na ziemi
    bool IsOnGround() const;

    // Ustawia dŸwiêk skoku
    void SetJumpSound(Sound* sound);
    // Ustawia dŸwiêk rzutu no¿em
    void SetKnifeThrowSound(Sound* sound);

    // Rozpoczyna efekt mrugania na okreœlony czas
    void StartBlink(float duration);
    // Sprawdza, czy gracz aktualnie mruga
    bool IsBlinking() const;

    // Ruch w lewo
    void MoveLeft();
    // Ruch w prawo
    void MoveRight();
    // Skok
    void Jump();
    // Zatrzymuje ruch gracza
    void StopMoving();
    // Atak gracza
    void Attack();

private:
    Vector2 position; // Pozycja gracza 
    Vector2 size; // Rozmiar gracza
    bool facingRight; // Zwrócenie w praw¹ stronê

    Vector2 velocity{ 0, 0 }; // Prêdkoœæ
    bool onGround{ false }; // Czy gracz stoi na ziemii?

    // Efekt mrugania
    bool blinking = false;
    float blinkTimer = 0.0f;
    float blinkDuration = 0.0f;
    float blinkFrequency = 12.0f; // ile "mrugniêæ" na sekundê

    // Animacje dla pozostania gracza w spoczynku, biegania, skakania i wskaŸnik pod aktualn¹ animacjê
    Animation idleAnim;
    Animation runAnim;
    Animation jumpAnim;
    Animation* currentAnim;

    // DŸwiêki skakania i rzucania no¿em
    Sound* jumpSound = nullptr;
    Sound* knifeThrowSound = nullptr;
};