#include <QSettings>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include "controlwindow.h"

ControlWindow::ControlWindow()
    : QMainWindow(nullptr)
{
    setAcceptDrops(true);

    //setAttribute(Qt::WA_DeleteOnClose);
    showControlPanelButton = new QToolButton(this);
    showControlPanelButton->setIcon(QIcon(":/images/showicon.png"));
    showControlPanelButton->setToolTip(tr("Show Control Panel"));
    //connect(showControlPanelButton, SIGNAL(clicked()), this, SLOT(showControlPanel()));

    createActions();
    createMenus();
    createStatusBar();

    controlButtons = new QToolBar(this);

    controlButtons->addAction(jumpToStartAction);
    controlButtons->addAction(jumpBack10SecAction);
    controlButtons->addAction(jumpBack1SecAction);

    controlButtons->addAction(rewindAction);
    controlButtons->addAction(fastForwardAction);

    controlButtons->addAction(stopAction);
    controlButtons->addAction(runAction);

    controlButtons->addAction(fastPlaybackAction);
    controlButtons->addAction(jumpToEndAction);
    controlButtons->addAction(jumpAction);

    controlButtons->addAction(chooseFileFormatAction);
    controlButtons->addAction(selectFilenameAction);
    controlButtons->addAction(recordAction);
    controlButtons->addAction(triggeredRecordAction);

    controlButtons->addWidget(new QLabel("   "));

    int margin = 6;

    timeLabel = new QLabel("<b>00:00:00</b>", this);
    int fontSize = 14;
    //if (state->highDPIScaleFactor > 1) fontSize = 21;
    QFont timeFont("Courier", fontSize);
    timeLabel->setFont(timeFont);
    timeLabel->setContentsMargins(margin, 0, margin, 0);
    QHBoxLayout* timeLayout = new QHBoxLayout;
    timeLayout->addWidget(timeLabel);
    timeLayout->setContentsMargins(0, 0, 0, 0);
    QFrame* timeBox = new QFrame(this);
    timeBox->setFrameStyle(QFrame::Box | QFrame::Plain);
    timeBox->setLayout(timeLayout);
    controlButtons->addWidget(timeBox);

    statusBars = new StatusBars(this);
    controlButtons->addWidget(new QLabel("   "));
    controlButtons->addWidget(statusBars);
    controlButtons->addWidget(new QLabel("   "));

    topStatusLabel = new QLabel("", this);
    topStatusLabel->setContentsMargins(margin, 0, margin, 0);
    controlButtons->addWidget(topStatusLabel);

    this->addToolBar(Qt::TopToolBarArea, controlButtons);

    //multiColumnDisplay = new MultiColumnDisplay(controllerInterface, state, this);
    //controllerInterface->setDisplay(multiColumnDisplay);
    //controlPanel = new ControlPanel(controllerInterface, state, this);
    //controlPanel->hide();

    QVBoxLayout *controlPanelCol = new QVBoxLayout;
    controlPanelCol->addWidget(showControlPanelButton);
    controlPanelCol->setAlignment(Qt::AlignTop);
    //controlPanelCol->addWidget(controlPanel);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(controlPanelCol);
    mainLayout->setAlignment(controlPanelCol, Qt::AlignTop);


    QScrollArea *scrollArea = new QScrollArea(this);
    //scrollArea->setWidget(multiColumnDisplay);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    mainLayout->addWidget(scrollArea);

    QWidget *central = new QWidget(this);
    central->setLayout(mainLayout);

    setCentralWidget(central);

    showMaximized();

    // Initialize Board Identifier.
    boardIdentifier = new BoardIdentifier(this);
    // Determine how many and what type of controllers are connected to this machine.
    //controllersInfo = boardIdentifier->getConnectedControllersInfo();

    //startBoard();
}

