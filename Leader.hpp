#ifndef LEADER_HPP
#define LEADER_HPP

#include <string>
#include <Pokemon.hpp>

class Leader {
 public:
  Leader(
    std::string name,
    int pokemonLevel,
    std::string pokemonName
  );
  std::string getName();
  Pokemon *getPokemon();
  bool isDefeated();

 private:
  std::string name;
  Pokemon *pokemon;
  bool defeated;
};

#endif // LEADER_HPP
