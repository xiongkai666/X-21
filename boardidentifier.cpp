#include <Qsettings>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include "boardidentifier.h"

BoardIdentifier::BoardIdentifier(QObject *parent) : QObject(parent)
{
    dev = new CPionway;
}

BoardIdentifier::~BoardIdentifier()
{
    while (controllers.size() > 0) {
        delete controllers.first();
        controllers.remove(0);
    }
}

// Return a QString description of the specified board.
QString BoardIdentifier::getBoardTypeString(BoardMode mode)
{
    switch (mode) {
    case RHDUSBInterfaceBoard:
        return RHDBoardString;
    case RHSUSBInterfaceBoard:
        return RHSBoardString;
    default:       
        return UnknownString;
    }
}

// Return a QIcon with a picture of the specified board.
QIcon BoardIdentifier::getIcon(const QString& boardType, QStyle *style, int size)
{
    if (boardType == RHDBoardString || boardType == RHSBoardString)
        return QIcon(":/images/rhxcontrollerboard.png");
    else
        return QIcon(style->standardIcon(QStyle::SP_MessageBoxQuestion).pixmap(size));
}

// Return a QVector of ControllerInfo structures containing information about each controller, after uploading bit files
// to each controller and determining its characteristics.
QVector<ControllerInfo*> BoardIdentifier::getConnectedControllersInfo()
{
    int i, nDevices;
    dev->GetDeviceCount(&nDevices);
    qDebug() << "nDevices" << nDevices;
    for (i = 0; i < nDevices; ++i) {
        ControllerInfo *controller = new ControllerInfo;
        identifyController(controller, i);
        controllers.append(controller);
    }
    delete dev;
    return controllers;
}

// Populate variables in 'controller'. Upload a bit file, writes some WireIns, and reads some WireOuts.
void BoardIdentifier::identifyController(ControllerInfo *controller, int index)
{
    // Populate serialNumber field.
    controller->serialNumber = dev->GetDeviceListSerial(index).c_str();

    QString modelName = opalKellyModelName(dev->GetDeviceListModel(index));

    controller->boardMode = UnknownUSB3Device;

    // Open device.
    if (dev->OpenBySerial(dev->GetDeviceListSerial(index).c_str()) != CPionway::NO_ERR) {
        return;
    }

    // Set up default PLL.
    //dev->LoadDefaultPLLConfiguration();

    QString bitfilename = ConfigFileRHSController;

    QString currentPath = QCoreApplication::applicationDirPath();
    QDir currentDir(currentPath);
    currentDir.cdUp();
    currentDir.cdUp();
    QString grandparentPath = currentDir.absolutePath();

    // Upload bit file.
    if (!uploadFpgaBitfileQMessageBox( grandparentPath + "/X-21/FPGA-bitfiles/" + bitfilename)) {
        QMessageBox::critical(nullptr, QObject::tr("Configuration File Error: Software Aborting"),
                              QObject::tr("Cannot upload configuration file: ") + bitfilename +
                              QObject::tr(".  Make sure file is in the same directory as the executable file."));
        exit(EXIT_FAILURE);
    }   
    RHXController::resetBoard(dev);

    // set boardmode.
    controller->boardMode = RHSUSBInterfaceBoard;

}

// Return name of Pionway board based on model code.
QString BoardIdentifier::opalKellyModelName(int model) const
{
    switch (model) {
    case PW_PRODUCT_XMS6301_LX45:
        return "XMS6301_LX45";
    case PW_PRODUCT_XMS6301_LX75:
        return "XMS6301_LX75";
    case PW_PRODUCT_XMS6301_LX100:
        return "XMS6301_LX100";
    case PW_PRODUCT_XMS6301_LX150:
        return "XMS6301_LX150";
    case PW_PRODUCT_XMS6302_LX45:
        return "XMS6302_LX45";
    case PW_PRODUCT_XMS6302_LX75:
        return "XMS6302_LX75";
    case PW_PRODUCT_XMS6302_LX100:
        return "XMS6302_LX100";
    case PW_PRODUCT_XMS6302_LX150:
        return "XMS6302_LX150";
    default:
        return "UNKNOWN";
    }
}

// Upload bitfile specified by 'filename' to the FPGA, reporting any errors that occur as a QMessageBox.
bool BoardIdentifier::uploadFpgaBitfileQMessageBox(const QString& filename)
{
    CPionway::ErrorCode errorCode = dev->ConfigureFPGA(filename.toStdString());
    switch (errorCode) {
    case CPionway::NO_ERR:
        break;
    case CPionway::DEVICE_NOT_OPEN:
        QMessageBox::critical(nullptr, "FPGA configuration failed", "Device not open.");
        return false;
    case CPionway::FILE_ERROR:
        QMessageBox::critical(nullptr, "FPGA configuration failed", "Cannot find configuration file.");
        return false;
    case CPionway::INVALID_BITSTREAM:
        QMessageBox::critical(nullptr, "FPGA configuration failed", "Bitstream is not properly formatted.");
        return false;
    case CPionway::DONE_NOT_HIGH:
        QMessageBox::critical(nullptr, "FPGA configuration failed", "FPGA DONE signal did not assert after configuration. Make sure switch on Pionway board is set to 'USB' not 'PROM'.");
        return false;
    case CPionway::TRANSFER_ERROR:
        QMessageBox::critical(nullptr, "FPGA configuration failed", "USB error occurred during download.");
        return false;
    case CPionway::COMMUNICATION_ERROR:
        QMessageBox::critical(nullptr, "FPGA configuration failed", "Communication error with firmware.");
        return false;
    case CPionway::UNSUPPORTED_FEATURE:
        QMessageBox::critical(nullptr, "FPGA configuration failed", "Unsupported feature.");
        return false;
    default:
        QMessageBox::critical(nullptr, "FPGA configuration failed", "Unknown error.");
        return false;
    }

    // Check for Pionway Pionway support in the FPGA configuration.
    if (dev->IsPionwayEnabled() == false) {
        QMessageBox::critical(nullptr, "FPGA configuration failed",
                              "Pionway Pionway support is not enabled in this FPGA configuration.");
        return false;
    }
    return true;
}

void BoardIdentifier::startSoftware(ControllerType controllerType,AmplifierSampleRate sampleRate, StimStepSize stimStepSize,
                                  const QString& boardSerialNumber)
{   qDebug() << "start to run startSoftware";
    rhxController = new RHXController(controllerType, sampleRate);
    qDebug() << "success to run new rhxController";
    controllerInterface = new ControllerInterface(boardSerialNumber);
    qDebug() << "success to run startSoftware";
}
