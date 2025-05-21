#pragma once

/// Klasa bazowa dla wszystkich komend wykonywanych przez gracza
class Player;

/// Klasa abstrakcyjna polecenia steruj¹cego graczem
/// Udostêpnia interfejs do wykonania dowolnej akcji na obiekcie gracza
class PlayerCommand {
public:
    /// Wirtualny destruktor
    virtual ~PlayerCommand() = default;

    /// Wykonuje polecenie na przekazanym obiekcie gracza
    /// Musi byæ zaimplementowane w klasach pochodnych
    virtual void Execute(Player& player) = 0;
};