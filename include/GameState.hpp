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

/// Klasa reprezentuj¹ca g³ówny stan gry (rozgrywkê)
class GameState : public State
{
public:
    /// Konstruktor przyjmuj¹cy wskaŸnik do struktury z danymi gry
    GameState(std::shared_ptr<GameData> data);

    /// Inicjalizuje stan gry (³adowanie zasobów, resetowanie zmiennych)
    void Init() override;

    /// Aktualizuje logikê gry (fizyka, AI, obiekty postaci z gry, itp.)
    void Update(float dt) override;

    /// Obs³uguje wejœcie gracza (klawiatura)
    void HandleInput() override;

    /// Rysuje wszystkie obiekty gry na ekranie
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;

    // Zmienne typów prostych (¿ycie gracza, flaga nieœmiertelnoœci, wynik, licznik czasu do niewidzialnoœci)
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

    // Wektory obiektów 
    std::vector<Rectangle> platforms;
    std::vector<Coin> coins;
    std::vector<Enemy> enemies;
    std::vector<Weapon> weapons;

    // Pojedyncze obiekty (gracz, kamera, trofeum, wektor prêdkoœci gracza)
    Player player;
    Trophy trophy;
    Camera2D camera;
    Vector2 playerVelocity;

    // DŸwiêki i muzyka 
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