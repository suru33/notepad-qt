#include "mainwindow.h"

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

  this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionExit_triggered() { this->close(); }

void MainWindow::on_actionNew_triggered() {
  currentFile.clear();
  ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open file");
  QFile file(fileName);
  currentFile = fileName;
  if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, "Warning",
                         "Failed to open file: " + file.errorString());
    return;
  }
  setWindowTitle(fileName);
  QTextStream in(&file);
  QString text = in.readAll();
  ui->textEdit->setText(text);
  file.close();
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
  QString fileText = ui->textEdit->toPlainText();
  out << fileText;
  file.close();
}

void MainWindow::on_actionPrint_triggered() {
  QPrinter printer;
  printer.setPrinterName("Printer name");
  QPrintDialog printerDialog(&printer, this);
  if (printerDialog.exec() == QDialog::Rejected) {
    QMessageBox::warning(this, "Warning", "Cannot access printer");
    return;
  }
  ui->textEdit->print(&printer);
}
