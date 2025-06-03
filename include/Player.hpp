#pragma once

#include "raylib.h"
#include "Weapon.hpp"
#include "Animation.hpp"
#include "PlayerCommand.hpp"
#include <cmath>
#include <memory>
#include <vector>
#include <unordered_map>

class Player {
public:

    // Konstruktory (domyślny i z parametrami)
    Player();
    Player(Vector2 startPos,
        const std::vector<Texture2D*>& idleFrames,
        const std::vector<Texture2D*>& runFrames,
        const std::vector<Texture2D*>& jumpFrames);

    // Aktualizuje animacje oraz stany gracza na podstawie wejścia
    void Update(float dt, bool isMoving, bool isJumping);
    // Rysuje gracza na ekranie
    void Draw();


    void handleInput(const std::unordered_map<int, bool>& keystates);
    // Aktualizuje fizykę gracza: kolizje, grawitacja, platformy
    void PhysicsUpdate(float dt, const std::vector<Rectangle>& platforms, float groundY);

    // Ustawia pozycję gracza
    void SetPosition(Vector2 pos);
    // Zwraca pozycję gracza
    Vector2 GetPosition() const;
    // Przesuwa gracza o podany wektor (metoda pod zastosowanie efektu odrzutu)
    void MoveBy(Vector2 offset);
    // Zwraca prostokąt kolizyjny gracza
    Rectangle GetCollisionRect() const;
    // Zwraca rozmiar gracza
    Vector2 GetSize() const;

    // Zwraca prędkość gracza (wektor prędkości)
    Vector2 GetVelocity() const;
    // Ustawia prędkość gracza
    void SetVelocity(Vector2 vel);
    // Sprawdza, czy gracz stoi na ziemi
    bool IsOnGround() const;
    // Próbuje rzucić bronią i dodaje ją do listy broni
    void tryThrowWeapon(Texture2D* weaponTexture, std::vector<Weapon>& weaponList);
    // Ustawia dźwięk skoku
    void SetJumpSound(Sound* sound);
    // Ustawia dźwięk rzutu nożem
    void SetKnifeThrowSound(Sound* sound);
    // Czy gracz może rzucić bronią (czy cooldown się skończył)
    bool canShoot() const;
    // Resetuje cooldown rzutu bronią
    void resetWeaponCooldown();
    // Zwraca wskaźnik do dźwięku rzucania nożem
    Sound* getKnifeThrowSound() const;

    // Rozpoczyna efekt mrugania na określony czas
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

    // Przypisuje komendę (wzorzec Command) do klawisza
    void bindCommand(int key, std::unique_ptr<PlayerCommand> command);

    // Mapa powiązań klawiszy z komendami
    std::unordered_map<int, std::unique_ptr<PlayerCommand>> commandMap;

private:
    Vector2 position; // Pozycja gracza 
    Vector2 size; // Rozmiar gracza
    bool facingRight; // Zwrócenie w prawą stronę

    Vector2 velocity{ 0, 0 }; // Prędkość
    bool onGround{ false }; // Czy gracz stoi na ziemii?

    // Efekt mrugania
    bool blinking = false;
    float blinkTimer = 0.0f;
    float blinkDuration = 0.0f;
    float blinkFrequency = 12.0f; // ile "mrugnięć" na sekundę

    float weaponCooldown = 0.0f;       // Czas do końca cooldownu dla rzutu bronią 
    float weaponCooldownDuration = 0.5f; // Długość trwania cooldownu dla rzutu bronią

    // Animacje dla pozostania gracza w spoczynku, biegania, skakania i wskaźnik pod aktualną animację
    Animation idleAnim;
    Animation runAnim;
    Animation jumpAnim;
    Animation* currentAnim;

    // Dźwięki skakania i rzucania nożem
    Sound* jumpSound = nullptr;
    Sound* knifeThrowSound = nullptr;
};