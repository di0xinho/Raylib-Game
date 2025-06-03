#include "Player.hpp"

// Konstruktor domy�lny gracza
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

// Obs�uga wej�cia: sprawdza, kt�re klawisze s� wci�ni�te i wywo�uj� powi�zane z nimi komendy
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
    // Wybierz odpowiedni� animacj� w zale�no�ci od stanu ruchu/skoku
    Animation* wantedAnim = &idleAnim;

    if (isJumping) {
        wantedAnim = &jumpAnim;
    }
    else if (isMoving) {
        wantedAnim = &runAnim;
    }

    // Zmie� animacj� je�li to konieczne
    if (wantedAnim != currentAnim) {
        currentAnim = wantedAnim;
        currentAnim->Reset();
    }

    // Obs�uga efektu mrugania
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
            // Ustawianie przezroczysto�ci podczas mrugania
            Color tint = WHITE;
            if (blinking) {
                float phase = fmodf(blinkTimer * blinkFrequency, 1.0f);
                if (phase < 0.5f)
                    tint.a = 60; // p�przezroczysty - kana� alfa na warto�� r�wn� 60
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

// Skok gracza (tylko je�li stoi na ziemi)
void Player::Jump() {
    if (onGround) {
        if (jumpSound) {
            PlaySound(*jumpSound);
        }
        velocity.y = -500; // Pr�dko�� w g�r�
        onGround = false;
    }
}

// Atak (odtworzenie d�wi�ku rzutu no�em)
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

    // Detekcja pod�o�a (ziemi)
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

        // Je�li gracz l�duje na platformie
        if (velocity.y > 0 && wasAbove && willBeBelow && xOverlap) {
            newY = plat.y - size.y;
            velocity.y = 0;
            onGround = true;
            break;
        }
    }
    position.y = newY;
}

// Zwraca pr�dko�� gracza
Vector2 Player::GetVelocity() const { return velocity; }

// Ustawia pr�dko�� gracza
void Player::SetVelocity(Vector2 vel) { velocity = vel; }

// Sprawdza, czy gracz jest na ziemii
bool Player::IsOnGround() const { return onGround; }

// Ustawia pozycj� gracza
void Player::SetPosition(Vector2 pos) { position = pos; }

// Zwraca pozycj� gracza
Vector2 Player::GetPosition() const { return position; }

// Przesuwa gracza o pewien wektor (metoda pod zastosowanie efektu odrzutu po zderzeniu z wrogiem)
void Player::MoveBy(Vector2 offset) { position.x += offset.x; position.y += offset.y; }

// Zwraca prostok�t kolizji gracza
Rectangle Player::GetCollisionRect() const { return { position.x, position.y, size.x, size.y }; }

// Zwraca rozmiar gracza
Vector2 Player::GetSize() const { return size; }

// Ustawia d�wi�k skoku gracza
void Player::SetJumpSound(Sound* sound) { jumpSound = sound; }

// Ustawia d�wi�ku rzutu no�em gracza
void Player::SetKnifeThrowSound(Sound* sound) { knifeThrowSound = sound; }

// Zwraca wska�nik do d�wi�ku rzucania no�em
Sound* Player::getKnifeThrowSound() const {
    return knifeThrowSound;
}

// Zwraca, czy gracz mo�e rzuci� broni� (cooldown)
bool Player::canShoot() const {
    return weaponCooldown <= 0.0f;
}

// Resetuje cooldown rzutu broni�
void Player::resetWeaponCooldown() {
    weaponCooldown = weaponCooldownDuration;
}

// Rozpocz�cie efektu mrugania na okre�lony czas
void Player::StartBlink(float duration) {
    blinking = true;
    blinkDuration = duration;
    blinkTimer = 0.0f;
}

// Sprawdzenie, czy gracz mruga
bool Player::IsBlinking() const {
    return blinking;
}

// Przypisuje komend� do klawisza
void Player::bindCommand(int key, std::unique_ptr<PlayerCommand> command) {
    commandMap[key] = std::move(command);
}

// Rzut broni�, tworzy nowy obiekt Weapon i dodaje go do listy
void Player::tryThrowWeapon(Texture2D* weaponTexture, std::vector<Weapon>& weaponList) {
    
    Vector2 playerPosition = GetPosition();

    Weapon weapon = Weapon({ playerPosition.x, playerPosition.y + (GetSize().y / 2.f)}, 500.0f, 5.0f, weaponTexture);

    weaponList.emplace_back(weapon);

    resetWeaponCooldown();
}