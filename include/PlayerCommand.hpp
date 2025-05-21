#pragma once

/// Klasa bazowa dla wszystkich komend wykonywanych przez gracza
class Player;

/// Klasa abstrakcyjna polecenia steruj�cego graczem
/// Udost�pnia interfejs do wykonania dowolnej akcji na obiekcie gracza
class PlayerCommand {
public:
    /// Wirtualny destruktor
    virtual ~PlayerCommand() = default;

    /// Wykonuje polecenie na przekazanym obiekcie gracza
    /// Musi by� zaimplementowane w klasach pochodnych
    virtual void Execute(Player& player) = 0;
};