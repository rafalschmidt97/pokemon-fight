#include "Pokemon.hpp"
#include <random>
#include <string>

Pokemon::Pokemon(int level, std::string name) {
  this->name = name;
  this->level = level;
  this->maximumHealth = 3 * level;
  this->currentHealth = this->maximumHealth;
  this->isAlive = true;
  this->experience = 0;
}

void Pokemon::heal() {
  this->maximumHealth = 3 * this->level;
  this->currentHealth = this->maximumHealth;
  this->isAlive = true;
}

void Pokemon::increaseLevel() {
  this->level += 1;
  this->heal();
}

void Pokemon::increaseHealth(int amout) {
  int newCurrentHealth = this->currentHealth + amout;

  if (newCurrentHealth >= this->maximumHealth) {
    this->currentHealth = this->maximumHealth;
  } else {
    this->currentHealth = newCurrentHealth;
  }
}

void Pokemon::decreaseHealth(int amount) {
  int newCurrentHealth = this->currentHealth - amount;

  if (newCurrentHealth <= 0) {
    this->currentHealth = 0;
    this->isAlive = false;
  } else {
    this->currentHealth = newCurrentHealth;
  }
}

void Pokemon::getDamageAmout(int opponentLevel) {
  std::default_random_engine defaultRandomEngine(std::random_device{}());
  std::uniform_int_distribution<> uniformDistribution(opponentLevel - 2, opponentLevel);
  int damage = static_cast<int>(uniformDistribution(defaultRandomEngine));
  this->decreaseHealth(damage);
}

bool Pokemon::increaseExperience(int opponentLevel) {
  int experienceNeededToLevelUp = this->getExperienceNeeded();
  int newExperience = this->experience + opponentLevel * 3;

  if (newExperience >= experienceNeededToLevelUp) {
    this->increaseLevel();
    this->experience = newExperience - experienceNeededToLevelUp;
    return true;
  } else {
    this->experience = newExperience;
    return false;
  }
}

std::string Pokemon::getName() {
  return this->name;
}

int Pokemon::getLevel() {
  return this->level;
}

int Pokemon::getCurrentHealth() {
  return this->currentHealth;
}

int Pokemon::getMaximumHealth() {
  return this->maximumHealth;
}

bool Pokemon::getIsAlive() {
  return this->isAlive;
}

int Pokemon::getExperience() {
  return this->experience;
}

int Pokemon::getExperienceNeeded() {
  return this->level * this->level - 5;
}

void Pokemon::setExperience(int amount) {
  this->experience = amount;
}
