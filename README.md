This Arduino project is an audio player that allows users to play audio tracks stored on an SD card through the DFRobotDFPlayerMini module. The player provides basic controls such as play, pause, next track, and previous track through button inputs.
Features:

    Play audio tracks from SD card using the DFRobotDFPlayerMini module.
    Control playback through physical buttons.
    Ability to control volume.
    Persistence of audio track and volume state.
    Error handling for missing audio tracks.

Dependencies:

    DFRobotDFPlayerMini library
    ezButton library
    Arduino EEPROM library for state persistence.

Hardware Components:

    Arduino board.
    DFRobotDFPlayerMini module.
    SD card with audio tracks.
    Physical buttons for playback controls.
    Optional: MOSFET for controlling DFPlayer power (pin 2).

Overview:

    Main File:
        Initializes the DFPlayer module, button controllers, and player controller.
        Sets up communication with the DFPlayer and initializes button configurations.
        Main loop checks button states and handles audio playback.
    ButtonController:
        Manages individual button inputs.
        Can play a specific audio track or handle media controls like next, previous, play, or pause.
        MediaController class extends ButtonController to provide additional functionality for media controls.
    Input:
        Handles button input states using the ezButton library.
        Differentiates between short presses and long presses.
    PersistanceState:
        Manages the saved state of the audio player, including the current track and volume level.
        Uses the Arduino EEPROM for state persistence.
    PlayerController:
        Manages the DFPlayer module for audio playback.
        Handles errors and communicates with the DFPlayer to control playback.

Usage:

    Load audio tracks onto the SD card. Ensure that the tracks are stored in folders named numerically (e.g., 1, 2, etc.) and the tracks within those folders are also named numerically (e.g., 001.mp3, 002.mp3, etc.).
    Connect the DFPlayer module, buttons, and (optionally) the MOSFET as described in the code comments.
    Upload the provided code to the Arduino board.
    Use the physical buttons to control audio playback.

Note:

    Ensure that the connected pins in the code match the actual connections on the Arduino board.
    The code provides error messages through the Serial monitor to help diagnose issues, such as missing audio files or button presses.
    It is recommended to check the Serial monitor if encountering any issues during usage.

This README provides a general overview of the Arduino audio player project. For detailed implementation, refer to the provided code.