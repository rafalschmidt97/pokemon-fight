#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QMovie>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QApplication>
#include <QTimer>
#include <QFontDatabase>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <string>
#include <sstream>
#include <random>
#include <iostream>
#include "Leader.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  QFontDatabase::addApplicationFont(":/fonts/assets/Pokemon_GB.ttf");
  ui->setupUi(this);

  QMediaPlaylist *playlist = new QMediaPlaylist();
  playlist->addMedia(QUrl("qrc:/sounds/assets/song.mp3"));
  playlist->setPlaybackMode(QMediaPlaylist::Loop);

  musicPlayer = new QMediaPlayer();
  musicPlayer->setPlaylist(playlist);
  musicPlayer->setVolume(50);
  musicPlayer->play();

  introductionMovie = new QMovie(":/images/assets/intro.gif");
  ui->movieIntroductionView->setMovie(introductionMovie);
  introductionMovie->start();
}

MainWindow::~MainWindow() {
  delete ui;
}

unsigned long MainWindow::getTextActionTime(std::string text) {
  return text.length() * TEXT_SPEED;
}

void MainWindow::changeGameAction(std::string actionName) {
  if (actionName == "characters") {
    ui->game->setCurrentIndex(1);
  } else if (actionName == "story") {
    ui->game->setCurrentIndex(2);
  } else if (actionName == "battle") {
    ui->game->setCurrentIndex(3);
  } else {
    ui->game->setCurrentIndex(0);
  }
}

void MainWindow::changeBattleAction(std::string actionName) {
  if (actionName == "fight") {
    ui->actionsBatteView->setCurrentIndex(1);
  } else if (actionName == "pokemon") {
    ui->actionsBatteView->setCurrentIndex(2);
  } else if (actionName == "item") {
    ui->actionsBatteView->setCurrentIndex(3);
  } else if (actionName == "run") {
    ui->actionsBatteView->setCurrentIndex(4);
  } else {
    ui->actionsBatteView->setCurrentIndex(0);
  }
}

void MainWindow::on_buttonIntroductionView_released() {
  QString homePath = QDir::homePath();
  QFile file(homePath + "/pokemonSave.txt");

  brockPokemonLevel = BROCK_STARTING_POKEMON_LEVEL;
  mistyPokemonLevel = MISTY_STARTING_POKEMON_LEVEL;
  garryPokemonLevel = GARRY_STARTING_POKEMON_LEVEL;

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    player = new Player("Ash", PLAYER_STARTING_POKEMON_LEVEL, PLAYER_STARTING_POKEMON_NAME, 0);
    ui->buttonMistyStoryView->setVisible(false);
    ui->buttonGarryStoryView->setVisible(false);
    changeGameAction("characters");
  } else {
    QTextStream in(&file);
    int lineCounter = 0;
    std::string saveArray[7];

    while (!in.atEnd()) {
      QString line = in.readLine();
      saveArray[lineCounter] = line.toStdString();
      lineCounter++;
    }

    if (saveArray[1] == "0") {
      player = new Player("Ash", PLAYER_STARTING_POKEMON_LEVEL, PLAYER_STARTING_POKEMON_NAME, 0);
      ui->buttonMistyStoryView->setVisible(false);
      ui->buttonGarryStoryView->setVisible(false);
      changeGameAction("characters");
    } else {
      int playerPokemonLevel = std::stoi(saveArray[1]);
      int playerPokemonHealth = std::stoi(saveArray[2]);
      int playerPokemonExperience = std::stoi(saveArray[3]);
      int playerPotions = std::stoi(saveArray[4]);
      player = new Player("Ash", playerPokemonLevel, "Pikachu", playerPotions);
      player->getPokemon()->decreaseHealth(player->getPokemon()->getMaximumHealth() - playerPokemonHealth);
      player->getPokemon()->setExperience(playerPokemonExperience);

      if (saveArray[5] == "1") {
        ui->buttonMistyStoryView->setVisible(true);
      } else {
        ui->buttonMistyStoryView->setVisible(false);
      }

      if (saveArray[6] == "1") {
        ui->buttonGarryStoryView->setVisible(true);
      } else {
        ui->buttonGarryStoryView->setVisible(false);
      }

      changeGameAction("story");
    }
  }
}

void MainWindow::on_buttonBrockStoryView_released() {
  opponent = new Leader("Brock", brockPokemonLevel, BROCK_STARTING_POKEMON_NAME);
  initializeBattle();
}

