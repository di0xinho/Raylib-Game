#include "StopMovingCommand.hpp"

/// Wykonuje polecenie zatrzymania ruchu gracza (ustawia pr�dko�� w poziomie na zero)
void StopMovingCommand::Execute(Player& player) {
    player.StopMoving();
}