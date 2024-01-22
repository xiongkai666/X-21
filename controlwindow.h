#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "rhxglobals.h"
#include "rhxcontroller.h"
#include "statusbars.h"
#include "boardidentifier.h"
#include "startupdialog.h"

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    ControlWindow();
    ~ControlWindow();

private slots:
    /*
    void showControlPanel();

    void probeMap();

    void performance();
    void psth();
    void spectrogram();
    void spikeSorting();

    void isi();

    void keyboardShortcutsHelp();
    void enableLoggingSlot(bool enable);
    void openIntanWebsite();
    */
    void about();
    void aboutDevice();
    void startBoard();

private:

    BoardIdentifier *boardIdentifier;
    QVector<ControllerInfo*> controllersInfo;

    QCheckBox *defaultSampleRateCheckBox;

    //SystemState* state;
    //CommandParser* parser;
    QToolButton *showControlPanelButton;

    //ProbeMapWindow *probeMapWindow;

    QToolBar *controlButtons;
    /*
    KeyboardShortcutDialog *keyboardShortcutDialog;
    TriggerRecordDialog *triggerRecordDialog;
    SetFileFormatDialog *fileFormatDialog;
    ISIDialog *isiDialog;
    PSTHDialog *psthDialog;
    SpectrogramDialog *spectrogramDialog;
    SpikeSortingDialog *spikeSortingDialog;
    */
    QMenu *fileMenu;
    QMenu *displayMenu;
    QMenu *channelMenu;
    QMenu *stimulationMenu;
    QMenu *tcpMenu;
    QMenu *impedanceMenu;
    QMenu *toolsMenu;
    QMenu *performanceMenu;
    QMenu *helpMenu;
    QMenu *settingsMenu;

    QAction *runAction;
    QAction *stopAction;
    QAction *selectFilenameAction;
    QAction *chooseFileFormatAction;
    QAction *recordAction;
    QAction *triggeredRecordAction;
    QAction *rewindAction;
    QAction *fastForwardAction;
    QAction *fastPlaybackAction;
    QAction *jumpToEndAction;
    QAction *jumpToStartAction;
    QAction *jumpBack1SecAction;
    QAction *jumpBack10SecAction;
    QAction *jumpAction;

    QAction *zoomInTScaleAction;
    QAction *zoomOutTScaleAction;
    QAction *toggleRollSweepAction;
    QAction *zoomInYScaleAction;
    QAction *zoomOutYScaleAction;

    QActionGroup *displayLabelGroup;
    QAction *displayLabelCustomNameAction;
    QAction *displayLabelNativeNameAction;
    QAction *displayLabelImpedanceMagnitudeAction;
    QAction *displayLabelImpedancePhaseAction;
    QAction *displayLabelReferenceAction;
    QAction *displayCycleAction;
    QAction *changeBackgroundColorAction;
    QAction *showAuxInputsAction;
    QAction *showSupplyVoltagesAction;

    QAction *loadSettingsAction;
    QAction *defaultSettingsAction;
    QAction *saveSettingsAction;
    QAction *loadStimSettingsAction;
    QAction *saveStimSettingsAction;
    QAction *exitAction;

    QAction *undoAction;
    QAction *redoAction;
    QAction *groupAction;
    QAction *ungroupAction;
    QAction *renameChannelAction;
    QAction *setReferenceAction;
    QAction *setSpikeThresholdsAction;
    QAction *autoColorChannelsAction;
    QAction *autoGroupChannelsAction;
    QAction *ungroupAllChannelsAction;
    QAction *restoreOrderChannelsAction;
    QAction *alphabetizeChannelsAction;

    QAction *copyStimParametersAction;
    QAction *pasteStimParametersAction;
    QAction *ampSettleSettingsAction;
    QAction *chargeRecoverySettingsAction;

    QAction *keyboardHelpAction;
    QAction *enableLoggingAction;
    QAction *intanWebsiteAction;
    QAction *aboutAction;
    QAction *loginAction;
    QAction *deviceAction;

    QAction *remoteControlAction;

    QAction *isiAction;
    QAction *probeMapAction;
    QAction *spectrogramAction;
    QAction *psthAction;

    QAction *performanceAction;

    QAction *spikeSortingAction;

    QLabel *timeLabel;
    QLabel *topStatusLabel;
    QLabel *statusBarLabel;
    QString queuedErrorMessage;

    StatusBars* statusBars;

    //AbstractPanel *controlPanel;

    //MultiColumnDisplay *multiColumnDisplay;

    QDialog *tcpDialog;

    //TCPDisplay *tcpDisplay;

    QHBoxLayout *showHideRow;

    QSpacerItem *showHideStretch;

    //XMLInterface* stimParametersInterface;

    //StimParametersClipboard *stimClipboard;

    bool currentlyRunning;
    bool currentlyRecording;
    bool fastPlaybackMode;

    int hwFifoNearlyFull;
    double mainCpuLoad;

    QString loadSettings();

    void updateForFilename(bool valid);
    void updateLiveNotesDialog();
    void updateForRun();
    void updateForLoad();
    void updateForStop();

    void createMenus();
    void createActions();
    void updateMenus();

    void createStatusBar();
};
#endif // CONTROLWINDOW_H
