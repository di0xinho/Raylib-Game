#include "GameState.hpp"

// Konstruktor inicjuj¹cy wskaŸnik do GameData
GameState::GameState(std::shared_ptr<GameData> data) : _data(data) {}

void GameState::Init()
{
    // £adowanie tekstur przez AssetManager 
    _data->assetManager->loadTexture("background", BACKGROUND_TEXTURE);
    _data->assetManager->loadTexture("land", LAND_TEXTURE);
    _data->assetManager->loadTexture("trophy", TROPHY);
    _data->assetManager->loadTexture("weapon", SWORD_TEXTURE);

    // £adowanie animacji gracza
    _data->assetManager->loadTexture("player_idle", PLAYER_IDLE);
    _data->assetManager->loadTexture("player_run1", PLAYER_RUN_1);
    _data->assetManager->loadTexture("player_run2", PLAYER_RUN_2);
    _data->assetManager->loadTexture("player_run3", PLAYER_RUN_3);
    _data->assetManager->loadTexture("player_jump", PLAYER_JUMP);

    // Animacje monet
    const char* coinPaths[] = { COIN_1, COIN_2, COIN_3, COIN_4, COIN_5, COIN_6, COIN_7, COIN_8, COIN_9, COIN_10, COIN_11, COIN_12, COIN_13, COIN_14 };
    for (int i = 0; i < 14; ++i) {
        std::string key = "coin_" + std::to_string(i + 1);
        _data->assetManager->loadTexture(key, coinPaths[i]);
    }

    // Animacje wrogów
    const char* enemyPaths[] = { ENEMY_1, ENEMY_2 };
    for (int i = 0; i < 2; ++i) {
        std::string key = "enemy_" + std::to_string(i + 1);
        _data->assetManager->loadTexture(key, enemyPaths[i]);
    }

    // £adowanie dŸwiêków i muzyki przez SoundManager 
    _data->soundManager->loadMusic("game_music", GAME_MUSIC);
    _data->soundManager->loadSound("jump", JUMP_SOUND);
    _data->soundManager->loadSound("attack", KNIFE_THROW_SOUND);
    _data->soundManager->loadSound("ouch", OUCH_SOUND);
    _data->soundManager->loadSound("punch", PUNCH_SOUND);
    _data->soundManager->loadSound("coin", COIN_SOUND);

    // Pobieranie wskaŸników do tekstur 
    backgroundTexture = &_data->assetManager->getTexture("background");
    landTexture = &_data->assetManager->getTexture("land");
    trophyTexture = &_data->assetManager->getTexture("trophy");
    weaponTexture = &_data->assetManager->getTexture("weapon");

    // Pobieranie klatek animacji (dla gracza) 
    idleFrames.clear();
    idleFrames.push_back(&_data->assetManager->getTexture("player_idle"));

    runFrames.clear();
    runFrames.push_back(&_data->assetManager->getTexture("player_run1"));
    runFrames.push_back(&_data->assetManager->getTexture("player_run2"));
    runFrames.push_back(&_data->assetManager->getTexture("player_run3"));

    jumpFrames.clear();
    jumpFrames.push_back(&_data->assetManager->getTexture("player_jump"));

    // Pobieranie klatek animacji (dla monet i wrogów) ---
    coinFrames.clear();
    for (int i = 0; i < 14; ++i)
        coinFrames.push_back(&_data->assetManager->getTexture("coin_" + std::to_string(i + 1)));

    enemyFrames.clear();
    enemyFrames.push_back(&_data->assetManager->getTexture("enemy_1"));
    enemyFrames.push_back(&_data->assetManager->getTexture("enemy_2"));

    // Pobieranie wskaŸników do dŸwiêków/muzyki 
    gameMusic = &_data->soundManager->getMusic("game_music");
    jumpSound = &_data->soundManager->getSound("jump");
    attackSound = &_data->soundManager->getSound("attack");
    ouchSound = &_data->soundManager->getSound("ouch");
    punchSound = &_data->soundManager->getSound("punch");
    coinCollectSound = &_data->soundManager->getSound("coin");

    // Ustawienie muzyki podczas gry (zapêtlenie, ustawienie poziomu g³oœnoœci i odtworzenie muzyki)
    gameMusic->looping = true;
    SetMusicVolume(*gameMusic, 0.8f);
    PlayMusicStream(*gameMusic);
    
    // Stworzenie gracza i ustawienie dla niego odpowiednich w³aœciwoœci 
    player = Player({ 400, 300 }, idleFrames, runFrames, jumpFrames);
    player.SetJumpSound(jumpSound);
    player.SetKnifeThrowSound(attackSound);

    // Tworzenie monet 
    coins.clear();
    coins.push_back(Coin({ 445, 290 }, coinFrames));
    coins.push_back(Coin({ 735, 240 }, coinFrames));
    coins.push_back(Coin({ 1035, 190 }, coinFrames));
    coins.push_back(Coin({ 1435, 240 }, coinFrames));
    coins.push_back(Coin({ 1735, 190 }, coinFrames));
    coins.push_back(Coin({ 2035, 240 }, coinFrames));
    coins.push_back(Coin({ 2445, 290 }, coinFrames));
    coins.push_back(Coin({ 2745, 340 }, coinFrames));

    // Ustawienie liczby ¿yæ, flagi nieœmiertelnoœci, aktualnego wyniki i licznika czasu pod bycie nieœmiertelnym
    playerLives = 3;
    playerInvincible = false;
    invincibleTimer = 0.0f;
    score = 0;

    // Ustawienie platform 
    platforms = {
        { 400, 300, 140, 60 }, { 700, 250, 120, 60 }, { 1000, 200, 120, 60 },
        { 1400, 250, 120, 60 }, { 1700, 200, 120, 60 }, { 2000, 250, 120, 60 },
        { 2400, 300, 140, 60 }, { 2700, 350, 140, 60 }
    };

    // Ustawienie pozycji gracza na ziemi 
    int groundY = backgroundTexture->height - landTexture->height;
    player.SetPosition({ 400, (float)(groundY - player.GetSize().y) });

    // Stworzenie przeciwników 
    enemies.clear();
    enemies.push_back(Enemy({ 735, (float)(groundY - 50) }, enemyFrames, ouchSound));
    enemies.push_back(Enemy({ 1200, (float)(groundY - 50) }, enemyFrames, ouchSound));
    enemies.push_back(Enemy({ 1600, (float)(groundY - 50) }, enemyFrames, ouchSound));
    enemies.push_back(Enemy({ 2000, (float)(groundY - 50) }, enemyFrames, ouchSound));
    enemies.push_back(Enemy({ 2400, (float)(groundY - 50) }, enemyFrames, ouchSound));

    // Utworzenie trofeum pod zakoñczenie gry
    trophy = Trophy({ 3100, groundY - (float)trophyTexture->height }, trophyTexture);

    // Ustawienie kamery
    camera.offset = { GetScreenWidth() / 3.0f, GetScreenHeight() / 2.0f };
    camera.target = player.GetPosition();
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

// Przechwytywanie wejœcia (pod pauzê rozgrywki)
void GameState::HandleInput() {
    if (IsKeyPressed(KEY_P)) {
        _data->machine.AddState(std::make_unique<PauseState>(_data), false);
        return;
    }
}

void GameState::Update(float dt)
{
    // Obs³uga wejœcia 
    if (_data->inputManager->isKeyDown(KEY_LEFT)) {
        moveLeftCmd.Execute(player); // Chodzenie w lewo
    }
    else if (_data->inputManager->isKeyDown(KEY_RIGHT)) {
        moveRightCmd.Execute(player); // Chodzenie w prawo
    }
    else {
        stopMovingCmd.Execute(player); // Zatrzymanie siê postaci
    }

    if (_data->inputManager->isKeyPressed(KEY_SPACE)) {
        jumpCmd.Execute(player); // Skakanie
    }

    if (_data->inputManager->isKeyPressed(KEY_ENTER)) {
        attackCmd.Execute(player); // Atakowanie
        weapons.emplace_back(player.GetPosition(), 500.0f, 5.0f, weaponTexture);
    }

    // Aktualizacja strumienia muzyki
    UpdateMusicStream(*gameMusic);

    float groundY = GetScreenHeight() - landTexture->height;
    player.PhysicsUpdate(dt, platforms, groundY);

    // Aktualizacja zdarzeñ dla monet 
    for (auto& coin : coins) {
        coin.Update(dt);

        // W przypadku kolizji postaci z monet¹ - zbieramy monetê, czyli zdobywamy punkt
        if (!coin.IsCollected() && CheckCollisionRecs(player.GetCollisionRect(), coin.GetCollisionRect())) {
            coin.Collect();
            PlaySound(*coinCollectSound);
            score++;
        }
    }

    // Kolizje z wrogami; nieœmiertelnoœæ po trafieniu przez wroga (tracimy przy okazji jedno ¿ycie)
    if (!playerInvincible) {
        for (auto& enemy : enemies) {
            if (CheckCollisionRecs(player.GetCollisionRect(), enemy.GetCollisionRect())) {
                --playerLives;
                PlaySound(*punchSound);
                playerInvincible = true;
                invincibleTimer = 1.0f;
                player.StartBlink(invincibleTimer); // Migoczenie postaci przez okreœlony czas

                float knockbackStrength = 60.0f; // Si³a odrzutu
                Vector2 knockback = { 0, 0 };

                // Ustalenie kierunku odrzutu
                if (player.GetCollisionRect().x < enemy.GetCollisionRect().x)
                    knockback.x = -knockbackStrength;
                else
                    knockback.x = knockbackStrength;
                knockback.y = -30.0f;

                // Odrzut gracza w danym kierunku
                player.MoveBy(knockback);
                break;
            }
        }
    }
    else { // W przypadku ustawienia flagi nieœmiertelnoœci na true - wtedy odliczamy po prostu czas do zakoñczenia nieœmiertelnoœci
        invincibleTimer -= dt;
        if (invincibleTimer <= 0.0f) {
            playerInvincible = false;
            invincibleTimer = 0.0f;
        }
    }

    // Warunek wygranej - kolizja z trofeum 
    if (CheckCollisionRecs(player.GetCollisionRect(), trophy.GetCollisionRect())) {
        _data->machine.AddState(std::make_unique<GameOverState>(_data, score, true), true);
        return;
    }

    // Aktualizacja animacji gracza 
    bool isMoving = player.GetVelocity().x != 0;
    bool isJumping = !player.IsOnGround();

    player.Update(dt, isMoving, isJumping);

    // Aktualizacja kamery œledz¹cej gracza 
    Vector2 camTarget = player.GetPosition();
    camera.target.x += (camTarget.x - camera.target.x) * 0.1f;
    float minCamTargetX = camera.offset.x;
    if (camera.target.x < minCamTargetX)
        camera.target.x = minCamTargetX;

    // Aktualizacja wrogów, broni, kolizje broni z wrogami 
    for (auto& enemy : enemies)
        enemy.Update(dt, groundY);

    for (auto& weapon : weapons)
        weapon.Update(dt, enemies);

    for (auto& weapon : weapons) {
        for (auto& enemy : enemies) {

            // W przypadku kolizji broni z wrogiem - wróg traci zdrowie (w przypadku utraty ca³ego zdrowia - wróg umiera)
            if (weapon.IsAlive() && enemy.IsAlive() && weapon.CollidesWith(enemy)) {
                enemy.Hit();
                weapon.Kill(); // Po trafieniu broñ znika
            }
        }
    }

    // Usuwanie martwych broni
    weapons.erase(
        std::remove_if(weapons.begin(), weapons.end(),
            [](const Weapon& w) { return !w.IsAlive(); }),
        weapons.end());

    // Usuwanie martwych wrogów
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& e) { return !e.IsAlive(); }),
        enemies.end());

    // Aktualizacja stanu dla trofeum 
    trophy.Update(dt);

    // Logika dla przegranej - brak ¿yæ 
    if (playerLives <= 0) {
        _data->machine.AddState(std::make_unique<GameOverState>(_data, score, false), true);
    }
}

