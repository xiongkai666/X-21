#ifndef RHXGLOBALS_H
#define RHXGLOBALS_H

#include <QString>

// Software version number (e.g., version 1.3.5)
#define SOFTWARE_MAIN_VERSION_NUMBER 3
#define SOFTWARE_SECONDARY_VERSION_NUMBER 3
#define SOFTWARE_TERTIARY_VERSION_NUMBER 0

enum ControllerType {
    ControllerRecordUSB3 = 1,
    ControllerStimRecord = 2
};

enum DemoSelections {
    DemoUSBInterfaceBoard,
    DemoRecordingController,
    DemoStimRecordController,
    DemoPlayback
};

enum AmplifierSampleRate {
    SampleRate1000Hz = 0,
    SampleRate1250Hz = 1,
    SampleRate1500Hz = 2,
    SampleRate2000Hz = 3,
    SampleRate2500Hz = 4,
    SampleRate3000Hz = 5,
    SampleRate3333Hz = 6,
    SampleRate4000Hz = 7,
    SampleRate5000Hz = 8,
    SampleRate6250Hz = 9,
    SampleRate8000Hz = 10,
    SampleRate10000Hz = 11,
    SampleRate12500Hz = 12,
    SampleRate15000Hz = 13,
    SampleRate20000Hz = 14,
    SampleRate25000Hz = 15,
    SampleRate30000Hz = 16
};

enum StimStepSize {
    StimStepSizeMin = 0,
    StimStepSize10nA = 1,
    StimStepSize20nA = 2,
    StimStepSize50nA = 3,
    StimStepSize100nA = 4,
    StimStepSize200nA = 5,
    StimStepSize500nA = 6,
    StimStepSize1uA = 7,
    StimStepSize2uA = 8,
    StimStepSize5uA = 9,
    StimStepSize10uA = 10,
    StimStepSizeMax = 11
};

enum ChipType {
    NoChip = -1,
    RHD2132Chip = 1,
    RHD2216Chip = 2,
    RHD2164Chip = 4,
    RHS2116Chip = 32,
};

enum SignalType {
    AmplifierSignal = 0,
    AuxInputSignal = 1,
    SupplyVoltageSignal = 2,
    BoardAdcSignal = 3,
    BoardDacSignal = 4,
    BoardDigitalInSignal = 5,
    BoardDigitalOutSignal = 6
};

enum FileFormat {
    FileFormatIntan,
    FileFormatFilePerSignalType,
    FileFormatFilePerChannel
};

enum BoardMode {
    RHDUSBInterfaceBoard,
    RHSUSBInterfaceBoard,
    UnknownUSB3Device,
};

const QString OrganizationName = "Intan Technologies";
const QString OrganizationDomain = "intantech.com";
const QString ApplicationName = "IntanRHX";
const QString ApplicationCopyrightYear = "2020-2023";

const QString SoftwareVersion = QString::number(SOFTWARE_MAIN_VERSION_NUMBER) + "." +
                                QString::number(SOFTWARE_SECONDARY_VERSION_NUMBER) + "." +
                                QString::number(SOFTWARE_TERTIARY_VERSION_NUMBER);

// FPGA configuration bitfiles
const QString ConfigFileRHSController = "ConfigRHSController.bit";

// Special Unicode characters, as QString data type
const QString DeltaSymbol = QString((QChar)0x0394);
const QString MuSymbol = QString((QChar)0x03bc);
const QString MicroVoltsSymbol = MuSymbol + QString("V");
const QString MicroAmpsSymbol = MuSymbol + QString("A");
const QString MicroSecondsSymbol = MuSymbol + QString("s");
const QString OmegaSymbol = QString((QChar)0x03a9);
const QString AngleSymbol = QString((QChar)0x2220);
const QString DegreeSymbol = QString((QChar)0x00b0);
const QString PlusMinusSymbol = QString((QChar)0x00b1);
const QString SqrtSymbol = QString((QChar)0x221a);
const QString EnDashSymbol = QString((QChar)0x2013);
const QString EmDashSymbol = QString((QChar)0x2014);
const QString EllipsisSymbol = QString((QChar)0x2026);
const QString CopyrightSymbol = QString((QChar)0x00a9);

const QString MuSymbolTCP = QString::fromStdWString(L"\u00b5");
const QString PlusMinusSymbolTCP = QString::fromStdWString(L"\u00b1");

const QString EndOfLine = QString("\n");

const QString ControllerTypeString[3] = {
    "RHD USB Interface Board",
    "RHD Recording Controller",
    "RHS Stimulation/Recording Controller"
};

const QString ControllerTypeSettingsGroup[3] = {
    "RHDUSBInterfaceBoard",
    "RHDRecordingController",
    "RHSStimRecordingController"
};

const QString SampleRateString[17] = {
    "1.0 kHz",
    "1.25 kHz",
    "1.5 kHz",
    "2 kHz",
    "2.5 kHz",
    "3.0 kHz",
    "3.33 kHz",
    "4 kHz",
    "5 kHz",
    "6.25 kHz",
    "8 kHz",
    "10 kHz",
    "12.5 kHz",
    "15 kHz",
    "20 kHz",
    "25 kHz",
    "30 kHz"
};

const QString StimStepSizeString[12] = {
    "minimum step size (imprecise)",
    PlusMinusSymbol + "2.55 " + MicroAmpsSymbol + " range (10 nA step size)",
    PlusMinusSymbol + "5.10 " + MicroAmpsSymbol + " range (20 nA step size)",
    PlusMinusSymbol + "12.75 " + MicroAmpsSymbol + " range (50 nA step size)",
    PlusMinusSymbol + "25.5 " + MicroAmpsSymbol + " range (0.1 " + MicroAmpsSymbol + " step size)",
    PlusMinusSymbol + "51.0 " + MicroAmpsSymbol + " range (0.2 " + MicroAmpsSymbol + " step size)",
    PlusMinusSymbol + "127.5 " + MicroAmpsSymbol + " range (0.5 " + MicroAmpsSymbol + " step size)",
    PlusMinusSymbol + "255 " + MicroAmpsSymbol + " range (1 " + MicroAmpsSymbol + " step size)",
    PlusMinusSymbol + "510 " + MicroAmpsSymbol + " range (2 " + MicroAmpsSymbol + " step size)",
    PlusMinusSymbol + "1.275 mA range (5 " + MicroAmpsSymbol + " step size)",
    PlusMinusSymbol + "2.550 mA range (10 " + MicroAmpsSymbol + " step size)",
    "maximum step size (imprecise)"
};


// Parameter setting error messages
const QString ReadOnlyErrorMessage = "cannot be changed once software has started.";
const QString RunningErrorMessage = "cannot be set while controller is running.";
const QString RecordingErrorMessage = "cannot be set while controller is recording.";
const QString NonStimErrorMessage = "cannot be set with a non-stim controller";
const QString NonStimRunningErrorMessage = "cannot be set with a non-stim controller, or while controller is running";
const QString StimErrorMessage = "cannot be set with a stim controller";
const QString StimRunningErrorMessage = "cannot be set with a stim controller, or while controller is running";

#endif // RHXGLOBALS_H
