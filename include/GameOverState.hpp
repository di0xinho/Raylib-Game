#pragma once

#include "raylib.h"
#include "State.hpp"
#include "GameState.hpp"
#include "GameConfig.hpp"
#include "GameData.hpp"
#include <memory>

/// Klasa reprezentuj¹ca stan zakoñczenia gry (wygrana/przegrana)
class GameOverState : public State {
public:
    /// Konstruktor GameOverState.
    /// @parametr data - wskaŸnik na g³ówn¹ strukturê gry
    /// @parametr finalScore - koñcowy wynik gracza (iloœæ zebranych monet)
    /// @parametr won - czy gracz wygra³ (true) czy przegra³ (false)
    GameOverState(std::shared_ptr<GameData> data, int finalScore, bool won);

    /// Inicjalizacja stanu, ³adowanie zasobów
    void Init() override;

    /// Obs³uga wejœcia u¿ytkownika (pod restart gry)
    void HandleInput() override;

    /// Aktualizacja stanu (nieu¿ywana w tym stanie)
    void Update(float dt) override;

    /// Rysowanie ekranu koñca gry
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;   /// Dane gry, assety, mened¿ery itd.
    int _finalScore;                   /// Wynik uzyskany przez gracza
    bool _won;                         /// Czy gracz wygra³

    Texture2D* gameOverTexture = nullptr; /// Tekstura ekranu koñca gry
    Font* font = nullptr;                 /// Czcionka do napisów na ekranie
    Sound* gameOverSound = nullptr;       /// DŸwiêk koñca gry (wygrana/przegrana)
};