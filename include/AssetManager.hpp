#pragma once

#include <raylib.h>
#include <map>
#include <string>
#include <stdexcept>

/// Klasa odpowiadaj¹ca za zarz¹dzanie zasobami gry (tekstury, czcionki)
class AssetManager
{
public:
    /// Konstruktor/Destruktor
    AssetManager() {}
    ~AssetManager();

    /// £aduje teksturê z pliku i zapisuje pod podan¹ nazw¹
    void loadTexture(const std::string& name, const std::string& fileName);

    /// Zwraca referencjê do tekstury o zadanej nazwie
    Texture2D& getTexture(const std::string& name);

    /// £aduje czcionkê z pliku i zapisuje pod podan¹ nazw¹
    void loadFont(const std::string& name, const std::string& fileName);

    /// Zwraca referencjê do czcionki o zadanej nazwie
    Font& getFont(const std::string& name);

private:
    /// Kontener na tekstury (klucz to nazwa tekstury)
    std::map<std::string, Texture2D> _textures;

    /// Kontener na czcionki (klucz to nazwa czcionki).
    std::map<std::string, Font> _fonts;
};