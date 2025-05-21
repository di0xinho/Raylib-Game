#pragma once

#include "raylib.h"
#include <cmath>
#include <vector>
#include "Animation.hpp"

/// Klasa reprezentuj�ca przeciwnika w grze
class Enemy {
public:
    /// Konstruktor przeciwnika
    /// @parametr startPos - pocz�tkowa pozycja przeciwnika
    /// @parametr sharedTextures - wektor wska�nik�w do tekstur animacji
    /// @parametr ouchSound - wska�nik do d�wi�ku otrzymania obra�e�
    Enemy(Vector2 startPos, const std::vector<Texture2D*>& sharedTextures, Sound* ouchSound = nullptr);

    /// Aktualizuje stan przeciwnika
    void Update(float dt, float groundY);

    /// Rysuje przeciwnika
    void Draw();

    /// Ustawia pozycj� przeciwnika
    void SetPosition(Vector2 pos);

    /// Pobiera pozycj� przeciwnika
    Vector2 GetPosition() const;

    /// Pobiera prostok�t kolizyjny przeciwnika
    Rectangle GetCollisionRect() const;

    /// Oznacza, �e przeciwnik zosta� trafiony (obni�a zdrowie wroga)
    void Hit();

    /// Zabija przeciwnika (oznacza jako zabitego)
    void Kill();

    /// Sprawdza, czy przeciwnik �yje
    bool IsAlive() const;

private:
    Vector2 position;        /// Pozycja przeciwnika
    Vector2 size;            /// Rozmiar przeciwnika
    Vector2 velocity{ 0, 0 };/// Pr�dko�� przeciwnika
    float gravity = 700.0f;  /// Si�a grawitacji
    bool isOnGround = false; /// Czy przeciwnik stoi na ziemi?

    int health = 3;          /// Liczba punkt�w �ycia przeciwnika (domy�lnie 3)
    float patrolDistance;    /// Dystans, kt�ry patroluje przeciwnik na mapie
    float walked;            /// Przebyty dystans patrolowania
    int direction;           /// Kierunek ruchu (-1 lub 1, czyli lewo/prawo)
    float speed;             /// Pr�dko�� poruszania si�

    float hitTimer = 0.0f;   /// Licznik czasu po trafieniu
    float hitDuration = 0.2f;/// Czas trwania efektu trafienia

    bool alive = true;       /// Czy przeciwnik �yje?

    Animation anim;          /// Animacja przeciwnika
    Sound* ouchSound;        /// Wska�nik do d�wi�ku po trafieniu przeciwnika
};