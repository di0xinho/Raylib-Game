#pragma once

#include "raylib.h"
#include <vector>

/// Klasa obs�uguj�ca animacje sprite'�w opart� na wektorze wska�nik�w do tekstur
class Animation {
public:
    /// Domy�lny konstruktor 
    Animation();

    /// Konstruktor z przekazan� sekwencj� klatek i czasem trwania jednej klatki.
    /// @parametr frames - wektor wska�nik�w do klatek animacji
    /// @parametr frameTime - czas trwania jednej klatki animacji
    Animation(const std::vector<Texture2D*>& frames, float frameTime);

    /// Aktualizuje animacj� o zadany czas (dt)
    void Update(float dt);

    /// Resetuje animacj� do pierwszej klatki
    void Reset();

    /// Zwraca wska�nik do aktualnej klatki animacji
    const Texture2D* GetCurrentFrame() const;

    /// Ustawia nowe klatki i czas trwania jednej klatki
    void SetFrames(const std::vector<Texture2D*>& frames, float frameTime);

    /// Pauzuje animacj�
    void SetPaused(bool paused);

    /// Sprawdza, czy animacja jest zapauzowana
    bool IsPaused() const;

private:
    const std::vector<Texture2D*>* frames = nullptr; /// Wska�nik do wektora klatek animacji
    float frameTime = 0.1f;                          /// Czas trwania jednej klatki animacji
    float timeAccumulator = 0.0f;                    /// Licznik czasu od poprzedniej zmiany klatki
    int currentFrame = 0;                            /// Indeks aktualnej klatki
    bool paused = false;                             /// Czy animacja jest zapauzowana?
};