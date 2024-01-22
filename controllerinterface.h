#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

#include <QObject>
#include "rhxcontroller.h"
class ControllerInterface : public QObject
{
    Q_OBJECT
public:

    ControllerInterface(const QString& boardSerialNumber, QObject *parent = nullptr);
    ~ControllerInterface();

private:
    void openController(const QString& boardSerialNumber);
    AbstractRHXController *rhxController;
};

#endif // CONTROLLERINTERFACE_H
