#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cmath>
#include <QDebug>
#include "rhxcontroller.h"

RHXController::RHXController(ControllerType type_, AmplifierSampleRate sampleRate_) :
    AbstractRHXController(type_, sampleRate_),
    dev(nullptr)
{
}



RHXController::~RHXController()
{

}

// Find an Pionway board attached to a USB port with the given serial number and open it.
// Returns 1 if successful, -1 if Pionway cannot be loaded, and -2 if board can't be found.
int RHXController::open(const string& boardSerialNumber)
{
    qDebug() << "start to run open()";
    pwTDeviceInfo DeviceInfo;
    cout << "Attempting to connect to device '" << boardSerialNumber.c_str() << "'\n";

    qDebug() << "start to run OpenBySerial";
    CPionway::ErrorCode result = dev->OpenBySerial(boardSerialNumber);
    qDebug() << "success to run OpenBySerial";
    // Attempt to open device.
    if (result != CPionway::NO_ERR) {
        delete dev;
        cerr << "Device could not be opened.  Is one connected?\n";
        cerr << "Error = " << result << "\n";
        return -2;
    }

    // Configure the on-board PLL appropriately.
    //dev->LoadDefaultPLLConfiguration();

    // Get some general information about the XEM.
    cout << "Pionway device firmware version: " << DeviceInfo.firmwareMajorVersion << "." <<
            DeviceInfo.firmwareMinorVersion << '\n';
    dev->GetDeviceInfo(&DeviceInfo);
    cout << "Pionway device serial number: " << DeviceInfo.serialNumber << '\n';
    cout << "Pionway device ID string: " << DeviceInfo.deviceID << "\n\n";

    return 1;
}
bool RHXController::uploadFPGABitfile(const string& filename)
{
    CPionway::ErrorCode errorCode = dev->ConfigureFPGA(filename);

    switch (errorCode) {
    case CPionway::NO_ERR:
        break;
    case CPionway::DEVICE_NOT_OPEN:
        cerr << "FPGA configuration failed: Device not open.\n";
        return false;
    case CPionway::FILE_ERROR:
        cerr << "FPGA configuration failed: Cannot find configuration file.\n";
        return false;
    case CPionway::INVALID_BITSTREAM:
        cerr << "FPGA configuration failed: Bitstream is not properly formatted.\n";
        return false;
    case CPionway::DONE_NOT_HIGH:
        cerr << "FPGA configuration failed: FPGA DONE signal did not assert after configuration.\n";
        cerr << "Note: Switch may be in PROM position instead of USB position.\n";
        return false;
    case CPionway::TRANSFER_ERROR:
        cerr << "FPGA configuration failed: USB error occurred during download.\n";
        return false;
    case CPionway::COMMUNICATION_ERROR:
        cerr << "FPGA configuration failed: Communication error with firmware.\n";
        return false;
    case CPionway::UNSUPPORTED_FEATURE:
        cerr << "FPGA configuration failed: Unsupported feature.\n";
        return false;
    default:
        cerr << "FPGA configuration failed: Unknown error.\n";
        return false;
    }

    // Check for Pionway Pionway support in the FPGA configuration.
    if (dev->IsPionwayEnabled() == false) {
        cerr << "Pionway Pionway support is not enabled in this FPGA configuration.\n";
        delete dev;
        return false;
    }
    return true;
}

// Reset FPGA.  This clears all auxiliary command RAM banks, clears the USB FIFO, and resets the per-channel sampling
// rate to 30.0 kS/s/ch.
void RHXController::resetBoard()
{
    resetBoard(dev);
}

// Simple board reset
void RHXController::resetBoard(CPionway* dev_)
{
    dev_->ActivateTriggerIn(TrigInResetRun, 0x31);
}

bool RHXController::isPlayback() const
{
    return 0;
}
AcquisitionMode RHXController::acquisitionMode() const
{
    return LiveMode;
}