void MainWindow::on_buttonMistyStoryView_released() {
  opponent = new Leader("Misty", mistyPokemonLevel, MISTY_STARTING_POKEMON_NAME);
  initializeBattle();
}

void MainWindow::on_buttonGarryStoryView_released() {
  opponent = new Leader("Garry", garryPokemonLevel, GARRY_STARTING_POKEMON_NAME);
  initializeBattle();
}

void MainWindow::on_buttonHealStoryView_released() {
  player->getPokemon()->heal();
  QMessageBox healMessage;
  healMessage.setText(QString::fromStdString(player->getPokemon()->getName() + " back to perfect health!"));
  healMessage.exec();
}

void MainWindow::on_buttonCloseStoryView_released() {
  QApplication::closeAllWindows();
}

void MainWindow::on_buttonSoundStoryView_released() {
  if (musicPlayer->volume() == 50) {
    musicPlayer->setVolume(0);
  } else {
    musicPlayer->setVolume(50);
  }
}

void MainWindow::on_buttonSaveStoryView_released() {
  QString homePath = QDir::homePath();
  QFile file(homePath + "/pokemonSave.txt");

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    std::cout << "Something went wrong while saving!";
  } else {
    QTextStream out(&file);
    out << 1 << "\n";
    out << player->getPokemon()->getLevel() << "\n";
    out << player->getPokemon()->getCurrentHealth() << "\n";
    out << player->getPokemon()->getExperience() << "\n";
    out << player->getPotions() << "\n";
    out << ui->buttonMistyStoryView->isVisible() << "\n";
    out << ui->buttonGarryStoryView->isVisible() << "\n";
  }
}

void MainWindow::on_buttonGarryCharacterSelectView_released() {
  QMessageBox errorCharacter;
  errorCharacter.setText("Did you ever play pokemon?");
  errorCharacter.setInformativeText("Gary Oak is Professor Oak's grandson and Ash Ketchum's rival in the first few seasons. His starter Pokémon was a Squirtle that later evolved into a Blastoise.");
  errorCharacter.exec();
}

void MainWindow::on_buttonMistyCharacterSelectView_released() {
  QMessageBox errorCharacter;
  errorCharacter.setText("There are no naked photos. Try again...");
  errorCharacter.setInformativeText("Misty is a character whose first appearance was in the very first episode of the anime series, Pokémon - I Choose You! She's 11.");

  errorCharacter.exec();
}

void MainWindow::on_buttonAshCharacterSelectView_released() {
  changeGameAction("story");
}

void MainWindow::on_buttonFightBatteView_released() {
  changeBattleAction("fight");
}

void MainWindow::on_buttonPokemonBatteView_released() {
  changeBattleAction("pokemon");
}

void MainWindow::on_buttonItemBatteView_released() {
  changeBattleAction("item");
}

void MainWindow::on_buttonRunBatteView_released() {
  changeBattleAction("run");
}

void MainWindow::on_buttonFightCancelBattleFight_released() {
  changeBattleAction("select");
}

void MainWindow::on_buttonPokemonCancelBattleFight_released() {
  changeBattleAction("select");
}

void MainWindow::on_buttonItemCancelBattleFight_released() {
  changeBattleAction("select");
}

void MainWindow::on_buttonItemBikeBattleFight_released() {
  animateTextActionFight("You can't use bike now!", "select");
}

void MainWindow::on_buttonRunCancelBattleFight_released() {
  changeBattleAction("select");
}

void MainWindow::on_buttonRunConfirmCancelBattleFight_released() {
  std::default_random_engine defaultRandomEngine(std::random_device{}());
  std::uniform_int_distribution<> uniformDistribution(0, 1);
  bool willEscape = static_cast<bool>(uniformDistribution(defaultRandomEngine));

  if (willEscape) {
    animateTextActionFight("You escaped!", "story");
    updateBattle->stop();
  } else {
    animateTextActionFight("Can't escape!", "nowhere");
    QTimer::singleShot((getTextActionTime("Can't escape!") + 2000), [=] {
      animateOpponentPokemonFight();
    });
  }
}

void MainWindow::on_buttonFightTackleBattleFight_released() {
  animatePlayerPokemonFight();
}

