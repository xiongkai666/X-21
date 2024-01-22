#include "abstractrhxcontroller.h"

#include <iostream>
#include <iomanip>
#include <cmath>

AbstractRHXController::AbstractRHXController(ControllerType type_, AmplifierSampleRate sampleRate_) :
    type(type_),
    sampleRate(sampleRate_)
{

}

AbstractRHXController::~AbstractRHXController()
{

}

// Return the board mode for a controller of the given type.
int AbstractRHXController::boardMode(ControllerType type_)
{
    switch (type_) {
    case ControllerRecordUSB3:
        return 13;
    case ControllerStimRecord:
        return 14;
    default:
        return -1;
    }
}

// Return the board mode for a controller of this controller's type.
int AbstractRHXController::boardMode() const
{
    return boardMode(type);
}

// Return the type of this controller.
ControllerType AbstractRHXController::getType() const
{
    return type;
}

// Return the sample rate (as an enum) of this controller.
AmplifierSampleRate AbstractRHXController::getSampleRateEnum() const
{
    return sampleRate;
}

// Return the current per-channel sampling rate (in Hz) as a floating-point number.
double AbstractRHXController::getSampleRate() const
{
    return getSampleRate(sampleRate);
}

// Return the given sample rate enum as a floating-point number.
double AbstractRHXController::getSampleRate(AmplifierSampleRate sampleRate_)
{
    switch (sampleRate_) {
    case SampleRate1000Hz:
        return 1000.0;
        break;
    case SampleRate1250Hz:
        return 1250.0;
        break;
    case SampleRate1500Hz:
        return 1500.0;
        break;
    case SampleRate2000Hz:
        return 2000.0;
        break;
    case SampleRate2500Hz:
        return 2500.0;
        break;
    case SampleRate3000Hz:
        return 3000.0;
        break;
    case SampleRate3333Hz:
        return (10000.0 / 3.0);
        break;
    case SampleRate4000Hz:
        return 4000.0;
        break;
    case SampleRate5000Hz:
        return 5000.0;
        break;
    case SampleRate6250Hz:
        return 6250.0;
        break;
    case SampleRate8000Hz:
        return 8000.0;
        break;
    case SampleRate10000Hz:
        return 10000.0;
        break;
    case SampleRate12500Hz:
        return 12500.0;
        break;
    case SampleRate15000Hz:
        return 15000.0;
        break;
    case SampleRate20000Hz:
        return 20000.0;
        break;
    case SampleRate25000Hz:
        return 25000.0;
        break;
    case SampleRate30000Hz:
        return 30000.0;
        break;
    default:
        return -1.0;
    }
}

string AbstractRHXController::getBoardTypeString(ControllerType type_)
{
    string typeString;
    switch (type_) {
    case ControllerRecordUSB3:
        typeString = "ControllerRecordUSB3"; break;
    case ControllerStimRecord:
        typeString = "ControllerStimRecord"; break;
    default:
        typeString = "unknown"; break;
    }
    return typeString;
}

string AbstractRHXController::getSampleRateString(AmplifierSampleRate sampleRate_)
{
    string sampleRateString;
    switch (sampleRate_) {
    case SampleRate30000Hz:
        sampleRateString = "30 kHz"; break;
    case SampleRate25000Hz:
        sampleRateString = "25 kHz"; break;
    case SampleRate20000Hz:
        sampleRateString = "20 kHz"; break;
    case SampleRate15000Hz:
        sampleRateString = "15 kHz"; break;
    case SampleRate12500Hz:
        sampleRateString = "12.5 kHz"; break;
    case SampleRate10000Hz:
        sampleRateString = "10 kHz"; break;
    case SampleRate8000Hz:
        sampleRateString = "8 kHz"; break;
    case SampleRate6250Hz:
        sampleRateString = "6.25 kHz"; break;
    case SampleRate5000Hz:
        sampleRateString = "5 kHz"; break;
    case SampleRate4000Hz:
        sampleRateString = "4 kHz"; break;
    case SampleRate3333Hz:
        sampleRateString = "3.33 kHz"; break;
    case SampleRate3000Hz:
        sampleRateString = "3 kHz"; break;
    case SampleRate2500Hz:
        sampleRateString = "2.5 kHz"; break;
    case SampleRate2000Hz:
        sampleRateString = "2 kHz"; break;
    case SampleRate1500Hz:
        sampleRateString = "1.5 kHz"; break;
    case SampleRate1250Hz:
        sampleRateString = "1.25 kHz"; break;
    case SampleRate1000Hz:
        sampleRateString = "1 kHz"; break;
    default:
        sampleRateString = "unknown"; break;
    }
    return sampleRateString;
}

string AbstractRHXController::getStimStepSizeString(StimStepSize stepSize_)
{
    string stimStepSizeString;
    switch (stepSize_) {
    case StimStepSize10nA:
        stimStepSizeString = "10 nA"; break;
    case StimStepSize20nA:
        stimStepSizeString = "20 nA"; break;
    case StimStepSize50nA:
        stimStepSizeString = "50 nA"; break;
    case StimStepSize100nA:
        stimStepSizeString = "100 nA"; break;
    case StimStepSize200nA:
        stimStepSizeString = "200 nA"; break;
    case StimStepSize500nA:
        stimStepSizeString = "500 nA"; break;
    case StimStepSize1uA:
        stimStepSizeString = "1 uA"; break;
    case StimStepSize2uA:
        stimStepSizeString = "2 uA"; break;
    case StimStepSize5uA:
        stimStepSizeString = "5 uA"; break;
    case StimStepSize10uA:
        stimStepSizeString = "10 uA"; break;
    default:
        stimStepSizeString = "unknown"; break;
    }
    return stimStepSizeString;
}
