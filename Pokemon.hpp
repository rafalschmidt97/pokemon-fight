#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>

class Pokemon {
 public:
  Pokemon(int level, std::string name);

  void heal();
  void increaseLevel();
  void increaseHealth(int amout);
  void decreaseHealth(int amount);
  void getDamageAmout(int opponentLevel);
  bool increaseExperience(int opponentLevel);
  std::string getName();
  int getLevel();
  int getCurrentHealth();
  int getMaximumHealth();
  bool getIsAlive();
  int getExperience();
  int getExperienceNeeded();
  void setExperience(int amount);

 private:
  std::string name;
  int level;
  int currentHealth;
  int maximumHealth;
  int isAlive;
  int experience;
};

#endif // POKEMON_HPP