void MainWindow::initializeBattle() {
  changeGameAction("battle");
  updateBattleView();
  ui->playerPokemonBattleView->setStyleSheet("background-image:url(':/images/assets/character-back.jpg') no-repeat;");

  if (opponent->getName() == "Brock") {
    ui->opponentPokemonBattleView->setStyleSheet("background-image:url(':/images/assets/brock.jpg') no-repeat;");
  } else if (opponent->getName() == "Misty") {
    ui->opponentPokemonBattleView->setStyleSheet("background-image:url(':/images/assets/misty.jpg') no-repeat;");
  } else {
    ui->opponentPokemonBattleView->setStyleSheet("background-image:url(':/images/assets/garry.jpg') no-repeat;");
  }

  if (!player->getPokemon()->getIsAlive()) {
    animateTextActionFight("Your pokemon died!", "story");
  } else {
    animateTextActionFight(opponent->getName() + " wants to fight!", "select");

    QTimer::singleShot(getTextActionTime(opponent->getName() + " wants to fight!") + 2000, [=] {
      if (player->getPokemon()->getName() == "Pikachu") {
        ui->playerPokemonBattleView->setStyleSheet("background-image:url(':/images/assets/pikachu-back.jpg') no-repeat;");
      }

      if (opponent->getPokemon()->getName() == "Bulbasaur") {
        ui->opponentPokemonBattleView->setStyleSheet("background-image:url(':/images/assets/bulbasaur-front.jpg') no-repeat;");
      } else if (opponent->getPokemon()->getName() == "Charmander") {
        ui->opponentPokemonBattleView->setStyleSheet("background-image:url(':/images/assets/charmander-front.jpg') no-repeat;");
      } else if (opponent->getPokemon()->getName() == "Squirtle") {
        ui->opponentPokemonBattleView->setStyleSheet("background-image:url(':/images/assets/squirtle-front.jpg') no-repeat;");
      } else {
        ui->opponentPokemonBattleView->setStyleSheet("background-image:url(':/images/assets/pikachu-back.jpg') no-repeat;");
      }
    });
  }

  updateBattle = new QTimer(this);
  connect(updateBattle, SIGNAL(timeout()), this, SLOT(updateBattleView()));
  updateBattle->start(100);
}

void MainWindow::updateBattleView() {
  ui->playerPokemonHealthCurrentBattleView->setText(QString::number(player->getPokemon()->getCurrentHealth()));
  ui->playerPokemonHealthMaxBattleView->setText(QString::number(player->getPokemon()->getMaximumHealth()));
  ui->playerPokemonLevelBattleView->setText(QString::number(player->getPokemon()->getLevel()));
  ui->playerPokemonHealthBattleView->setValue(player->getPokemon()->getCurrentHealth());
  ui->playerPokemonHealthBattleView->setMaximum(player->getPokemon()->getMaximumHealth());
  ui->playerPokemonExperienceBattleView->setValue(player->getPokemon()->getExperience());
  ui->playerPokemonExperienceBattleView->setMaximum(player->getPokemon()->getExperienceNeeded());

  ui->opponentPokemonHealthBattleView->setMaximum(opponent->getPokemon()->getMaximumHealth());
  ui->opponentPokemonHealthBattleView->setValue(opponent->getPokemon()->getCurrentHealth());
  ui->opponentPokemonLevelBattleView->setText(QString::number(opponent->getPokemon()->getLevel()));

  if (player->getPotions() > 0) {
    std::string potionText = "POTIONS " + std::to_string(player->getPotions()) + "x";
    ui->buttonItemPotionBattleFight->setVisible(true);
    ui->buttonItemPotionBattleFight->setText(QString::fromStdString(potionText));
  } else {
    ui->buttonItemPotionBattleFight->setVisible(false);
  }
}

void MainWindow::animateMovePokemonFight(std::string character, long x, int time) {
  if(character == "player") {
    QTimer::singleShot(time, [=] {
      ui->playerPokemonBattleView->setGeometry(
        ui->playerPokemonBattleView->geometry().x() + static_cast<int>(x),
        ui->playerPokemonBattleView->geometry().y(),
        ui->playerPokemonBattleView->geometry().width(),
        ui->playerPokemonBattleView->geometry().height()
      );
    });
  } else {
    QTimer::singleShot(time, [=] {
      ui->opponentPokemonBattleView->setGeometry(
        ui->opponentPokemonBattleView->geometry().x() + static_cast<int>(x),
        ui->opponentPokemonBattleView->geometry().y(),
        ui->opponentPokemonBattleView->geometry().width(),
        ui->opponentPokemonBattleView->geometry().height()
      );
    });
  }
}

