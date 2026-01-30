#include "canceldownload.h"
#include <QIcon>
#include <QCoreApplication>

cancelDownload::cancelDownload(QWidget *parent) : QMessageBox(parent)
{
    this->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    this->setDefaultButton(QMessageBox::No);
    this->setText(QCoreApplication::tr("Cancel download in progress?"));
    this->setIcon(QMessageBox::Question);
    this->setWindowIcon(QIcon::fromTheme("youtubedl-gui"));
}
