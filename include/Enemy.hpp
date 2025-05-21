#pragma once

#include "raylib.h"
#include <cmath>
#include <vector>
#include "Animation.hpp"

/// Klasa reprezentuj¹ca przeciwnika w grze
class Enemy {
public:
    /// Konstruktor przeciwnika
    /// @parametr startPos - pocz¹tkowa pozycja przeciwnika
    /// @parametr sharedTextures - wektor wskaŸników do tekstur animacji
    /// @parametr ouchSound - wskaŸnik do dŸwiêku otrzymania obra¿eñ
    Enemy(Vector2 startPos, const std::vector<Texture2D*>& sharedTextures, Sound* ouchSound = nullptr);

    /// Aktualizuje stan przeciwnika
    void Update(float dt, float groundY);

    /// Rysuje przeciwnika
    void Draw();

    /// Ustawia pozycjê przeciwnika
    void SetPosition(Vector2 pos);

    /// Pobiera pozycjê przeciwnika
    Vector2 GetPosition() const;

    /// Pobiera prostok¹t kolizyjny przeciwnika
    Rectangle GetCollisionRect() const;

    /// Oznacza, ¿e przeciwnik zosta³ trafiony (obni¿a zdrowie wroga)
    void Hit();

    /// Zabija przeciwnika (oznacza jako zabitego)
    void Kill();

    /// Sprawdza, czy przeciwnik ¿yje
    bool IsAlive() const;

private:
    Vector2 position;        /// Pozycja przeciwnika
    Vector2 size;            /// Rozmiar przeciwnika
    Vector2 velocity{ 0, 0 };/// Prêdkoœæ przeciwnika
    float gravity = 700.0f;  /// Si³a grawitacji
    bool isOnGround = false; /// Czy przeciwnik stoi na ziemi?

    int health = 3;          /// Liczba punktów ¿ycia przeciwnika (domyœlnie 3)
    float patrolDistance;    /// Dystans, który patroluje przeciwnik na mapie
    float walked;            /// Przebyty dystans patrolowania
    int direction;           /// Kierunek ruchu (-1 lub 1, czyli lewo/prawo)
    float speed;             /// Prêdkoœæ poruszania siê

    float hitTimer = 0.0f;   /// Licznik czasu po trafieniu
    float hitDuration = 0.2f;/// Czas trwania efektu trafienia

    bool alive = true;       /// Czy przeciwnik ¿yje?

    Animation anim;          /// Animacja przeciwnika
    Sound* ouchSound;        /// WskaŸnik do dŸwiêku po trafieniu przeciwnika
};