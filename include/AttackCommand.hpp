#pragma once

#include "PlayerCommand.hpp"
#include "Player.hpp"
#include "raylib.h"
#include <vector>
#include "Weapon.hpp"

/// Klasa reprezentuj¹ca polecenie ataku dla gracza (wzorzec Command)
class AttackCommand : public PlayerCommand {
public:
    /// Konstruktor przyjmuj¹cy teksturê broni oraz referencjê do wektora broni
    AttackCommand(Texture2D* weaponTexture, std::vector<Weapon>& weapons): 
        weaponTexture(weaponTexture), weapons(weapons) {}

    /// Wykonuje komendê ataku na przekazanym obiekcie Player
    void Execute(Player& player) override;

private:
        Texture2D* weaponTexture;        // WskaŸnik na teksturê broni
        std::vector<Weapon>& weapons;    // Referencja do wektora aktywnych broni
};