void GameState::Draw(float dt)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Ustawienie kamery w trybie 2D
    BeginMode2D(camera);

    // Rysowanie t³a (paralaksa) 
    float parallax = 0.2f;
    float bgX = player.GetPosition().x * (1.0f - parallax);

    int bgWidth = backgroundTexture->width;
    int bgScreenTiles = 3;
    int firstBgX = ((int)bgX / bgWidth - 1) * bgWidth;

    for (int i = 0; i < bgScreenTiles; ++i) {
        DrawTexture(*backgroundTexture, firstBgX + i * bgWidth, 0, WHITE);
    }

    // Rysowanie powierzchni 
    int groundY = GetRenderHeight() - landTexture->height + player.GetSize().y;
    int landTileWidth = landTexture->width;
    int landScreenTiles = 7;

    for (int i = 0; i < landScreenTiles; ++i) {
        DrawTexture(*landTexture, i * landTileWidth, groundY, WHITE);
    }

    // Rysowanie platform 
    for (auto& plat : platforms)
        DrawRectangleRec(plat, DARKGRAY);

    // Rysowanie obiektów gry (gracz, przeciwnicy, monety, wrogowie, trofeum)
    player.Draw();
    for (auto& enemy : enemies)
        enemy.Draw();
    for (auto& coin : coins)
        coin.Draw();
    for (auto& weapon : weapons)
        weapon.Draw();
    trophy.Draw();

    // Koñczenie trybu kamery 2D
    EndMode2D();

    // Rysowanie HUD (celowo po zakoñczeniu trybu kamery 2D, aby umo¿liwiæ przyczepienie HUD do ekranu)
    hud.Draw(playerLives, score);

    EndDrawing();
}