ControlWindow::~ControlWindow()
{

}
void ControlWindow::createActions()
{
    // Menu actions (at the top of the window)

    // File menu
    loadSettingsAction = new QAction(tr("Load Settings"), this);
    loadSettingsAction->setShortcut(tr("Ctrl+O"));
    //connect(loadSettingsAction, SIGNAL(triggered()), this, SLOT(loadSettingsSlot()));

    defaultSettingsAction = new QAction(tr("Set Default Settings"), this);
    //connect(defaultSettingsAction, SIGNAL(triggered()), this, SLOT(defaultSettingsSlot()));

    saveSettingsAction = new QAction(tr("Save Settings"), this);
    saveSettingsAction->setShortcut(tr("Ctrl+S"));
    //connect(saveSettingsAction, SIGNAL(triggered()), this, SLOT(saveSettingsSlot()));

    exitAction = new QAction(tr("Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    //connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Display menu
    zoomInTScaleAction = new QAction(tr("Zoom In Time Scale"), this);
    zoomInTScaleAction->setShortcuts({ tr("<"), tr(",") });
    //connect(zoomInTScaleAction, SIGNAL(triggered()), this, SLOT(zoomInTScale()));

    zoomOutTScaleAction = new QAction(tr("Zoom Out Time Scale"), this);
    zoomOutTScaleAction->setShortcuts({ tr(">"), tr(".") });
    //connect(zoomOutTScaleAction, SIGNAL(triggered()), this, SLOT(zoomOutTScale()));

    toggleRollSweepAction = new QAction(tr("Toggle Roll/Sweep"), this);
    toggleRollSweepAction->setShortcuts({ tr("/"), tr("?") });
    //connect(toggleRollSweepAction, SIGNAL(triggered()), this, SLOT(toggleRollSweep()));

    zoomInYScaleAction = new QAction(tr("Zoom In Voltage Scale"), this);
    zoomInYScaleAction->setShortcuts({ tr("+"), tr("=") });
    //connect(zoomInYScaleAction, SIGNAL(triggered()), this, SLOT(zoomInYScale()));

    zoomOutYScaleAction = new QAction(tr("Zoom Out Voltage Scale"), this);
    zoomOutYScaleAction->setShortcuts({ tr("-"), tr("_") });
    //connect(zoomOutYScaleAction, SIGNAL(triggered()), this, SLOT(zoomOutYScale()));

    displayLabelCustomNameAction = new QAction(tr("Display Custom Channel Name"), this);
    displayLabelCustomNameAction->setShortcut(tr("Ctrl+1"));
    displayLabelCustomNameAction->setCheckable(true);
    //connect(displayLabelCustomNameAction, SIGNAL(triggered()), this, SLOT(setLabelCustomName()));

    displayLabelNativeNameAction = new QAction(tr("Display Native Channel Name"), this);
    displayLabelNativeNameAction->setShortcut(tr("Ctrl+2"));
    displayLabelNativeNameAction->setCheckable(true);
    //connect(displayLabelNativeNameAction, SIGNAL(triggered()), this, SLOT(setLabelNativeName()));

    displayLabelImpedanceMagnitudeAction = new QAction(tr("Display Impedance Magnitude"), this);
    displayLabelImpedanceMagnitudeAction->setShortcut(tr("Ctrl+3"));
    displayLabelImpedanceMagnitudeAction->setCheckable(true);
    //connect(displayLabelImpedanceMagnitudeAction, SIGNAL(triggered()), this, SLOT(setLabelImpedanceMagnitude()));

    displayLabelImpedancePhaseAction = new QAction(tr("Display Impedance Phase"), this);
    displayLabelImpedancePhaseAction->setShortcut(tr("Ctrl+4"));
    displayLabelImpedancePhaseAction->setCheckable(true);
    //connect(displayLabelImpedancePhaseAction, SIGNAL(triggered()), this, SLOT(setLabelImpedancePhase()));

    displayLabelReferenceAction = new QAction(tr("Display Reference"), this);
    displayLabelReferenceAction->setShortcut(tr("Ctrl+5"));
    displayLabelReferenceAction->setCheckable(true);
    //connect(displayLabelReferenceAction, SIGNAL(triggered()), this, SLOT(setLabelReference()));

    displayCycleAction = new QAction(tr("Cycle Display Text"), this);
    displayCycleAction->setShortcut(tr("Ctrl+T"));
    //connect(displayCycleAction, SIGNAL(triggered()), this, SLOT(cycleLabelText()));

    changeBackgroundColorAction = new QAction(tr("Change Background Color"), this);
    //connect(changeBackgroundColorAction, SIGNAL(triggered()), this, SLOT(changeBackgroundColor()));

    displayLabelGroup = new QActionGroup(this);
    displayLabelGroup->addAction(displayLabelCustomNameAction);
    displayLabelGroup->addAction(displayLabelNativeNameAction);
    displayLabelGroup->addAction(displayLabelImpedanceMagnitudeAction);
    displayLabelGroup->addAction(displayLabelImpedancePhaseAction);
    displayLabelGroup->addAction(displayLabelReferenceAction);
    displayLabelCustomNameAction->setChecked(true);

    // Channel menu
    undoAction = new QAction(tr("Undo"), this);
    undoAction->setShortcut(tr("Ctrl+Z"));
    //connect(undoAction, SIGNAL(triggered()), this, SLOT(undoSlot()));

    redoAction = new QAction(tr("Redo"), this);
    redoAction->setShortcut(tr("Ctrl+Y"));
    //connect(redoAction, SIGNAL(triggered()), this, SLOT(redoSlot()));

    groupAction = new QAction(tr("Group"), this);
    groupAction->setShortcut(tr("Ctrl+G"));
    //connect(groupAction, SIGNAL(triggered()), this, SLOT(group()));

    ungroupAction = new QAction(tr("Ungroup"), this);
    ungroupAction->setShortcut(tr("Ctrl+Shift+G"));
    //connect(ungroupAction, SIGNAL(triggered()), this, SLOT(ungroup()));

    renameChannelAction = new QAction(tr("Rename Channel"), this);
    renameChannelAction->setShortcut(tr("Ctrl+R"));
    //connect(renameChannelAction, SIGNAL(triggered()), this, SLOT(renameChannel()));

    setReferenceAction = new QAction(tr("Set Reference"), this);
    //connect(setReferenceAction, SIGNAL(triggered()), this, SLOT(setReference()));

    setSpikeThresholdsAction = new QAction(tr("Set Spike Detection Thresholds"), this);
    //connect(setSpikeThresholdsAction, SIGNAL(triggered()), this, SLOT(setSpikeThresholds()));

    autoColorChannelsAction = new QAction(tr("Color Amplifier Channels"), this);
    //connect(autoColorChannelsAction, SIGNAL(triggered()), this, SLOT(autoColorChannels()));

    autoGroupChannelsAction = new QAction(tr("Group Amplifier Channels"), this);
    //connect(autoGroupChannelsAction, SIGNAL(triggered()), this, SLOT(autoGroupChannels()));

    ungroupAllChannelsAction = new QAction(tr("Ungroup All Channels"), this);
    //connect(ungroupAllChannelsAction, SIGNAL(triggered()), this, SLOT(ungroupAllChannels()));

    restoreOrderChannelsAction = new QAction(tr("Restore Original Order"), this);
    //connect(restoreOrderChannelsAction, SIGNAL(triggered()), this, SLOT(restoreOrderChannels()));

    alphabetizeChannelsAction = new QAction(tr("Alphabetize Channels"), this);
    //connect(alphabetizeChannelsAction, SIGNAL(triggered()), this, SLOT(alphabetizeChannels()));

    // Stimulation menu
    loadStimSettingsAction = new QAction(tr("Load Stimulation Settings"), this);
    //connect(loadStimSettingsAction, SIGNAL(triggered()), this, SLOT(loadStimSettingsSlot()));

    saveStimSettingsAction = new QAction(tr("Save Stimulation Settings"), this);
    //connect(saveStimSettingsAction, SIGNAL(triggered()), this, SLOT(saveStimSettingsSlot()));

    copyStimParametersAction = new QAction(tr("Copy Stimulation Parameters"), this);
    copyStimParametersAction->setShortcut(QKeySequence::Copy);
    //connect(copyStimParametersAction, SIGNAL(triggered()), this, SLOT(copyStimParametersSlot()));

    pasteStimParametersAction = new QAction(tr("Paste Stimulation Parameters"), this);
    pasteStimParametersAction->setShortcut(QKeySequence::Paste);
    //connect(pasteStimParametersAction, SIGNAL(triggered()), this, SLOT(pasteStimParametersSlot()));

    ampSettleSettingsAction = new QAction(tr("Amplifier Settle Settings"), this);
    //connect(ampSettleSettingsAction, SIGNAL(triggered()), this, SLOT(ampSettleSettingsSlot()));

    chargeRecoverySettingsAction = new QAction(tr("Charge Recovery Settings"), this);
    //connect(chargeRecoverySettingsAction, SIGNAL(triggered()), this, SLOT(chargeRecoverySettingsSlot()));


    // Network menu
    remoteControlAction = new QAction(tr("Remote TCP Control"), this);
    //connect(remoteControlAction, SIGNAL(triggered()), this, SLOT(remoteControl()));

    // Help menu
    keyboardHelpAction = new QAction(tr("Keyboard Shortcuts..."), this);
    keyboardHelpAction->setShortcut(tr("F12"));
    //connect(keyboardHelpAction, SIGNAL(triggered()), this, SLOT(keyboardShortcutsHelp()));

    enableLoggingAction = new QAction(tr("Generate Log File for Debug"), this);
    enableLoggingAction->setCheckable(true);
    //enableLoggingAction->setChecked(state->logErrors);
    //connect(enableLoggingAction, SIGNAL(toggled(bool)), this, SLOT(enableLoggingSlot(bool)));

    intanWebsiteAction = new QAction(tr("Visit Intan Website..."), this);
    //connect(intanWebsiteAction, SIGNAL(triggered()), this, SLOT(openIntanWebsite()));

    aboutAction = new QAction(tr("About Intan RHX Software..."), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    //Settings menu
    loginAction = new QAction(tr("login information..."), this);
    loginAction->setShortcut(tr("F11"));

    deviceAction = new QAction(tr("device information..."), this);
    deviceAction->setShortcut(tr("F10"));
    connect(deviceAction, SIGNAL(triggered()), this, SLOT(aboutDevice()));

    // Tools menu
    isiAction = new QAction(tr("ISI"), this);
    //connect(isiAction, SIGNAL(triggered()), this, SLOT(isi()));

    probeMapAction = new QAction(tr("Probe Map"), this);
    //connect(probeMapAction, SIGNAL(triggered()), this, SLOT(probeMap()));

    performanceAction = new QAction(tr("Performance Optimization"), this);
    //connect(performanceAction, SIGNAL(triggered()), this, SLOT(performance()));

    psthAction = new QAction(tr("PSTH"), this);
    //connect(psthAction, SIGNAL(triggered()), this, SLOT(psth()));

    spectrogramAction = new QAction(tr("Spectrogram"), this);
    //connect(spectrogramAction, SIGNAL(triggered()), this, SLOT(spectrogram()));

    spikeSortingAction = new QAction(tr("Spike Scope"), this);
    //connect(spikeSortingAction, SIGNAL(triggered()), this, SLOT(spikeSorting()));

    // Toolbar actions (within the toolbar, represented by an icon)

    rewindAction = new QAction(QIcon(":/images/rewindicon.png"), tr("Rewind"), this);
    rewindAction->setEnabled(false);
    //connect(rewindAction, SIGNAL(triggered()), this, SLOT(rewindSlot()));

    fastForwardAction = new QAction(QIcon(":/images/fficon.png"), tr("Fast Forward"), this);
    fastForwardAction->setEnabled(false);
    //connect(fastForwardAction, SIGNAL(triggered()), this, SLOT(fastForwardSlot()));


    runAction = new QAction(QIcon(":/images/runicon.png"), tr("Run"), this);
    //connect(runAction, SIGNAL(triggered()), this, SLOT(runControllerSlot()));

    fastPlaybackAction = new QAction(QIcon(":/images/fficon.png"), tr("Fast Forward"), this);
    //connect(fastPlaybackAction, SIGNAL(triggered()), this, SLOT(fastPlaybackSlot()));

    QPixmap jumpToEndPixmap(":/images/tostarticon.png");
    QMatrix rm;
    rm.rotate(180);
    jumpToEndPixmap = jumpToEndPixmap.transformed(rm);
    QIcon jumpToEndIcon(jumpToEndPixmap);
    jumpToEndAction = new QAction(jumpToEndIcon, tr("Jump to End"), this);
    //connect(jumpToEndAction, SIGNAL(triggered()), this, SLOT(jumpToEndSlot()));

    jumpToStartAction = new QAction(QIcon(":/images/tostarticon.png"), tr("Jump to Start"), this);
    //connect(jumpToStartAction, SIGNAL(triggered()), this, SLOT(jumpToStartSlot()));

    jumpBack1SecAction = new QAction(QIcon(":/images/jumpback1s.png"), tr("Jump Back 1s"), this);
    //connect(jumpBack1SecAction, SIGNAL(triggered()), this, SLOT(jumpBack1SecSlot()));

    jumpBack10SecAction = new QAction(QIcon(":/images/jumpback10s.png"), tr("Jump Back 10s"), this);
    //connect(jumpBack10SecAction, SIGNAL(triggered()), this, SLOT(jumpBack10SecSlot()));

    jumpAction = new QAction(QIcon(":/images/jumptoicon.png"), tr("Jump to Position"), this);
    //connect(jumpAction, SIGNAL(triggered()), this, SLOT(jumpToPositionSlot()));

    recordAction = new QAction(QIcon(":/images/recordicon.png"), tr("Record (no valid filename)"), this);
    //recordAction->setEnabled(state->filename->isValid());
    //connect(recordAction, SIGNAL(triggered()), this, SLOT(recordControllerSlot()));

    const QString stopActionText = "Stop";
    stopAction = new QAction(QIcon(":/images/stopicon.png"), stopActionText, this);
    stopAction->setEnabled(false);
    //connect(stopAction, SIGNAL(triggered()), this, SLOT(stopControllerSlot()));

    selectFilenameAction = new QAction(QIcon(":/images/selectfilenameicon.png"), tr("Select Filename"), this);
    //connect(selectFilenameAction, SIGNAL(triggered()), this, SLOT(selectBaseFilenameSlot()));

    chooseFileFormatAction = new QAction(QIcon(":/images/choosefileformaticon.png"), tr("Choose File Format"), this);
    //connect(chooseFileFormatAction, SIGNAL(triggered()), this, SLOT(chooseFileFormatDialog()));

    triggeredRecordAction = new QAction(QIcon(":/images/triggeredrecordicon.png"), tr("Triggered Recording (no valid filename)"), this);
    //triggeredRecordAction->setEnabled(state->filename->isValid());
    //connect(triggeredRecordAction, SIGNAL(triggered()), this, SLOT(triggeredRecordControllerSlot()));
}
void ControlWindow::createMenus()
{

    // File menu
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(loadSettingsAction);
    fileMenu->addAction(saveSettingsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(defaultSettingsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Display menu
    displayMenu = menuBar()->addMenu(tr("Display"));
    displayMenu->addAction(zoomInTScaleAction);
    displayMenu->addAction(zoomOutTScaleAction);
    displayMenu->addAction(toggleRollSweepAction);
    displayMenu->addSeparator();
    displayMenu->addAction(zoomInYScaleAction);
    displayMenu->addAction(zoomOutYScaleAction);
    displayMenu->addSeparator()->setText(tr("Labels"));
    displayMenu->addAction(displayLabelCustomNameAction);
    displayMenu->addAction(displayLabelNativeNameAction);
    displayMenu->addAction(displayLabelImpedanceMagnitudeAction);
    displayMenu->addAction(displayLabelImpedancePhaseAction);
    displayMenu->addAction(displayLabelReferenceAction);
    displayMenu->addAction(displayCycleAction);
    displayMenu->addSeparator();
    displayMenu->addAction(changeBackgroundColorAction);

    // Channels menu
    channelMenu = menuBar()->addMenu(tr("Channels"));
    channelMenu->addAction(undoAction);
    channelMenu->addAction(redoAction);
    channelMenu->addSeparator();
    channelMenu->addAction(groupAction);
    channelMenu->addAction(ungroupAction);
    channelMenu->addSeparator();
    channelMenu->addAction(autoColorChannelsAction);
    channelMenu->addAction(autoGroupChannelsAction);
    channelMenu->addAction(ungroupAllChannelsAction);
    channelMenu->addSeparator();
    channelMenu->addAction(renameChannelAction);
    channelMenu->addAction(setReferenceAction);
    channelMenu->addAction(alphabetizeChannelsAction);
    channelMenu->addAction(restoreOrderChannelsAction);
    channelMenu->addSeparator();
    channelMenu->addAction(setSpikeThresholdsAction);

    // Stimulation menu
    stimulationMenu = menuBar()->addMenu(tr("Stimulation"));
    stimulationMenu->addAction(loadStimSettingsAction);
    stimulationMenu->addAction(saveStimSettingsAction);
    stimulationMenu->addSeparator();
    stimulationMenu->addAction(copyStimParametersAction);
    stimulationMenu->addAction(pasteStimParametersAction);
    stimulationMenu->addSeparator();
    stimulationMenu->addAction(ampSettleSettingsAction);
    stimulationMenu->addAction(chargeRecoverySettingsAction);

    // Tools menu
    toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(spikeSortingAction);
    toolsMenu->addAction(isiAction);
    toolsMenu->addAction(psthAction);
    toolsMenu->addAction(spectrogramAction);
    toolsMenu->addAction(probeMapAction);

    // Network menu
    tcpMenu = menuBar()->addMenu(tr("Network"));
    tcpMenu->addAction(remoteControlAction);


    // Performance menu
    performanceMenu = menuBar()->addMenu(tr("Performance"));
    performanceMenu->addAction(performanceAction);

    menuBar()->addSeparator();

    // Help
    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(keyboardHelpAction);
    helpMenu->addSeparator();

    helpMenu->addAction(enableLoggingAction);
    helpMenu->addSeparator();

    helpMenu->addAction(intanWebsiteAction);
    helpMenu->addAction(aboutAction);

    // Settings
    settingsMenu = menuBar()->addMenu(tr("Settings"));
    settingsMenu->addAction(loginAction);
    settingsMenu->addSeparator();

    settingsMenu->addAction(deviceAction);

}

void ControlWindow::createStatusBar()
{
    statusBarLabel = new QLabel(tr(""));
    statusBar()->addWidget(statusBarLabel, 1);
    statusBar()->setSizeGripEnabled(false); // Fixed window size
}

void ControlWindow::about()
{
    QMessageBox::about(this, tr("About Intan RHX Software"),
                       tr("<h2>Intan RHX Data Acquisition Software</h2>"
                       "<p>Version ") + SoftwareVersion +
                       tr("<p>Copyright ") + CopyrightSymbol + " " + ApplicationCopyrightYear + tr(" Intan Technologies"
                       "<p>This application controls the "
                       "RHD USB Interface Board, RHD Recording Controllers, "
                       "and RHS Stimulation/Recording Controller "
                       "from Intan Technologies.  The C++/Qt source code "
                       "for this application is freely available from Intan Technologies. "
                       "For more information visit <i>www.intantech.com</i>."
                       "<p>This program is free software: you can redistribute it and/or modify "
                       "it under the terms of the GNU General Public License as published "
                       "by the Free Software Foundation, either version 3 of the License, or "
                       "(at your option) any later version."
                       "<p>This program is distributed in the hope that it will be useful, "
                       "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                       "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                       "GNU General Public License for more details."));
}

void ControlWindow::aboutDevice()
{
    QMessageBox::about(this, tr("Device Information"),
                       tr("<h2>Connected Device Information</h2>")
                       );
}

void ControlWindow::startBoard()
{
    AmplifierSampleRate sampleRate = SampleRate20000Hz;
    StimStepSize stimStepSize = StimStepSize500nA;
    if(controllersInfo.size() >= 1){
        boardIdentifier->startSoftware(ControllerStimRecord, sampleRate, stimStepSize, controllersInfo[0]->serialNumber);;
    }
}


