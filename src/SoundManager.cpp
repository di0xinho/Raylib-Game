#include "SoundManager.hpp"

/// Destruktor - zwalnia wszystkie za�adowane d�wi�ki i muzyk�
SoundManager::~SoundManager() {
    // Zwalnianie d�wi�k�w
    for (auto& [k, v] : sounds) {
        UnloadSound(v);
    }
    // Zwalnianie muzyki
    for (auto& [k, v] : musics) {
        UnloadMusicStream(v);
    }
}

/// �aduje d�wi�k z pliku i przypisuje mu nazw�
/// Rzuca wyj�tek je�li nie uda si� za�adowa� d�wi�ku
void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    Sound s = LoadSound(filename.c_str());
    if (s.frameCount == 0) throw std::runtime_error("Nie udalo sie zaladowac dzwieku: " + filename);
    sounds[name] = s;
}

/// Zwraca referencj� do za�adowanego d�wi�ku na podstawie nazwy
/// Rzuca wyj�tek je�li d�wi�k nie istnieje
Sound& SoundManager::getSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it == sounds.end()) throw std::runtime_error("Dzwiek nie zostal znaleziony: " + name);
    return it->second;
}

/// �aduje muzyk� z pliku i przypisuje jej nazw�
/// Rzuca wyj�tek je�li nie uda si� za�adowa� muzyki
void SoundManager::loadMusic(const std::string& name, const std::string& filename) {
    Music m = LoadMusicStream(filename.c_str());
    if (!m.ctxData) throw std::runtime_error("Nie udalo sie zaladowac muzyki: " + filename);
    musics[name] = m;
}

/// Zwraca referencj� do za�adowanej muzyki na podstawie nazwy
/// Rzuca wyj�tek je�li muzyka nie istnieje
Music& SoundManager::getMusic(const std::string& name) {
    auto it = musics.find(name);
    if (it == musics.end()) throw std::runtime_error("Muzyka nie zostala znaleziona: " + name);
    return it->second;
}