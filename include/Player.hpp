#pragma once

#include "raylib.h"
#include "Animation.hpp"
#include <cmath>
#include <vector>

class Player {
public:

    // Konstruktory (domy�lny i z parametrami)
    Player();
    Player(Vector2 startPos,
        const std::vector<Texture2D*>& idleFrames,
        const std::vector<Texture2D*>& runFrames,
        const std::vector<Texture2D*>& jumpFrames);

    // Aktualizuje animacje oraz stany gracza na podstawie wej�cia
    void Update(float dt, bool isMoving, bool isJumping);
    // Rysuje gracza na ekranie
    void Draw();

    // Aktualizuje fizyk� gracza: kolizje, grawitacja, platformy
    void PhysicsUpdate(float dt, const std::vector<Rectangle>& platforms, float groundY);

    // Ustawia pozycj� gracza
    void SetPosition(Vector2 pos);
    // Zwraca pozycj� gracza
    Vector2 GetPosition() const;
    // Przesuwa gracza o podany wektor (metoda pod zastosowanie efektu odrzutu)
    void MoveBy(Vector2 offset);
    // Zwraca prostok�t kolizyjny gracza
    Rectangle GetCollisionRect() const;
    // Zwraca rozmiar gracza
    Vector2 GetSize() const;

    // Zwraca pr�dko�� gracza (wektor pr�dko�ci)
    Vector2 GetVelocity() const;
    // Ustawia pr�dko�� gracza
    void SetVelocity(Vector2 vel);
    // Sprawdza, czy gracz stoi na ziemi
    bool IsOnGround() const;

    // Ustawia d�wi�k skoku
    void SetJumpSound(Sound* sound);
    // Ustawia d�wi�k rzutu no�em
    void SetKnifeThrowSound(Sound* sound);

    // Rozpoczyna efekt mrugania na okre�lony czas
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
    bool facingRight; // Zwr�cenie w praw� stron�

    Vector2 velocity{ 0, 0 }; // Pr�dko��
    bool onGround{ false }; // Czy gracz stoi na ziemii?

    // Efekt mrugania
    bool blinking = false;
    float blinkTimer = 0.0f;
    float blinkDuration = 0.0f;
    float blinkFrequency = 12.0f; // ile "mrugni��" na sekund�

    // Animacje dla pozostania gracza w spoczynku, biegania, skakania i wska�nik pod aktualn� animacj�
    Animation idleAnim;
    Animation runAnim;
    Animation jumpAnim;
    Animation* currentAnim;

    // D�wi�ki skakania i rzucania no�em
    Sound* jumpSound = nullptr;
    Sound* knifeThrowSound = nullptr;
};