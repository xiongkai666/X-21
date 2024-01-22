#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include <QtGlobal>
#include <QElapsedTimer>
#include <iostream>
#include <QDebug>
#include "rhxglobals.h"
#include "controllerinterface.h"

ControllerInterface::ControllerInterface(const QString& boardSerialNumber, QObject* parent) :
    QObject(parent)
{
    openController(boardSerialNumber);
}

ControllerInterface::~ControllerInterface()
{

}
void ControllerInterface::openController(const QString& boardSerialNumber)
{
    qDebug() << "boardSerialNumber" << boardSerialNumber;
    rhxController->open(boardSerialNumber.toStdString());
    qDebug() << "success to run resetBoard()";

    // Upload FPGA bit file.
    QString bitfilename;

    bitfilename = ConfigFileRHSController;

    QString currentPath = QCoreApplication::applicationDirPath();
    QDir currentDir(currentPath);
    currentDir.cdUp();
    currentDir.cdUp();
    QString grandparentPath = currentDir.absolutePath();

    if (!rhxController->uploadFPGABitfile(QString( grandparentPath  + "/" + bitfilename).toStdString())) {
        QMessageBox::critical(nullptr, tr("Configuration File Error: Software Aborting"),
                              tr("Cannot upload configuration file: ") + bitfilename +
                              tr(".  Make sure file is in the same directory as the executable file."));
        exit(EXIT_FAILURE);
    }

    qDebug() << "start to run resetBoard()";
    rhxController->resetBoard();
}

