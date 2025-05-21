#include "AssetManager.hpp"

// £adowanie tekstury z pliku i dodanie do mapy
void AssetManager::loadTexture(const std::string& name, const std::string& fileName)
{
    Texture2D tex = LoadTexture(fileName.c_str());
    if (tex.id != 0)
    {
        _textures[name] = tex;
    }
    else
    {
        throw std::runtime_error("Nie udalo sie zaladowac tekstury " + fileName);
    }
}

// Pobieranie tekstury po nazwie (wyrzucany wyj¹tek jeœli brak)
Texture2D& AssetManager::getTexture(const std::string& name)
{
    auto it = _textures.find(name);
    if (it == _textures.end())
        throw std::runtime_error("Nie znaleziono tekstury: " + name);
    return it->second;
}

// £adowanie czcionki z pliku i dodanie do mapy
void AssetManager::loadFont(const std::string& name, const std::string& fileName)
{
    Font font = LoadFont(fileName.c_str());
    if (font.texture.id != 0)
    {
        _fonts[name] = font;
    }
    else
    {
        throw std::runtime_error("Nie udalo sie zaladowac czcionki " + fileName);
    }
}

// Pobieranie czcionki po nazwie (wyrzuca wyj¹tek jeœli brak)
Font& AssetManager::getFont(const std::string& name)
{
    auto it = _fonts.find(name);
    if (it == _fonts.end())
        throw std::runtime_error("Czcionka nie znaleziona: " + name);
    return it->second;
}

// Destruktor: zwalnia wszystkie teksturki i czcionki
AssetManager::~AssetManager()
{
    // Zwalnianie wszystkich tekstur
    for (auto& pair : _textures)
    {
        UnloadTexture(pair.second);
    }
    // Zwalnianie wszystkich czcionek
    for (auto& pair : _fonts)
    {
        UnloadFont(pair.second);
    }
}