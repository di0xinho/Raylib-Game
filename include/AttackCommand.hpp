#pragma once

#include "PlayerCommand.hpp"
#include "Player.hpp"

/// Klasa reprezentuj�ca polecenie ataku dla gracza (wzorzec Command)
class AttackCommand : public PlayerCommand {
public:
    /// Wykonuje komend� ataku na przekazanym obiekcie Player
    void Execute(Player& player) override;
};