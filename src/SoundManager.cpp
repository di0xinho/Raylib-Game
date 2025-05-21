#include "SoundManager.hpp"

/// Destruktor - zwalnia wszystkie za³adowane dŸwiêki i muzykê
SoundManager::~SoundManager() {
    // Zwalnianie dŸwiêków
    for (auto& [k, v] : sounds) {
        UnloadSound(v);
    }
    // Zwalnianie muzyki
    for (auto& [k, v] : musics) {
        UnloadMusicStream(v);
    }
}

/// £aduje dŸwiêk z pliku i przypisuje mu nazwê
/// Rzuca wyj¹tek jeœli nie uda siê za³adowaæ dŸwiêku
void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    Sound s = LoadSound(filename.c_str());
    if (s.frameCount == 0) throw std::runtime_error("Nie udalo sie zaladowac dzwieku: " + filename);
    sounds[name] = s;
}

/// Zwraca referencjê do za³adowanego dŸwiêku na podstawie nazwy
/// Rzuca wyj¹tek jeœli dŸwiêk nie istnieje
Sound& SoundManager::getSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it == sounds.end()) throw std::runtime_error("Dzwiek nie zostal znaleziony: " + name);
    return it->second;
}

/// £aduje muzykê z pliku i przypisuje jej nazwê
/// Rzuca wyj¹tek jeœli nie uda siê za³adowaæ muzyki
void SoundManager::loadMusic(const std::string& name, const std::string& filename) {
    Music m = LoadMusicStream(filename.c_str());
    if (!m.ctxData) throw std::runtime_error("Nie udalo sie zaladowac muzyki: " + filename);
    musics[name] = m;
}

/// Zwraca referencjê do za³adowanej muzyki na podstawie nazwy
/// Rzuca wyj¹tek jeœli muzyka nie istnieje
Music& SoundManager::getMusic(const std::string& name) {
    auto it = musics.find(name);
    if (it == musics.end()) throw std::runtime_error("Muzyka nie zostala znaleziona: " + name);
    return it->second;
}