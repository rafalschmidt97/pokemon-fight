#ifndef INTRODUCTIONWINDOW_HPP
#define INTRODUCTIONWINDOW_HPP

#include <QWidget>

namespace Ui {
class IntroductionWindow;
}

class IntroductionWindow : public QWidget
{
    Q_OBJECT

  public:
    explicit IntroductionWindow(QWidget *parent = 0);
    ~IntroductionWindow();

  private:
    Ui::IntroductionWindow *ui;
};

#endif // INTRODUCTIONWINDOW_HPP
