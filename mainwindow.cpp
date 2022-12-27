#include "mainwindow.h"

#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->setCentralWidget(ui->plainTextEdit);

  setWindowTitle("notepad-qt");

  // init settings dialog
  settingsDialog = new SettingsDialog(this);

  QTextDocument *doc = ui->plainTextEdit->document();
  QFont font = doc->defaultFont();
  font.setFamily("JetBrains Mono");
  doc->setDefaultFont(font);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionExit_triggered() { this->close(); }

void MainWindow::on_actionNew_triggered() {
  currentFile.clear();
  ui->plainTextEdit->setPlainText(QString());
}

void MainWindow::on_actionOpen_triggered() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open file");
  qDebug() << fileName;
  QFile file(fileName);
  if (!currentFile.isEmpty()) {
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
      QMessageBox::warning(this, "Warning",
                           "Failed to open file: " + file.errorString());
      return;
    }

    qDebug() << fileName;

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();

    qDebug() << text;

    ui->plainTextEdit->setPlainText(text);
    file.close();
  }
}

void MainWindow::on_actionSaveAs_triggered() {
  QString fileName = QFileDialog::getSaveFileName(this, "Save file as");
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, "Warning",
                         "Failed to save file: " + file.errorString());
    return;
  }

  setWindowTitle(fileName);
  currentFile = fileName;
  QTextStream out(&file);
  QString fileText = ui->plainTextEdit->toPlainText();
  out << fileText;
  file.close();
}

void MainWindow::on_actionPrint_triggered() {
  QPrinter printer;
  QPrintDialog printerDialog(&printer, this);
  if (printerDialog.exec() == QDialog::Rejected) {
    QMessageBox::warning(this, "Warning", "Cannot access printer");
    return;
  }
  ui->plainTextEdit->print(&printer);
}

void MainWindow::on_actionSettings_triggered() { settingsDialog->show(); }
