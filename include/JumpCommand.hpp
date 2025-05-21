#pragma once

#include "PlayerCommand.hpp"
#include "Player.hpp"

/// Komenda odpowiadaj�ca za skok gracza
class JumpCommand : public PlayerCommand {
public:
    /// Wykonuje komend� skoku na przekazanym obiekcie gracza
    void Execute(Player& player) override;
};