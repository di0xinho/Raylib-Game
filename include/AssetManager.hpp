#pragma once

#include <raylib.h>
#include <map>
#include <string>
#include <stdexcept>

/// Klasa odpowiadaj�ca za zarz�dzanie zasobami gry (tekstury, czcionki)
class AssetManager
{
public:
    /// Konstruktor/Destruktor
    AssetManager() {}
    ~AssetManager();

    /// �aduje tekstur� z pliku i zapisuje pod podan� nazw�
    void loadTexture(const std::string& name, const std::string& fileName);

    /// Zwraca referencj� do tekstury o zadanej nazwie
    Texture2D& getTexture(const std::string& name);

    /// �aduje czcionk� z pliku i zapisuje pod podan� nazw�
    void loadFont(const std::string& name, const std::string& fileName);

    /// Zwraca referencj� do czcionki o zadanej nazwie
    Font& getFont(const std::string& name);

private:
    /// Kontener na tekstury (klucz to nazwa tekstury)
    std::map<std::string, Texture2D> _textures;

    /// Kontener na czcionki (klucz to nazwa czcionki).
    std::map<std::string, Font> _fonts;
};