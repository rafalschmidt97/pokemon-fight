#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Leader.hpp"

class Player : public Leader {
 public:
  Player(
    std::string name,
    int pokemonLevel,
    std::string pokemonName,
    int potions
  );

  int getPotions();
  void usePotion();
  void addPotion(int amount);

 private:
  int potions;
};

#endif // PLAYER_HPP
