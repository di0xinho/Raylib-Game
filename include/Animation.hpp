#pragma once

#include "raylib.h"
#include <vector>

/// Klasa obs³uguj¹ca animacje sprite'ów opart¹ na wektorze wskaŸników do tekstur
class Animation {
public:
    /// Domyœlny konstruktor 
    Animation();

    /// Konstruktor z przekazan¹ sekwencj¹ klatek i czasem trwania jednej klatki.
    /// @parametr frames - wektor wskaŸników do klatek animacji
    /// @parametr frameTime - czas trwania jednej klatki animacji
    Animation(const std::vector<Texture2D*>& frames, float frameTime);

    /// Aktualizuje animacjê o zadany czas (dt)
    void Update(float dt);

    /// Resetuje animacjê do pierwszej klatki
    void Reset();

    /// Zwraca wskaŸnik do aktualnej klatki animacji
    const Texture2D* GetCurrentFrame() const;

    /// Ustawia nowe klatki i czas trwania jednej klatki
    void SetFrames(const std::vector<Texture2D*>& frames, float frameTime);

    /// Pauzuje animacjê
    void SetPaused(bool paused);

    /// Sprawdza, czy animacja jest zapauzowana
    bool IsPaused() const;

private:
    const std::vector<Texture2D*>* frames = nullptr; /// WskaŸnik do wektora klatek animacji
    float frameTime = 0.1f;                          /// Czas trwania jednej klatki animacji
    float timeAccumulator = 0.0f;                    /// Licznik czasu od poprzedniej zmiany klatki
    int currentFrame = 0;                            /// Indeks aktualnej klatki
    bool paused = false;                             /// Czy animacja jest zapauzowana?
};