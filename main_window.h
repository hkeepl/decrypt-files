#pragma once

#include <QFileInfoList>
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
  void on_actionOpen_File_triggered();

  void on_actionOpen_Folder_triggered();

  void on_revealPushButton_clicked();

  void on_actionAbout_triggered();

private:
  void decrypt(const QFileInfoList &file_info_list);

private:
  Ui::MainWindow *ui;
  QString root_dir_;
};
