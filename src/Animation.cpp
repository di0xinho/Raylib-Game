#include "Animation.hpp"

// Konstruktor domy�lny
Animation::Animation()
    : frames(nullptr), frameTime(0.1f), timeAccumulator(0), currentFrame(0), paused(false) {}

// Konstruktor z parametrami
Animation::Animation(const std::vector<Texture2D*>& frames, float frameTime)
    : frames(&frames), frameTime(frameTime), timeAccumulator(0), currentFrame(0), paused(false) {}

// Aktualizuje klatk� animacji na podstawie up�ywu czasu
void Animation::Update(float dt) {
    if (!frames || frames->empty() || paused) return;
    timeAccumulator += dt;
    if (timeAccumulator > frameTime) {
        currentFrame = (currentFrame + 1) % frames->size();
        timeAccumulator = 0;
    }
}

// Resetuje animacj� do pierwszej klatki
void Animation::Reset() {
    currentFrame = 0;
    timeAccumulator = 0;
}

// Zwraca wska�nik do aktualnej klatki animacji
const Texture2D* Animation::GetCurrentFrame() const {
    if (frames && !frames->empty())
        return (*frames)[currentFrame];
    return nullptr; // przy braku klatek zwraca nullptr
}

// Ustawia nowe klatki animacji i czas trwania jednej klatki
void Animation::SetFrames(const std::vector<Texture2D*>& newFrames, float newFrameTime) {
    frames = &newFrames;
    frameTime = newFrameTime;
    Reset();
}

// Pauzuje lub wznawia animacj�
void Animation::SetPaused(bool p) { paused = p; }

// Sprawdza, czy animacja jest zapauzowana
bool Animation::IsPaused() const { return paused; }