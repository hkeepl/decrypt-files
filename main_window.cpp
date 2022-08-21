#include "main_window.h"
#include "about_dialog.h"
#include "ui_main_window.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QProcess>
#include <QTextCursor>
#include <QWidget>

// All files of ini suffix are not be encrypted.
const QString kTempSuffix = "ini";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->centralwidget->hide();
  ui->progressBar->setValue(0);
  ui->progressBar->setMinimum(0);
  ui->progressBar->setMaximum(100);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_File_triggered() {
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFile);
  auto ret_code = dialog.exec();
  if (0 == ret_code) {
    return;
  }
  auto file = dialog.selectedFiles()[0];
  QFileInfoList file_info_list;
  file_info_list.append(QFileInfo(file));

  decrypt(file_info_list);
}

void MainWindow::on_actionOpen_Folder_triggered() {
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::DirectoryOnly);
  auto ret_code = dialog.exec();
  if (0 == ret_code) {
    return;
  }
  auto folder = dialog.selectedFiles()[0];

  QDirIterator it(folder, QDir::Files, QDirIterator::Subdirectories);
  QFileInfoList file_info_list;
  while (it.hasNext()) {
    file_info_list.append(QFileInfo(it.next()));
  }

  decrypt(file_info_list);
}

void MainWindow::decrypt(const QFileInfoList &file_info_list) {
  if (ui->centralwidget->isHidden()) {
    ui->centralwidget->show();
  }

  ui->textBrowser->clear();
  QString text_browser_text;
  int prog = 0;

  root_dir_ = file_info_list.front().absolutePath();

  auto list_size = file_info_list.size();
  for (int i = 0; i < list_size; ++i) {
    const auto &file_info = file_info_list.at(i);
    if (file_info.suffix() == kTempSuffix) {
      continue;
    }

    auto file = file_info.absoluteFilePath();
    auto file_base = file_info.absolutePath() + "/" + file_info.baseName();
    auto temp_file = file_base + "_t.txt";
    auto decrpyted_file = file_base + "_t." + kTempSuffix;

    // rename all files since some suffix file cannot be opened by notepad++
    QFile::rename(file, temp_file);

    QStringList params;
    params << temp_file << decrpyted_file;
    // decrypt
    if (QProcess::execute("notepad++.exe", params) >= 0) {
      // remove the old encrypted file
      QFile::remove(temp_file);
      // rename the decrypted file to the old encrypted file
      QFile::rename(decrpyted_file, file);

      // update gui
      text_browser_text += file + "...\n";
      ui->textBrowser->setText(text_browser_text);
      auto text_cursor = ui->textBrowser->textCursor();
      text_cursor.movePosition(QTextCursor::End);
      ui->textBrowser->setTextCursor(text_cursor);
      prog = 1.0 * (i + 1) / list_size * 100;
      ui->progressBar->setValue(prog);
      qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
  }
  text_browser_text +=
      "\n" + QString::number(list_size) + " files are decrypted!";
  ui->textBrowser->setText(text_browser_text);
  auto text_cursor = ui->textBrowser->textCursor();
  text_cursor.movePosition(QTextCursor::End);
  ui->textBrowser->setTextCursor(text_cursor);
}

void MainWindow::on_revealPushButton_clicked() {
  QDesktopServices::openUrl(QUrl::fromLocalFile(root_dir_));
}

void MainWindow::on_actionAbout_triggered() {
  AboutDialog dialog(this);
  dialog.exec();
}
