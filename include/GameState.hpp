#pragma once

#include <raylib.h>
#include <memory>
#include <vector>
#include "GameConfig.hpp"
#include "State.hpp"
#include "MoveLeftCommand.hpp"
#include "MoveRightCommand.hpp"
#include "JumpCommand.hpp"
#include "AttackCommand.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Coin.hpp"
#include "HUD.hpp"
#include "GameData.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "Trophy.hpp"
#include "Weapon.hpp"

/// Klasa reprezentuj�ca g��wny stan gry (rozgrywk�)
class GameState : public State
{
public:
    /// Konstruktor przyjmuj�cy wska�nik do struktury z danymi gry
    GameState(std::shared_ptr<GameData> data);

    /// Inicjalizuje stan gry (�adowanie zasob�w, resetowanie zmiennych)
    void Init() override;

    /// Aktualizuje logik� gry (fizyka, AI, obiekty postaci z gry, itp.)
    void Update(float dt) override;

    /// Obs�uguje wej�cie gracza (klawiatura)
    void HandleInput() override;

    /// Rysuje wszystkie obiekty gry na ekranie
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;

    // Zmienne typ�w prostych (�ycie gracza, flaga nie�miertelno�ci, wynik, licznik czasu do niewidzialno�ci)
    int playerLives = 0;
    bool playerInvincible = false;
    float invincibleTimer = 0.0f;
    int score = 0;

    // Tekstury 
    Texture2D* backgroundTexture = nullptr;
    Texture2D* landTexture = nullptr;
    Texture2D* trophyTexture = nullptr;
    Texture2D* weaponTexture = nullptr;

    // Klatki animacji gracza
    std::vector<Texture2D*> idleFrames;
    std::vector<Texture2D*> runFrames;
    std::vector<Texture2D*> jumpFrames;
    std::vector<Texture2D*> coinFrames;
    std::vector<Texture2D*> enemyFrames;

    // Wektory obiekt�w 
    std::vector<Rectangle> platforms;
    std::vector<Coin> coins;
    std::vector<Enemy> enemies;
    std::vector<Weapon> weapons;

    // Pojedyncze obiekty (gracz, kamera, trofeum, wektor pr�dko�ci gracza)
    Player player;
    Trophy trophy;
    Camera2D camera;
    Vector2 playerVelocity;

    // D�wi�ki i muzyka 
    Music* gameMusic = nullptr;
    Music* levelFailedMusic = nullptr;
    Sound* jumpSound = nullptr;
    Sound* gameOverSound = nullptr;
    Sound* punchSound = nullptr;
    Sound* attackSound = nullptr;
    Sound* ouchSound = nullptr;
    Sound* coinCollectSound = nullptr;

    // HUD pod pokazywanie aktualnego zdrowia i wyniku
    HUD hud;
};