#include "Leader.hpp"
#include <string>
#include <Pokemon.hpp>

Leader::Leader(
    std::string name,
    int pokemonLevel,
    std::string pokemonName
  ) {
  this->name = name;
  this->pokemon = new Pokemon(pokemonLevel, pokemonName);
  this->defeated = false;
}

std::string Leader::getName() {
  return this->name;
}

Pokemon *Leader::getPokemon() {
  return this->pokemon;
}

bool Leader::isDefeated() {
  return this->defeated;
}
