#pragma once

#include "PlayerCommand.hpp"
#include "Player.hpp"

/// Komenda odpowiadaj¹ca za ruch gracza w lewo
class MoveLeftCommand : public PlayerCommand {
public:
    /// Wykonuje komendê ruchu w lewo na przekazanym obiekcie gracza
    void Execute(Player& player) override;
};