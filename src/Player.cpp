#include "Player.hpp"

// Konstruktor domyœlny gracza
Player::Player()
    : position({ 0,0 }), size({ 0,0 }), facingRight(true),
    idleAnim(), runAnim(), jumpAnim(), currentAnim(nullptr),
    velocity({ 0,0 }), onGround(false), jumpSound(nullptr),
    blinking(false), blinkTimer(0), blinkDuration(0), blinkFrequency(12) {}

// Konstruktor z parametrami (pozycja startowa, animacje)
Player::Player(Vector2 startPos, const std::vector<Texture2D*>& idleFrames, const std::vector<Texture2D*>& runFrames,
    const std::vector<Texture2D*>& jumpFrames) : position(startPos),
    size({ 50, 50 }),
    facingRight(true),
    idleAnim(idleFrames, 0.2f),
    runAnim(runFrames, 0.1f),
    jumpAnim(jumpFrames, 0.1f),
    currentAnim(&idleAnim),
    velocity({ 0,0 }), onGround(false), jumpSound(nullptr),
    blinking(false), blinkTimer(0), blinkDuration(0), blinkFrequency(12) {}

// Obs³uga wejœcia: sprawdza, które klawisze s¹ wciœniête i wywo³uj¹ powi¹zane z nimi komendy
void Player::handleInput(const std::unordered_map<int, bool>& keystates) {
    velocity.x = 0;

    for (const auto& [key, command] : commandMap) {
        if (keystates.count(key) && keystates.at(key)) {
            command->Execute(*this);
        }
    }
}

// Aktualizacja animacji i efektu mrugania
void Player::Update(float dt, bool isMoving, bool isJumping)
{
    // Wybierz odpowiedni¹ animacjê w zale¿noœci od stanu ruchu/skoku
    Animation* wantedAnim = &idleAnim;

    if (isJumping) {
        wantedAnim = &jumpAnim;
    }
    else if (isMoving) {
        wantedAnim = &runAnim;
    }

    // Zmieñ animacjê jeœli to konieczne
    if (wantedAnim != currentAnim) {
        currentAnim = wantedAnim;
        currentAnim->Reset();
    }

    // Obs³uga efektu mrugania
    if (blinking) {
        blinkTimer += dt;
        if (blinkTimer >= blinkDuration) {
            blinking = false;
            blinkTimer = 0.0f;
        }
    }

    if (weaponCooldown > 0.0f) weaponCooldown -= dt;

    // Aktualizacja klatki animacji
    if (currentAnim) currentAnim->Update(dt);
}

// Renderowanie gracza na ekranie
void Player::Draw()
{
    if (currentAnim) {
        const Texture2D* frame = currentAnim->GetCurrentFrame();
        if (frame) {
            // Ustawianie przezroczystoœci podczas mrugania
            Color tint = WHITE;
            if (blinking) {
                float phase = fmodf(blinkTimer * blinkFrequency, 1.0f);
                if (phase < 0.5f)
                    tint.a = 60; // pó³przezroczysty - kana³ alfa na wartoœæ równ¹ 60
            }
            DrawTextureEx(*frame, position, 0.0f, size.x / frame->width, tint);
        }
    }
}

// Ruch w lewo
void Player::MoveLeft() {
    velocity.x = -200;
    facingRight = false;
}

// Ruch w prawo
void Player::MoveRight() {
    velocity.x = 200;
    facingRight = true;
}

// Zatrzymanie ruchu poziomego gracza
void Player::StopMoving() {
    velocity.x = 0;
}

// Skok gracza (tylko jeœli stoi na ziemi)
void Player::Jump() {
    if (onGround) {
        if (jumpSound) {
            PlaySound(*jumpSound);
        }
        velocity.y = -500; // Prêdkoœæ w górê
        onGround = false;
    }
}

// Atak (odtworzenie dŸwiêku rzutu no¿em)
void Player::Attack() {
    if (knifeThrowSound) {
        PlaySound(*knifeThrowSound);
    }
}

