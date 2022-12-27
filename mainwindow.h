#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <settingsdialog.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionNew_triggered();

  void on_actionOpen_triggered();

  void on_actionSaveAs_triggered();

  void on_actionExit_triggered();

  void on_actionPrint_triggered();

  void on_actionSettings_triggered();

 private:
  Ui::MainWindow *ui;
  QString currentFile;
  QString font = "monospace";
  qint8 fontSize = 12;

  SettingsDialog *settingsDialog;
};
#endif  // MAINWINDOW_H
