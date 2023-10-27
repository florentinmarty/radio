#include "ButtonController.h"

ButtonController::ButtonController() {}

ButtonController::ButtonController(int pin, int folder, PersistanceState state, DFRobotDFPlayerMini player) {
  _state = state;
  _input = Input(pin);
  _folder = folder;
  _player = player;
}

void ButtonController::loop() {
   _input.updateState();

  if (_input.getFallingEdge())  {
    Serial.println(_folder + " gedrückt");
    _state.setFolder(_folder);
    _player.playFolder(_state.getFolder(), _state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

  if (_input.isLongPressed())  {
    Serial.println(_folder + " lang gedrückt");
    _state.setFolder(_folder);
    _state.setTrack(_folder);
    _player.playFolder(_state.getFolder(), _state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }
}

// Implementation for the AlternateButtonController class

MediaController::MediaController(int pin, PersistanceState state, DFRobotDFPlayerMini player, MediaControl action) 
    : ButtonController(pin, -1, state, player) {
      _action = action;
      _volume = _state.getVolume();
  
      if (_volume > MAX_VOLUME){
        state.setVolume(MAX_VOLUME);
      }
 }
 
void MediaController::loop() {
     _input.updateState();

  if (_input.isShortPressed()){
    switch (_action) {
      case MediaControl::NEXT_TRACK :
        Serial.println("forward");
        _state.nextTrack();
        _player.playFolder(_state.getFolder(), _state.getTrack());
        break;

      case MediaControl::PREVIOUS_TRACK:
        Serial.println("back");
    
        int currentTrack = _state.getTrack();
        int nextTrack = currentTrack - 1;
        if (nextTrack < 1) {
          nextTrack = 1;
        }

        _state.setTrack(nextTrack);
        _player.playFolder(_state.getFolder(), _state.getTrack());
        break;

      case MediaControl::PAUSE_PLAY:
        if (_isPaused){
          _player.start();
          _isPaused = false;
        }else{
          _player.pause();
          _isPaused = true;
        }
        break;

      default:
            // Handle unknown or unsupported media
            Serial.println("Unknown media type.");
            break;
    }
  }
  if (_input.isLongPressed()){
    switch (_action) {
      case MediaControl::NEXT_TRACK:
        if (_volume +1 > MAX_VOLUME) {
          _volume = MAX_VOLUME;
         } else {
          _volume++;
        }
        adjustVolume(_volume);
        break;

      case MediaControl::PREVIOUS_TRACK:
      if (_volume < 2) {
          _volume = 1;
      } else {
          _volume--;
      }
        adjustVolume(_volume);
        break;

      default:
        // Handle unknown or unsupported media
        Serial.println("Unknown media type.");
        break;
    }
  }
}

  void MediaController::adjustVolume(int newVolume) {
    _player.volume(newVolume);  // Adjust player volume
    _state.setVolume(newVolume);    // Save volume state
    Serial.print("new volume ");
    Serial.println(newVolume);     // Print current volume
    delay(100);  // Delay for 100ms
}
