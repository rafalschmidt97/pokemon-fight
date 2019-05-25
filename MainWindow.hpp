#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMovie>
#include <QTimer>
#include <string>
#include "Player.hpp"
#include "Leader.hpp"

#define PLAYER_STARTING_POKEMON_LEVEL 5
#define PLAYER_STARTING_POKEMON_NAME "Pikachu"
#define TEXT_SPEED 75

#define BROCK_STARTING_POKEMON_LEVEL 4
#define BROCK_STARTING_POKEMON_NAME "Bulbasaur"
#define MISTY_STARTING_POKEMON_LEVEL 7
#define MISTY_STARTING_POKEMON_NAME "Squirtle"
#define GARRY_STARTING_POKEMON_LEVEL 12
#define GARRY_STARTING_POKEMON_NAME "Charmander"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  int brockPokemonLevel;
  int mistyPokemonLevel;
  int garryPokemonLevel;

 private:
  Ui::MainWindow *ui;
  QMediaPlayer *musicPlayer;
  QMovie *introductionMovie;
  QTimer *updateBattle;
  Player *player;
  Leader *opponent;

 private slots:
  unsigned long getTextActionTime(std::string text);
  void changeGameAction(std::string actionName);
  void changeBattleAction(std::string actionName);
  void on_buttonIntroductionView_released();
  void on_buttonBrockStoryView_released();
  void on_buttonMistyStoryView_released();
  void on_buttonGarryStoryView_released();
  void on_buttonHealStoryView_released();
  void on_buttonCloseStoryView_released();
  void on_buttonSoundStoryView_released();
  void on_buttonSaveStoryView_released();

  void on_buttonGarryCharacterSelectView_released();
  void on_buttonMistyCharacterSelectView_released();
  void on_buttonAshCharacterSelectView_released();

  void on_buttonFightBatteView_released();
  void on_buttonPokemonBatteView_released();
  void on_buttonItemBatteView_released();
  void on_buttonRunBatteView_released();
  void on_buttonFightCancelBattleFight_released();
  void on_buttonPokemonCancelBattleFight_released();
  void on_buttonItemCancelBattleFight_released();
  void on_buttonItemBikeBattleFight_released();
  void on_buttonRunCancelBattleFight_released();
  void on_buttonRunConfirmCancelBattleFight_released();
  void on_buttonFightTackleBattleFight_released();
  void initializeBattle();
  void updateBattleView();
  void animateMovePokemonFight(std::string character, long x, int time);
  void animatePlayerPokemonFight();
  void animateOpponentPokemonFight();
  void animateTextActionFight(std::string text, std::string goToAction);
  void on_buttonItemPotionBattleFight_released();
};

#endif // MAINWINDOW_HPP
