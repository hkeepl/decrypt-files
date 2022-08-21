#include "about_dialog.h"
#include "ui_about_dialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent, Qt::WindowCloseButtonHint), ui(new Ui::AboutDialog) {
  ui->setupUi(this);
}

AboutDialog::~AboutDialog() { delete ui; }
