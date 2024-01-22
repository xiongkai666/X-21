#ifndef ABSTRACTRHXCONTROLLER_H
#define ABSTRACTRHXCONTROLLER_H

#include "rhxglobals.h"
#include <string>
#include <vector>
#include <deque>
#include <mutex>
#include <cstdint>

using namespace std;

enum AcquisitionMode {
    LiveMode,
    SyntheticMode,
    PlaybackMode
};

class AbstractRHXController
{
public:

    AbstractRHXController(ControllerType type_, AmplifierSampleRate sampleRate_);
    virtual ~AbstractRHXController();


    void initialize();

    static int maxNumDataStreams(ControllerType type_);
    int maxNumDataStreams() const;

    static int maxNumSPIPorts(ControllerType type_);
    int maxNumSPIPorts() const;

    static int boardMode(ControllerType type_);
    int boardMode() const;

    ControllerType getType() const;
    AmplifierSampleRate getSampleRateEnum() const;
    double getSampleRate() const;
    static double getSampleRate(AmplifierSampleRate sampleRate_);

    static string getBoardTypeString(ControllerType type_);
    static string getSampleRateString(AmplifierSampleRate sampleRate_);
    static string getStimStepSizeString(StimStepSize stepSize_);

    virtual bool isPlayback() const = 0;
    virtual AcquisitionMode acquisitionMode() const = 0;
    virtual int open(const string& boardSerialNumber) = 0;
    virtual bool uploadFPGABitfile(const string& filename) = 0;
    virtual void resetBoard() = 0;

protected:
    ControllerType type;
    AmplifierSampleRate sampleRate;
};
#endif // ABSTRACTRHXCONTROLLER_H
