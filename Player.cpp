#include "Player.hpp"

#include <string>
#include "Leader.hpp"

Player::Player(
  std::string name,
  int pokemonLevel,
  std::string pokemonName,
  int potions
) : Leader(
  name,
  pokemonLevel,
  pokemonName
){
  this->potions = potions;
}

int Player::getPotions(){
  return this->potions;
}

void Player::usePotion() {
  if(this->potions > 0) {
    this->getPokemon()->increaseHealth(15);
    this->potions--;
  }
}

void Player::addPotion(int amount) {
  this->potions+=amount;
}
