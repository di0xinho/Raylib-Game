#pragma once

#include <raylib.h>
#include <map>
#include <string>
#include <stdexcept>

/// Klasa zarz�dzaj�ca d�wi�kami i muzyk� w grze
/// Pozwala �adowa�, pobiera� i zwalnia� zasoby d�wi�kowe oraz muzyczne
class SoundManager {
public:
    /// Domy�lny konstruktor SoundManagera
    SoundManager() = default;

    /// Destruktor zwalniaj�cy zasoby muzyczne i d�wi�kowe
    ~SoundManager();

    /// �aduje d�wi�k z pliku i przypisuje mu nazw�
    void loadSound(const std::string& name, const std::string& filename);

    /// Zwraca referencj� do za�adowanego d�wi�ku na podstawie nazwy
    Sound& getSound(const std::string& name);

    /// �aduje muzyk� z pliku i przypisuje jej nazw�
    void loadMusic(const std::string& name, const std::string& filename);

    /// Zwraca referencj� do za�adowanej muzyki na podstawie nazwy
    Music& getMusic(const std::string& name);

private:
    /// Kontener przechowuj�cy za�adowane d�wi�ki
    std::map<std::string, Sound> sounds;

    /// Kontener przechowuj�cy za�adowane �cie�ki muzyczne
    std::map<std::string, Music> musics;
};