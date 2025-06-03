#include "AttackCommand.hpp"
#include "Player.hpp"

// Wykonuje komend� ataku - rzut no�em, je�li mo�liwe
void AttackCommand::Execute(Player& player) {
    // Je�li gracz mo�e rzuci� broni� (nie trwa cooldown)
    if (player.canShoot()) {
        // Rzu� broni� (np. no�em)
        player.tryThrowWeapon(weaponTexture, weapons);

        // Odtw�rz d�wi�k rzutu no�em, je�li jest ustawiony
        if (auto sound = player.getKnifeThrowSound()) {
            PlaySound(*sound);
        }
    }
}