void MainWindow::animatePlayerPokemonFight() {
  animateMovePokemonFight("player", 20, 500);
  animateMovePokemonFight("player", 10, 1000);
  animateMovePokemonFight("opponent", 5, 1100);
  animateMovePokemonFight("player", -10, 1200);
  animateMovePokemonFight("opponent", -5, 1300);
  animateMovePokemonFight("player", -20, 2000);

  opponent->getPokemon()->getDamageAmout(player->getPokemon()->getLevel());
  animateTextActionFight(player->getPokemon()->getName() + " used TACKLE!", "nowhere");

  QTimer::singleShot(getTextActionTime(player->getPokemon()->getName() + " used TACKLE!") + 2000, [=] {
    if (opponent->getPokemon()->getIsAlive()) {
      animateOpponentPokemonFight();
    } else {
      if (opponent->getName() == "Brock") {
        if (player->getPotions() < 8) {
          player->addPotion(2);
        }
        ui->buttonMistyStoryView->setVisible(true);
      } else if (opponent->getName() == "Misty") {
        if (player->getPotions() < 9) {
          player->addPotion(1);
        }
        ui->buttonGarryStoryView->setVisible(true);
      } else if (opponent->getName() == "Garry") {
        QMessageBox endingMessage;
        endingMessage.setText(QString::fromStdString("YOU WIN THIS GAME AND UNLOCKED NG+"));
        endingMessage.exec();

        brockPokemonLevel = 20;
        mistyPokemonLevel = 30;
        garryPokemonLevel = 50;
      }

      animateTextActionFight("TRAINER was defeated!", "nowhere");
      QTimer::singleShot(getTextActionTime("TRAINER was defeated!") + 2000, [=] {
        if (player->getPokemon()->increaseExperience(opponent->getPokemon()->getLevel())) {
          animateTextActionFight(player->getPokemon()->getName() + " grew to level " + std::to_string(player->getPokemon()->getLevel()) + "!", "story");
        } else {
          animateTextActionFight(player->getPokemon()->getName() + " gained " + std::to_string(opponent->getPokemon()->getLevel() * 3) + " EXP. Points!", "story");
        }
      });
    }
  });
}

void MainWindow::animateOpponentPokemonFight() {
  animateMovePokemonFight("opponent", -20, 500);
  animateMovePokemonFight("opponent", -10, 1000);
  animateMovePokemonFight("player", -5, 1100);
  animateMovePokemonFight("opponent", 10, 1200);
  animateMovePokemonFight("player", 5, 1300);
  animateMovePokemonFight("opponent", 20, 2000);

  player->getPokemon()->getDamageAmout(opponent->getPokemon()->getLevel());
  animateTextActionFight(opponent->getPokemon()->getName() +  " used TACKLE!", "nowhere");

  QTimer::singleShot(getTextActionTime(opponent->getPokemon()->getName() +  " used TACKLE!") + 2000, [=] {
    if (player->getPokemon()->getIsAlive()) {
      ui->actionsBatteView->setCurrentIndex(0);
    } else {
      animateTextActionFight("Player was defeated!", "story");
    }
  });
}

void MainWindow::animateTextActionFight(std::string textAction, std::string goToAction) {
  ui->actionsBatteView->setCurrentIndex(5);
  ui->labelTextBattleFight->setText("");

  for (unsigned long time = 0; time <= getTextActionTime(textAction); time+= TEXT_SPEED) {
    QTimer::singleShot(time, [=] {
      std::string textToRender = textAction.substr(0, time / TEXT_SPEED);
      ui->labelTextBattleFight->setText(QString::fromStdString(textToRender));
    });
  }

  if (goToAction == "story"){
    QTimer::singleShot((getTextActionTime(textAction) + 2000), [=] {
      changeGameAction("story");
      updateBattle->stop();
    });
  } else if (goToAction == "select") {
    QTimer::singleShot((getTextActionTime(textAction) + 2000), [=] {
      changeBattleAction("select");
    });
  }
}

void MainWindow::on_buttonItemPotionBattleFight_released() {
  player->usePotion();
  animateTextActionFight("Player used POTION!", "select");
}
