#pragma once

#include "PlayerCommand.hpp"
#include "Player.hpp"

/// Polecenie zatrzymania ruchu gracza (ustawia pr�dko�� w poziomie na zero)
class StopMovingCommand : public PlayerCommand {
public:
    /// Wykonuje zatrzymanie ruchu gracza
    void Execute(Player& player) override;
};