// Aktualizacja fizyki i kolizji gracza
void Player::PhysicsUpdate(float dt, const std::vector<Rectangle>& platforms, float groundY) {
    float gravity = 600.0f;
    position.x += velocity.x * dt;
    velocity.y += gravity * dt;
    float newY = position.y + velocity.y * dt;

    onGround = false;

    // Detekcja pod³o¿a (ziemi)
    if (position.x + size.x > 0 && position.x < GetScreenWidth() * 10 &&
        groundY >= position.y + size.y && groundY <= newY + size.y)
    {
        newY = groundY - size.y;
        velocity.y = 0;
        onGround = true;
    }

    // Detekcja kolizji z platformami
    for (const auto& plat : platforms) {
        float platLeft = plat.x;
        float platRight = plat.x + plat.width;

        float prevBottom = position.y + size.y;
        float nextBottom = newY + size.y;

        bool wasAbove = prevBottom <= plat.y;
        bool willBeBelow = nextBottom >= plat.y && prevBottom <= plat.y + plat.height;
        bool xOverlap = position.x + size.x > platLeft && position.x < platRight;

        // Jeœli gracz l¹duje na platformie
        if (velocity.y > 0 && wasAbove && willBeBelow && xOverlap) {
            newY = plat.y - size.y;
            velocity.y = 0;
            onGround = true;
            break;
        }
    }
    position.y = newY;
}

// Zwraca prêdkoœæ gracza
Vector2 Player::GetVelocity() const { return velocity; }

// Ustawia prêdkoœæ gracza
void Player::SetVelocity(Vector2 vel) { velocity = vel; }

// Sprawdza, czy gracz jest na ziemii
bool Player::IsOnGround() const { return onGround; }

// Ustawia pozycjê gracza
void Player::SetPosition(Vector2 pos) { position = pos; }

// Zwraca pozycjê gracza
Vector2 Player::GetPosition() const { return position; }

// Przesuwa gracza o pewien wektor (metoda pod zastosowanie efektu odrzutu po zderzeniu z wrogiem)
void Player::MoveBy(Vector2 offset) { position.x += offset.x; position.y += offset.y; }

// Zwraca prostok¹t kolizji gracza
Rectangle Player::GetCollisionRect() const { return { position.x, position.y, size.x, size.y }; }

// Zwraca rozmiar gracza
Vector2 Player::GetSize() const { return size; }

// Ustawia dŸwiêk skoku gracza
void Player::SetJumpSound(Sound* sound) { jumpSound = sound; }

// Ustawia dŸwiêku rzutu no¿em gracza
void Player::SetKnifeThrowSound(Sound* sound) { knifeThrowSound = sound; }

// Zwraca wskaŸnik do dŸwiêku rzucania no¿em
Sound* Player::getKnifeThrowSound() const {
    return knifeThrowSound;
}

// Zwraca, czy gracz mo¿e rzuciæ broni¹ (cooldown)
bool Player::canShoot() const {
    return weaponCooldown <= 0.0f;
}

// Resetuje cooldown rzutu broni¹
void Player::resetWeaponCooldown() {
    weaponCooldown = weaponCooldownDuration;
}

// Rozpoczêcie efektu mrugania na okreœlony czas
void Player::StartBlink(float duration) {
    blinking = true;
    blinkDuration = duration;
    blinkTimer = 0.0f;
}

// Sprawdzenie, czy gracz mruga
bool Player::IsBlinking() const {
    return blinking;
}

// Przypisuje komendê do klawisza
void Player::bindCommand(int key, std::unique_ptr<PlayerCommand> command) {
    commandMap[key] = std::move(command);
}

// Rzut broni¹, tworzy nowy obiekt Weapon i dodaje go do listy
void Player::tryThrowWeapon(Texture2D* weaponTexture, std::vector<Weapon>& weaponList) {
    
    Vector2 playerPosition = GetPosition();

    Weapon weapon = Weapon({ playerPosition.x, playerPosition.y + (GetSize().y / 2.f)}, 500.0f, 5.0f, weaponTexture);

    weaponList.emplace_back(weapon);

    resetWeaponCooldown();
}