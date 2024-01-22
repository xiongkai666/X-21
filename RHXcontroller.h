#ifndef RHXCONTROLLER_H
#define RHXCONTROLLER_H

#include <QObject>
#include <mutex>
#include <string>
#include <vector>
#include <deque>
#include <cstdint>

#include "abstractrhxcontroller.h"
#include "rhxglobals.h"
#include "PionwayDLL.h"

using namespace std;

class RHXController : public AbstractRHXController, public QObject, public CPionway
{

public:
    RHXController(ControllerType type_, AmplifierSampleRate sampleRate_);
    ~RHXController();

    int open(const string& boardSerialNumber) override;
    bool uploadFPGABitfile(const string& filename) override;
    void resetBoard() override;

    // Physical board only
    static void resetBoard(CPionway* dev_);

    bool isPlayback() const override;
    AcquisitionMode acquisitionMode() const override;

private:
    CPionway *dev;

    enum EndPoint {

        WireInDataFreqPll = 0x03,
        WireInMisoDelay = 0x04,
        WireInDataStreamEn = 0x14,
        WireInDacSource1 = 0x16,
        WireInDacSource2 = 0x17,
        WireInDacSource3 = 0x18,
        WireInDacSource4 = 0x19,
        WireInDacSource5 = 0x1a,
        WireInDacSource6 = 0x1b,
        WireInDacSource7 = 0x1c,
        WireInDacSource8 = 0x1d,
        WireInDacManual = 0x1e,
        WireInMultiUse = 0x1f,

        TrigInResetRun = 0x40,
        TrigInSpiStart = 0x41,

        WireOutSpiRunning = 0x22,
        WireOutTtlIn = 0x23,
        WireOutDataClkLocked = 0x24,
        WireOutBoardMode = 0x25,
        WireOutBoardId = 0x3e,
        WireOutBoardVersion = 0x3f,

        PipeOutData = 0xa0
    };

    // Physical board only
    //static int endPointWireInResetRun() { return (int)WireInResetRun; }

protected:

    mutex okMutex;

};
#endif // RHXCONTROLLER_H
