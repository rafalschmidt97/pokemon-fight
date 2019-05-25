#include "IntroductionWindow.hpp"
#include "ui_IntroductionWindow.h"

IntroductionWindow::IntroductionWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::IntroductionWindow)
{
  ui->setupUi(this);
}

IntroductionWindow::~IntroductionWindow()
{
  delete ui;
}
