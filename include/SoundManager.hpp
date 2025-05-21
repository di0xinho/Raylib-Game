#pragma once

#include <raylib.h>
#include <map>
#include <string>
#include <stdexcept>

/// Klasa zarz¹dzaj¹ca dŸwiêkami i muzyk¹ w grze
/// Pozwala ³adowaæ, pobieraæ i zwalniaæ zasoby dŸwiêkowe oraz muzyczne
class SoundManager {
public:
    /// Domyœlny konstruktor SoundManagera
    SoundManager() = default;

    /// Destruktor zwalniaj¹cy zasoby muzyczne i dŸwiêkowe
    ~SoundManager();

    /// £aduje dŸwiêk z pliku i przypisuje mu nazwê
    void loadSound(const std::string& name, const std::string& filename);

    /// Zwraca referencjê do za³adowanego dŸwiêku na podstawie nazwy
    Sound& getSound(const std::string& name);

    /// £aduje muzykê z pliku i przypisuje jej nazwê
    void loadMusic(const std::string& name, const std::string& filename);

    /// Zwraca referencjê do za³adowanej muzyki na podstawie nazwy
    Music& getMusic(const std::string& name);

private:
    /// Kontener przechowuj¹cy za³adowane dŸwiêki
    std::map<std::string, Sound> sounds;

    /// Kontener przechowuj¹cy za³adowane œcie¿ki muzyczne
    std::map<std::string, Music> musics;
};