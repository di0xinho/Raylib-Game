#pragma once

#include "PlayerCommand.hpp"
#include "Player.hpp"
#include "raylib.h"
#include <vector>
#include "Weapon.hpp"

/// Klasa reprezentuj�ca polecenie ataku dla gracza (wzorzec Command)
class AttackCommand : public PlayerCommand {
public:
    /// Konstruktor przyjmuj�cy tekstur� broni oraz referencj� do wektora broni
    AttackCommand(Texture2D* weaponTexture, std::vector<Weapon>& weapons): 
        weaponTexture(weaponTexture), weapons(weapons) {}

    /// Wykonuje komend� ataku na przekazanym obiekcie Player
    void Execute(Player& player) override;

private:
        Texture2D* weaponTexture;        // Wska�nik na tekstur� broni
        std::vector<Weapon>& weapons;    // Referencja do wektora aktywnych broni
};