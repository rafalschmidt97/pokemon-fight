#include "About.hpp"
#include "ui_About.h"

About::About(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::About)
{
  ui->setupUi(this);
}

About::~About()
{
  delete ui;
}
