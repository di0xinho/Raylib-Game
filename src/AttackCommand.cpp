#include "AttackCommand.hpp"
#include "Player.hpp"

// Wykonuje komendê ataku - rzut no¿em, jeœli mo¿liwe
void AttackCommand::Execute(Player& player) {
    // Jeœli gracz mo¿e rzuciæ broni¹ (nie trwa cooldown)
    if (player.canShoot()) {
        // Rzuæ broni¹ (np. no¿em)
        player.tryThrowWeapon(weaponTexture, weapons);

        // Odtwórz dŸwiêk rzutu no¿em, jeœli jest ustawiony
        if (auto sound = player.getKnifeThrowSound()) {
            PlaySound(*sound);
        }
    }
}