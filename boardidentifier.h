#ifndef BOARDIDENTIFIER_H
#define BOARDIDENTIFIER_H

#include <QObject>
#include <cstdint>

//#include "demodialog.h"
//#include "startupdialog.h"
#include "rhxcontroller.h"
//#include "syntheticrhxcontroller.h"
//#include "playbackrhxcontroller.h"
#include "rhxglobals.h"
//#include "controlwindow.h"
#include "controllerinterface.h"
#include "systemstate.h"
//#include "commandparser.h"

const QString RHDBoardString = "RHD USB Interface Board";
const QString RHSBoardString = "RHS USB Interface Board";
const QString UnknownString = "Unknown Device";

struct ControllerInfo {
    QString serialNumber;
    bool expConnected;
    BoardMode boardMode;
};

class BoardIdentifier : public QObject
{
    Q_OBJECT
public:
    BoardIdentifier(QObject *parent = nullptr);
    ~BoardIdentifier();
    static QString getBoardTypeString(BoardMode mode);
    static QIcon getIcon(const QString& boardType, QStyle *style, int size);

    QVector<ControllerInfo*> getConnectedControllersInfo();

    void startSoftware(ControllerType controllerType, AmplifierSampleRate sampleRate, StimStepSize stimStepSize,
                       const QString& boardSerialNumber);

private:
    void identifyController(ControllerInfo* controller, int index);
    QString opalKellyModelName(int model) const;
    bool uploadFpgaBitfileQMessageBox(const QString& filename);

    QVector<ControllerInfo*> controllers;

    AbstractRHXController *rhxController;
    ControllerInterface *controllerInterface;

    CPionway *dev;
};

#endif // BOARDIDENTIFIER_H
