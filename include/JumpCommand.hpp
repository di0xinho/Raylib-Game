#pragma once

#include "PlayerCommand.hpp"
#include "Player.hpp"

/// Komenda odpowiadaj¹ca za skok gracza
class JumpCommand : public PlayerCommand {
public:
    /// Wykonuje komendê skoku na przekazanym obiekcie gracza
    void Execute(Player& player) override;
};