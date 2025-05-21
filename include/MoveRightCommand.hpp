#pragma once

#include "PlayerCommand.hpp"
#include "Player.hpp"

/// Komenda odpowiadaj¹ca za ruch gracza w prawo
class MoveRightCommand : public PlayerCommand {
public:
    /// Wykonuje komendê ruchu w prawo na przekazanym obiekcie gracza
    void Execute(Player& player) override;
};