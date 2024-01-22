#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFile>
#include <map>

class SystemState : public QObject
{
    Q_OBJECT
public:
    SystemState(QObject *parent = nullptr);
    ~SystemState();
};
#endif // SYSTEMSTATE_H
