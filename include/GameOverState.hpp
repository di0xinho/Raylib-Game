#pragma once

#include "raylib.h"
#include "State.hpp"
#include "GameState.hpp"
#include "GameConfig.hpp"
#include "GameData.hpp"
#include <memory>

/// Klasa reprezentuj�ca stan zako�czenia gry (wygrana/przegrana)
class GameOverState : public State {
public:
    /// Konstruktor GameOverState.
    /// @parametr data - wska�nik na g��wn� struktur� gry
    /// @parametr finalScore - ko�cowy wynik gracza (ilo�� zebranych monet)
    /// @parametr won - czy gracz wygra� (true) czy przegra� (false)
    GameOverState(std::shared_ptr<GameData> data, int finalScore, bool won);

    /// Inicjalizacja stanu, �adowanie zasob�w
    void Init() override;

    /// Obs�uga wej�cia u�ytkownika (pod restart gry)
    void HandleInput() override;

    /// Aktualizacja stanu (nieu�ywana w tym stanie)
    void Update(float dt) override;

    /// Rysowanie ekranu ko�ca gry
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;   /// Dane gry, assety, mened�ery itd.
    int _finalScore;                   /// Wynik uzyskany przez gracza
    bool _won;                         /// Czy gracz wygra�

    Texture2D* gameOverTexture = nullptr; /// Tekstura ekranu ko�ca gry
    Font* font = nullptr;                 /// Czcionka do napis�w na ekranie
    Sound* gameOverSound = nullptr;       /// D�wi�k ko�ca gry (wygrana/przegrana)
};